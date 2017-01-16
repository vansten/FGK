#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Image.h"

/**
  Window that displays rendered image.
  */
class DisplayWindow : public wxPanel
{
public:
	explicit DisplayWindow(wxWindow* parent, const wxPoint& pos, const wxSize& size);

	void paintEvent(wxPaintEvent& evt);
	void render(wxDC& dc);

    void setImage(Image* img);

private:
    Image* image;
	wxImage* pixmap;

	wxDECLARE_EVENT_TABLE();
};

#endif // DISPLAYWINDOW_H
