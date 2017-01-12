#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>

//#include <QtWidgets/QWidget>
//#include <QtWidgets/QPushButton>
#include "DisplayWindow.h"
#include "Lights/PointLight.h"

#include "rendererpanel.h"


class MainWindow : public GtkWidget
{
    //Q_OBJECT
public:
    //explicit MainWindow(QWidget *parent = 0);
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
