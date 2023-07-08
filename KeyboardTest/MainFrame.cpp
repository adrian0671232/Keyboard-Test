#include "MainFrame.h"
#include <wx/wx.h>
#include <chrono>
#include <vector>
#include <numeric>

long double curtime() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

std::vector<long double> keyDelays;
long double before;

wxStaticText* lastDelay;
wxStaticText* lastDown;
wxStaticText* lastRelease;
wxStaticText* averageDelayText;
wxStaticText* highestDelayText;
wxStaticText* lowestDelayText;
wxStaticText* keyStrokes;
wxStaticText* info;

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(640, 380), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
    wxPanel* panel = new wxPanel(this);

    wxFont textFont(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    panel->Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyDownEvent, this);
    panel->Bind(wxEVT_KEY_UP, &MainFrame::OnKeyUpEvent, this);

    keyStrokes = new wxStaticText(panel, wxID_ANY, "# of KeyStrokes: ", wxPoint(0, 0), wxDefaultSize, wxALIGN_LEFT);
    keyStrokes->SetFont(textFont);

    lastDown = new wxStaticText(panel, wxID_ANY, "Last Key Down:", wxPoint(0, 25), wxDefaultSize, wxALIGN_LEFT);
    lastDown->SetFont(textFont);

    lastRelease = new wxStaticText(panel, wxID_ANY, "Last Key Up: ", wxPoint(0, 50), wxDefaultSize, wxALIGN_LEFT);
    lastRelease->SetFont(textFont);

    lastDelay = new wxStaticText(panel, wxID_ANY, "Last Delay: ", wxPoint(0, 100), wxDefaultSize, wxALIGN_LEFT);
    lastDelay->SetFont(textFont);

    averageDelayText = new wxStaticText(panel, wxID_ANY, "Average Delay: ", wxPoint(0, 125), wxDefaultSize, wxALIGN_LEFT);
    averageDelayText->SetFont(textFont);

    highestDelayText = new wxStaticText(panel, wxID_ANY, "Highest Delay: ", wxPoint(0, 150), wxDefaultSize, wxALIGN_LEFT);
    highestDelayText->SetFont(textFont);

    lowestDelayText = new wxStaticText(panel, wxID_ANY, "Lowest Delay: ", wxPoint(0, 175), wxDefaultSize, wxALIGN_LEFT);
    lowestDelayText->SetFont(textFont);

    info = new wxStaticText(panel, wxID_ANY, "https://github.com/stevanoac", wxPoint(0, 290), wxDefaultSize, wxALIGN_LEFT);
    info->SetFont(textFont);
}

void MainFrame::OnKeyDownEvent(wxKeyEvent& evt) {
    before = curtime();
    wxChar keyChar = evt.GetUnicodeKey();
    lastDown->SetLabelText(wxString::Format("Last Key Down: %c", keyChar));
}

void MainFrame::OnKeyUpEvent(wxKeyEvent& evt) {
    wxChar keyChar = evt.GetUnicodeKey();
    long double after = curtime();
    long double time = after - before;

    keyDelays.push_back(time);

    long double average = std::accumulate(keyDelays.begin(), keyDelays.end(), 0.0) / keyDelays.size();
    long double lowest = *std::min_element(keyDelays.begin(), keyDelays.end());
    long double largest = *std::max_element(keyDelays.begin(), keyDelays.end());

    lastDelay->SetLabelText(wxString::Format("Last Delay: %.2f ms", time));
    lastRelease->SetLabelText(wxString::Format("Last Key Up: %c", keyChar));
    keyStrokes->SetLabelText(wxString::Format("# of KeyStrokes: %d", keyDelays.size()));
    averageDelayText->SetLabelText(wxString::Format("Average Delay: %.2f ms", average));
    lowestDelayText->SetLabelText(wxString::Format("Lowest Delay: %.2f ms", lowest));
    highestDelayText->SetLabelText(wxString::Format("Highest Delay: %.2f ms", largest));
}
