#include "App.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("Keyboard Test");
    wxIcon icon;
    icon.LoadFile("C:/Users/goat/Pictures/icon.ico", wxBITMAP_TYPE_ICO);
    mainFrame->SetIcon(icon);
    mainFrame->SetClientSize(640, 320);
    mainFrame->Center();
    mainFrame->Show();
    return true;
}
