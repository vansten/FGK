#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "DisplayWindow.h"
#include "Lights/PointLight.h"

#include "rendererpanel.h"


class MainWindow : public wxFrame
{
public:
	explicit MainWindow(const wxPoint& pos, const wxSize& size);
    ~MainWindow();

public:
    void renderScene();

private:
    DisplayWindow display;
    //QVBoxLayout* mainLayout;
    //QHBoxLayout* layout;
    //QPushButton* renderButton;
    Image* m_image;
    //QTimer timer;

    RendererPanel* m_rendererPanel;
};

#endif // MAINWINDOW_H
