#include "MainFrame.h"
#include <wx/wx.h>
#include <iostream>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* searchPanel = new wxPanel(this);


    button = new wxButton(searchPanel, wxID_ANY, "Search");
    button->Bind(wxEVT_BUTTON, &MainFrame::OnButtonClicked, this);
    button->SetSize(100,35);
    button->SetPosition(wxPoint(305,0));

    textCtrl = new wxTextCtrl(searchPanel, wxID_ANY, "Input song, album or artist name");
    textCtrl->SetSize(300, 35);


}

void MainFrame::OnButtonClicked(wxCommandEvent &) {
    std::cout<<textCtrl->GetValue()<<std::endl;
    textCtrl->SetValue("");
}
