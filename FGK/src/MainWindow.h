#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "DisplayWindow.h"
#include "Lights/PointLight.h"
#include "Timer.h"

#include "rendererpanel.h"
#include "ConsolePanel.h"

class MainWindow : public wxFrame
{
public:
	explicit MainWindow(const wxPoint& pos, const wxSize& size);
    ~MainWindow();

public:
    void renderScene(wxCommandEvent& ev);

private:
    DisplayWindow* display;
	wxButton* renderButton;

    Image* m_image;
    Timer timer;

    RendererPanel* m_rendererPanel;
	ConsolePanel* m_consolePanel;

	wxDECLARE_EVENT_TABLE();
};

#endif // MAINWINDOW_H
