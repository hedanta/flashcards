﻿#include "main_app.hpp"

#include <wx/wx.h>
#include <wx/uilocale.h>

namespace {
  // trim from start (in place)
  static inline void StartTrim(std::wstring& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
      return !std::isspace(ch);
      }));
  }

  // trim from end (in place)
  static inline void EndTrim(std::wstring& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
      return !std::isspace(ch);
      }).base(), s.end());
  }

  // trim from both ends (in place)
  static inline void Trim(std::wstring& s) {
    StartTrim(s);
    EndTrim(s);
  }
}

wxIMPLEMENT_APP(MyApp);


bool MyApp::OnInit() {
  long ru_lang = wxLANGUAGE_RUSSIAN;
  wxLocale* locale = new wxLocale(ru_lang);

  MyFrame* frame = new MyFrame("Карточки", wxDefaultPosition, wxDefaultSize);
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
  : wxFrame(NULL, wxID_ANY, title, pos, size)
{
  SetupMenu();
  BuildUI();
}

void MyFrame::SetupMenu() {
  wxMenuBar* menu_bar = new wxMenuBar();

  wxMenu* deck_submenu = new wxMenu();

  for (auto it : cards.LoadAllDecks()) {
    auto append_deck = deck_submenu->AppendRadioItem(wxID_ANY, it.second);
    int id = append_deck->GetId();

    deck_menu_id.push_back(std::make_pair(it.first, id));
    this->Bind(wxEVT_MENU, &MyFrame::SelectDeck, this);

    if (it.first == cards.GetCurrentDeckId()) {
      append_deck->Check(true);
    }
    
  }

  wxMenu* options_menu = new wxMenu();

  options_menu->AppendSubMenu(deck_submenu, "&Текущая колода");
  menu_bar->Append(options_menu, "&Опции");

  int id_rename = options_menu->Append(wxID_ANY, "&Переименовать колоду\tCtrl+R")->GetId();
  this->Bind(wxEVT_MENU, &MyFrame::RenameDeck, this, id_rename);

  int id_cards = options_menu->Append(wxID_ANY, "Редактор колоды&\tCtrl+E")->GetId();
  this->Bind(wxEVT_MENU, &MyFrame::EditDeck, this, id_cards);

  int id_create = options_menu->Append(wxID_ANY, "Создать колоду&\tCtrl+N")->GetId();
  this->Bind(wxEVT_MENU, &MyFrame::CreateDeck, this, id_create);

  SetMenuBar(menu_bar);
}

void MyFrame::BuildUI() {

  wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

  wxPanel* card_panel = new wxPanel(this, wxID_ANY);
  
  // themes
  //this->SetBackgroundColour(wxSystemSettings::GetAppearance().IsDark() ? *wxBLACK : wxColor(229, 229, 229));
  //this->question_text->SetBackgroundColour(this->GetBackgroundColour());
  //this->question_text->SetForegroundColour(wxSystemSettings::GetAppearance().IsDark() ? *wxWHITE : *wxBLACK);

  auto title_font = wxFont(wxNORMAL_FONT->GetPointSize() * 1.5, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  auto text_font = wxFont(wxNORMAL_FONT->GetPointSize() + 1, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);

  question = new wxStaticText(card_panel, wxID_ANY, "Вопрос:");
  question->SetFont(title_font);

  question_text = new wxTextCtrl(card_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
  question_text->SetValue("Вопрос появится здесь");

  answer = new wxStaticText(card_panel, wxID_ANY, "Ваш ответ:");
  answer->SetFont(title_font);

  answer_text = new wxTextCtrl(card_panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
  answer_text->SetHint(" Напишите ответ...");

  checker = new wxStaticText(card_panel, wxID_ANY, "       ");
  checker->SetFont(text_font);

  auto quest_button = new wxButton(card_panel, quest_id, "Случайный вопрос");
  auto check_button = new wxButton(card_panel, check_id, "Проверить ответ");
  auto ans_button = new wxButton(card_panel, ans_id, "Показать правильный ответ");

  wxFlexGridSizer* card_sizer = new wxFlexGridSizer(2, 10, 10);
  card_sizer->AddGrowableCol(1);
  card_sizer->AddGrowableRow(1);
  card_sizer->SetMinSize(FromDIP(450), FromDIP(300));

  auto empty_text = new wxStaticText(card_panel, wxID_ANY, "");

  card_sizer->Add(question, 0, wxALIGN_LEFT | wxLEFT | wxTOP, 10);
  card_sizer->Add(question_text, 1, wxEXPAND | wxRIGHT | wxTOP, 10);
  card_sizer->Add(answer, 0, wxALIGN_LEFT | wxLEFT, 10);
  card_sizer->Add(answer_text, 1, wxEXPAND | wxRIGHT, 10);
  card_sizer->Add(checker, 0, wxALIGN_CENTER);
  card_sizer->Add(quest_button, 1, wxEXPAND | wxRIGHT, 10);
  card_sizer->Add(new wxStaticText(card_panel, wxID_ANY, ""), 1, wxEXPAND);
  card_sizer->Add(check_button, 1, wxEXPAND | wxRIGHT, 10);
  card_sizer->Add(new wxStaticText(card_panel, wxID_ANY, ""), 1, wxEXPAND);
  card_sizer->Add(ans_button, 1, wxEXPAND | wxRIGHT | wxBOTTOM, 10);

  card_panel->SetSizer(card_sizer);

  main_sizer->Add(card_panel, 1, wxEXPAND);

  SetSizerAndFit(main_sizer);
}

void MyFrame::OnClickQuest(wxCommandEvent&) {
  this->checker->SetLabel("");

  if (DeckEnded()) {
    return;
  }

  if (!first_click) {
    if (checked) {
      cards.EraseCurrentCard();

      answer_text->SetValue("");
      answer_text->SetHint(" Напишите ответ...");

      this->question_text->SetValue(cards.GetQuestion());
    }

    else if (!show || !checked) {
      wxString user_ans_wx = answer_text->GetValue();
      std::wstring user_ans = user_ans_wx.ToStdWstring();

      Trim(user_ans);

      if (user_ans == "") {
        wxMessageBox("Вы не написали ответ!", "Сообщение", wxOK);
      }

      else {
        wxMessageBox("Вы не проверили Ваш ответ!", "Сообщение", wxOK);
      }
    }
  }

  else {
    answer_text->SetValue("");
    answer_text->SetHint(" Напишите ответ...");

    this->question_text->SetValue(cards.GetQuestion());

    first_click = false;
  }

  checked = false;
}

void MyFrame::OnClickCheck(wxCommandEvent&) {
  if (DeckEnded()) {
    return;
  }

  if (!first_click) {
    std::wstring user_ans = answer_text->GetValue().ToStdWstring();
    std::wstring expected_ans = cards.GetAnswer();
    Trim(user_ans);

    if (user_ans == "") {
      wxMessageBox("Вы не написали ответ!", "Сообщение", wxOK);
    }
    else if (cards.CheckUserAnswer(user_ans, expected_ans)) {
      this->checker->SetLabel("Верно");
      checked = true;

      if (cards.GetCurrentDeckSize() - 1 == 0) {
        cards.EraseCurrentCard();
      }
    }
    else {
      this->checker->SetLabel("Неверно");
      checked = true;
    }
  }
  
  else {
    wxMessageBox("Вы не получили вопрос!", "Сообщение", wxOK);
  }
}

void MyFrame::OnClickAns(wxCommandEvent&) {
  if (DeckEnded()) {
    return;
  }
  
  if (!first_click) {
    show = true;
    checked = true;
    this->answer_text->SetValue(this->cards.GetAnswer());

    return;
  }

  wxMessageBox("Вы не получили вопрос!", "Сообщение", wxOK);
  answer_text->SetValue("");
  answer_text->SetHint(" Напишите ответ...");
}

bool MyFrame::DeckEnded() {
  if (cards.GetCurrentDeckSize() == 0) {
    RefsreshCard();
    wxMessageBox("Текущая колода пуста", "Сообщение", wxOK);

    return true;
  }

  return false;
}

void MyFrame::RenameDeck(wxCommandEvent&) {
  std::wstring current_name = cards.GetCurrentDeckName();
  wxString msg = "Введите новое название для колоды " + current_name;

  rename.Create(this, msg, "Смена названия", "", wxOK);
  rename.SetValue("");

  rename.ShowModal();

  new_name = rename.GetValue();

  std::wstring w_new_name = new_name.ToStdWstring();

  
  if (new_name != "") {
    msg = "Название изменено на " + new_name;

    if (w_new_name == current_name) {
      wxMessageBox("Вы ввели текущее название!", "Внимание", wxOK | wxICON_WARNING);
    }
    else if (wxMessageBox(msg, "Сообщение", wxOK | wxCANCEL) == wxOK) {

      cards.RenameCurrentDeck(cards.GetCurrentDeckId(), w_new_name);
      SetupMenu();
    }
    else {
      wxMessageBox("Смена названия отменена", "Сообщение", wxOK);
    }
  }
}

void MyFrame::SelectDeck(wxCommandEvent& e) {
  RefsreshCard();

  std::wstring selected = L"";
  std::string selected_id = "";

  int id = e.GetId();

  for (auto& it : deck_menu_id) {
    if (id == it.second) {
      selected_id = it.first;
      selected = cards.GetDeckNameFromId(selected_id);

      wxString msg = "Выбрана колода ";
      msg += selected;
      wxMessageBox(msg, "Сообщение", wxOK);

      break;
    }
  }

  cards.SetCurrentDeck(selected_id);
}

void MyFrame::RefsreshCard() {
  first_click = true;
  checked = false;
  show = false;
  this->question_text->SetValue("Вопрос появится здесь");
  this->answer_text->SetValue("");
  this->answer_text->SetHint("Напишите ответ...");
  this->checker->SetLabel("");
}

void MyFrame::OnSelectCard(wxCommandEvent& event) {
  int card_id = event.GetInt();
  std::string deck_id = cards.GetCurrentDeckId();
  wxString card;
  card << card_id;

  if (select_cards->IsChecked(card_id) == false) {
    cards.RemoveFromDeck(card_id, deck_id);
  }

  else {
    cards.AddToDeck(card_id, deck_id);
  }

  cards.SetCurrentDeck(deck_id);
}

void MyFrame::EditDeck(wxCommandEvent&) {
  wxDialog* select_dlg = new wxDialog(this, wxID_ANY, "Выберите карточки", wxDefaultPosition, wxSize(330, 300));

  select_cards = new wxCheckListBox(select_dlg, wxID_ANY, wxDefaultPosition, wxSize(300, 200), 0, NULL, wxLB_ALWAYS_SB);

  int idx = 0;

  for (auto it : cards.GetCardsList()) {
    select_cards->Append(it.second);
    for (auto cur_it : cards.GetCurrentCardsList()) {
      if (it == cur_it) {
        select_cards->Check(idx);
        break;
      }
    }
    select_cards->Bind(wxEVT_CHECKLISTBOX, &MyFrame::OnSelectCard, this);
    idx += 1;
  }

  auto ok_sizer = select_dlg->CreateButtonSizer(wxOK);
  auto ok = new wxButton(select_dlg, wxID_OK);
  ok_sizer->Add(ok, 1, wxALIGN_BOTTOM | wxRIGHT | wxBOTTOM, 10);
  select_dlg->SetSizer(ok_sizer);
  select_dlg->ShowModal();
}

void MyFrame::CreateDeck(wxCommandEvent&) {
  wxString msg = "Введите название для новой колоды";

  wxTextEntryDialog creator(this, msg, "Создание колоды", "", wxOK);
  creator.SetValue("");

  creator.ShowModal();

  new_name = creator.GetValue();

  if (new_name != "") {
    msg = "Создана колода " + new_name;

    if (wxMessageBox(msg, "Сообщение", wxOK | wxCANCEL) == wxCANCEL) {
      msg = "Создание колоды отменено";
      wxMessageBox(msg, "Сообщение");
    }

    else {
      std::wstring w_new_name = new_name.ToStdWstring();
      cards.CreateDeck(w_new_name);

      SetupMenu();
    }
  }
}

void MyFrame::OnUpdateOk(wxUpdateUIEvent& event) {
  event.Enable(false);

  if (!rename.GetValue().IsEmpty()) {
    event.Enable(true);
  }
}