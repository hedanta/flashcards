#include <wx/wx.h>

#include "card_learner.hpp"

class MyApp : public wxApp {
public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
  void SetupMenu();
  void BuildUI();

  void RefsreshCard();

  void OnClickQuest(wxCommandEvent&);
  void OnClickCheck(wxCommandEvent&);
  void OnClickAns(wxCommandEvent&);
  bool DeckEnded();

  void RenameDeck(wxCommandEvent&);
  void SelectDeck(wxCommandEvent&);

  wxStaticText* question;
  wxStaticText* answer;
  wxStaticText* checker;

  wxTextCtrl* question_text;
  wxTextCtrl* answer_text;

  CardLearner deck;

  std::vector<std::pair<wxString, int>> deck_menu_id;

  bool first_click = true;
  bool checked = false;
  bool show = false;

  wxDECLARE_EVENT_TABLE();
};

enum ButtonId {
  quest_id = wxID_LAST + 2,
  check_id = wxID_LAST,
  ans_id
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(quest_id, MyFrame::OnClickQuest)
EVT_BUTTON(check_id, MyFrame::OnClickCheck)
EVT_BUTTON(ans_id, MyFrame::OnClickAns)
wxEND_EVENT_TABLE()

bool MyApp::OnInit() {
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

  for (auto it : deck.GetAllDecks()) {
    int id = deck_submenu->AppendRadioItem(wxID_ANY, it)->GetId();
    deck_menu_id.push_back(std::make_pair(it, id));
    this->Bind(wxEVT_MENU, &MyFrame::SelectDeck, this);
  }

  wxMenu* select_menu = new wxMenu();
  wxMenu* rename_submenu = new wxMenu();

  int id = rename_submenu->Append(wxID_ANY, "Изменить...\tCtrl+R")->GetId();
  this->Bind(wxEVT_MENU, &MyFrame::RenameDeck, this, id);

  select_menu->AppendSubMenu(rename_submenu, "&Сменить название колоды");
  select_menu->AppendSubMenu(deck_submenu, "&SВыбрать колоду");
  menu_bar->Append(select_menu, "&Опции");

  SetMenuBar(menu_bar);
}

void MyFrame::BuildUI() {
  wxPanel* panel_top_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(350, 200));
  //panel_top_left->SetBackgroundColour(wxColor(238, 233, 207));

