#include <wx/wx.h>

class MyApp : public wxApp {
public:
  virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

class MyFrame : public wxFrame {
public:
  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
  void OnClick(wxCommandEvent&);

  wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_BUTTON(wxID_ANY, MyFrame::OnClick)
wxEND_EVENT_TABLE()

bool MyApp::OnInit() {
  MyFrame* frame = new MyFrame("Hello World", wxDefaultPosition, wxDefaultSize);
  frame->Show(true);
  return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(nullptr, wxID_ANY, title, pos, size) {
  wxPanel* panel_top_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
  panel_top_left->SetBackgroundColour(wxColor(238, 233, 207));

  wxPanel* panel_top_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
  panel_top_right->SetBackgroundColour(wxColor(235, 202, 205));

  wxPanel* panel_bottom = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 200));
  panel_bottom->SetBackgroundColour(wxColor(191, 230, 232));

  wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* sizer_top = new wxBoxSizer(wxHORIZONTAL);
  sizer_top->Add(panel_top_left, 1, wxEXPAND | wxTOP | wxBOTTOM | wxRIGHT, 5);
  sizer_top->Add(panel_top_right, 1, wxEXPAND | wxTOP | wxBOTTOM, 5);
  
  auto button = new wxButton(this, wxID_ANY, "Show random question");

  wxBoxSizer* sizer_bottom = new wxBoxSizer(wxHORIZONTAL);
  sizer_bottom->Add(button, 1, wxCENTER | wxALL, 0);
  panel_bottom->SetSizerAndFit(sizer_bottom);

  sizer->Add(sizer_top, 1, wxEXPAND | wxALL, 0);
  sizer->Add(panel_bottom, 1, wxEXPAND);
  /*sizer->Add(sizer_bottom, 1, wxEXPAND | wxALL, 0);
  sizer->Add(button, 0, wxCENTER | wxALL, 0);*/
  SetSizerAndFit(sizer);
}

void MyFrame::OnClick(wxCommandEvent&) {
  std::cout << "haha ne budu!!!!!" << std::endl;
}