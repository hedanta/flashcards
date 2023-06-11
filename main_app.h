#include <quiz/quiz_manager.hpp>

#include <wx/wx.h>

/*!
* @brief Основное приложение,
* инициализирующее графический интерфейс
*/
class MyApp : public wxApp {
public:
  virtual bool OnInit();
};

/*!
* @brief Класс, позволяющий создать
* графический интерфейс
*/
class MyFrame : public wxFrame {
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
  void SetupMenu();
  void BuildUI();

  void RefsreshCard();

  void OnUpdateOk(wxUpdateUIEvent&);

  void OnClickQuest(wxCommandEvent&);
  void OnClickCheck(wxCommandEvent&);
  void OnClickAns(wxCommandEvent&);
  void OnSelectCard(wxCommandEvent&);
  bool DeckEnded();

  void RenameDeck(wxCommandEvent&);
  void SelectDeck(wxCommandEvent&);
  void EditDeck(wxCommandEvent&);


  wxStaticText* question;
  wxStaticText* answer;
  wxStaticText* checker;

  wxTextCtrl* question_text;
  wxTextCtrl* answer_text;

  wxTextEntryDialog rename;

  wxCheckListBox* select_cards;
  
  QuizManager cards;

  std::vector<std::pair<std::string, int>> deck_menu_id;

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