  wxPanel* panel_top_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(350, 200));
  //panel_top_right->SetBackgroundColour(wxColor(235, 202, 205));

  wxPanel* panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(350, 200));
  //panel_bottom->SetBackgroundColour(wxColor(201, 224, 232));

  auto title_font = wxFont(wxNORMAL_FONT->GetPointSize() * 1.7, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
  auto text_font = wxFont(wxNORMAL_FONT->GetPointSize() + 1, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_ITALIC, wxFONTWEIGHT_NORMAL);

  question = new wxStaticText(panel_top_left, wxID_ANY, "Вопрос: ");
  question->SetFont(title_font);

  question_text = new wxTextCtrl(panel_top_left, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
  question_text->SetValue("Вопрос будет показан здесь");

  answer = new wxStaticText(panel_top_right, wxID_ANY, "Ваш\nответ: ");
  answer->SetFont(title_font);

  answer_text = new wxTextCtrl(panel_top_right, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
  answer_text->SetHint("Напишите ответ...");

  checker = new wxStaticText(panel_bottom, wxID_ANY, "");
  checker->SetFont(text_font);

  wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* quest_sizer = new wxBoxSizer(wxHORIZONTAL);
  quest_sizer->Add(question, 0, wxCENTER | wxALL, 10);
  quest_sizer->Add(question_text, 1, wxCENTER | wxRIGHT, 40);
  panel_top_left->SetSizer(quest_sizer);

  wxBoxSizer* ans_sizer = new wxBoxSizer(wxHORIZONTAL);
  ans_sizer->Add(answer, 0, wxCENTER | wxALL, 18);
  ans_sizer->Add(answer_text, 1, wxCENTER | wxRIGHT, 40);
  panel_top_right->SetSizer(ans_sizer);

  auto quest_button = new wxButton(panel_bottom, quest_id, "Случайный вопрос");
  auto check_button = new wxButton(panel_bottom, check_id, "Проверить ответ");
  auto ans_button = new wxButton(panel_bottom, ans_id, "Показать правильный ответ");

  wxBoxSizer* checker_sizer = new wxBoxSizer(wxVERTICAL);
  checker_sizer->Add(checker, 0, wxALIGN_LEFT);

  wxBoxSizer* sizer_bottom = new wxBoxSizer(wxVERTICAL);
  sizer_bottom->Add(quest_button, 0, wxCENTER);
  sizer_bottom->Add(check_button, 0, wxCENTER);
  sizer_bottom->Add(ans_button, 0, wxCENTER);

  wxBoxSizer* sizer_bottom_h = new wxBoxSizer(wxHORIZONTAL);
  sizer_bottom_h->Add(sizer_bottom, 1, wxCENTER);
  sizer_bottom_h->Add(checker_sizer, 1, wxCENTER);

  panel_bottom->SetSizerAndFit(sizer_bottom_h);

  main_sizer->Add(panel_top_left, 1, wxEXPAND | wxALL, 0);
  main_sizer->Add(panel_top_right, 1, wxEXPAND | wxALL, 0);
  main_sizer->Add(panel_bottom, 1, wxEXPAND);

  SetSizerAndFit(main_sizer);
}

void MyFrame::OnClickQuest(wxCommandEvent&) {
  this->checker->SetLabel("");

  if (DeckEnded()) {
    return;
  }

  if (!first_click) {
    if (checked) {
      deck.EraseCurrentCard();
      this->answer_text->SetValue("");
      this->question_text->SetValue(deck.GetQuestion());
    }

    else if (!show || !checked) {
      wxString user_ans_wx = answer_text->GetValue();
      std::string user_ans = user_ans_wx.ToStdString();

      if (user_ans == "") {
        this->checker->SetLabel("Вы не написали ответ!");
      }

      else {
        this->checker->SetLabel("Вы не провверили ответ!");
      }
    }
  }

  else {
    this->question_text->SetValue(deck.GetQuestion());
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
    std::wstring expected_ans = deck.GetAnswer();


    if (user_ans == "") {
      this->checker->SetLabel("Вы не написали ответ!");
    }
    else if (deck.CheckUserAnswer(user_ans, expected_ans)) {
      this->checker->SetLabel("Правильный ответ");
      checked = true;

      if (deck.GetDeckSize() - 1 == 0) {
        deck.EraseCurrentCard();
      }
    }
    else {
      this->checker->SetLabel("Неправильный ответ");
      checked = true;
    }
  }
  
  else {
    this->checker->SetLabel("Вы не получили вопрос!");
  }
}

void MyFrame::OnClickAns(wxCommandEvent&) {
  if (DeckEnded()) {
    return;
  }
  
  if (!first_click) {
    show = true;
    checked = true;
    this->checker->SetLabel("Показан правильный ответ");
    this->answer_text->SetValue(this->deck.GetAnswer());

    return;
  }

  this->checker->SetLabel("Вы не получили вопрос!");
  this->answer_text->SetLabel("");
}

bool MyFrame::DeckEnded() {
  if (deck.GetDeckSize() == 0) {
    this->answer_text->SetValue("");
    question_text->SetValue("Вопрос будет показан здесь");
    wxMessageBox("Текущая колода пуста", "Сообщение", wxOK);

    return true;
  }

  return false;
}

void MyFrame::RenameDeck(wxCommandEvent&) {
  wxMessageBox("in progress...", "rename will be here", wxOK);
}

void MyFrame::SelectDeck(wxCommandEvent& e) {
  RefsreshCard();

  std::wstring selected = deck.GetDeckName();
  int id = e.GetId();

  for (auto& it : deck_menu_id) {
    if (id == it.second) {
      selected = it.first;

      wxString msg = "Выбрана колода: ";
      msg += selected;
      this->checker->SetLabel(msg);

      break;
    }
  }

  deck.SetCurrentDeck(selected);
}

void MyFrame::RefsreshCard() {
  first_click = true;
  checked = false;
  show = false;
  this->question_text->SetValue("");
  this->answer_text->SetValue("");
  this->checker->SetLabel("");
}