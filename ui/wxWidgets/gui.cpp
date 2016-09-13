#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "../../lib/Calculator.H"

class MyApp: public wxApp
{
    public:
        virtual bool OnInit();
};

class MyFrame: public wxFrame
{
    public:
        MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
        wxTextCtrl *binDisplay;
        wxTextCtrl *decDisplay;
        wxTextCtrl *hexDisplay;
    private:
        Calculator *calculator;
        void OnBinTextChange(wxCommandEvent& event);
        void OnDecTextChange(wxCommandEvent& event);
        void OnHexTextChange(wxCommandEvent& event);
        void OnEnter(wxCommandEvent& event);
        wxDECLARE_EVENT_TABLE();
};

enum
{
    TEXT_bin = wxID_HIGHEST+1,
    TEXT_dec = wxID_HIGHEST+2,
    TEXT_hex = wxID_HIGHEST+3,
};

wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_TEXT(TEXT_bin,MyFrame::OnBinTextChange) 
    EVT_TEXT(TEXT_dec,MyFrame::OnDecTextChange) 
    EVT_TEXT(TEXT_hex,MyFrame::OnHexTextChange) 
    EVT_TEXT_ENTER(TEXT_bin,MyFrame::OnEnter) 
    EVT_TEXT_ENTER(TEXT_dec,MyFrame::OnEnter) 
    EVT_TEXT_ENTER(TEXT_hex,MyFrame::OnEnter) 
wxEND_EVENT_TABLE()
wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
    MyFrame *frame = new MyFrame( "Calculator", wxPoint(50, 50), wxSize(1450, 340) );
    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
        : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
    binDisplay = new wxTextCtrl(this, TEXT_bin, "", wxDefaultPosition, wxSize(450,25), wxTE_RICH | wxTE_RIGHT | wxTE_PROCESS_ENTER ,wxDefaultValidator, wxTextCtrlNameStr);
    decDisplay = new wxTextCtrl(this, TEXT_dec, "", wxDefaultPosition, wxSize(450,25), wxTE_RICH | wxTE_RIGHT | wxTE_PROCESS_ENTER ,wxDefaultValidator, wxTextCtrlNameStr);
    hexDisplay = new wxTextCtrl(this, TEXT_hex, "", wxDefaultPosition, wxSize(450,25), wxTE_RICH | wxTE_RIGHT | wxTE_PROCESS_ENTER ,wxDefaultValidator, wxTextCtrlNameStr);
    
    vbox->Add(binDisplay, 1, wxEXPAND);
    vbox->Add(decDisplay, 1, wxEXPAND);
    vbox->Add(hexDisplay, 1, wxEXPAND);
    
    SetSizerAndFit(vbox);
    std::vector<int> bases;
    bases.push_back(2);
    bases.push_back(10);
    bases.push_back(16);
    calculator = new Calculator(bases);
}

void MyFrame::OnBinTextChange(wxCommandEvent& event)
{
    calculator->updateDisplays(std::string(binDisplay->GetValue().mb_str()), 2);
    decDisplay->ChangeValue(calculator->getDisplayText(10));
    hexDisplay->ChangeValue(calculator->getDisplayText(16));
}

void MyFrame::OnDecTextChange(wxCommandEvent& event)
{
    calculator->updateDisplays(std::string(decDisplay->GetValue().mb_str()), 10);
    binDisplay->ChangeValue(calculator->getDisplayText(2));
    hexDisplay->ChangeValue(calculator->getDisplayText(16));
}

void MyFrame::OnHexTextChange(wxCommandEvent& event)
{
    calculator->updateDisplays(std::string(hexDisplay->GetValue().mb_str()), 16);
    binDisplay->ChangeValue(calculator->getDisplayText(2));
    decDisplay->ChangeValue(calculator->getDisplayText(10));
}

void MyFrame::OnEnter(wxCommandEvent& event)
{
    calculator->toggleAnswerDisplay();
    binDisplay->ChangeValue(calculator->getDisplayText(2));
    decDisplay->ChangeValue(calculator->getDisplayText(10));
    hexDisplay->ChangeValue(calculator->getDisplayText(16));

}
