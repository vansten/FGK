#include "DisplayWindow.h"

//DisplayWindow::DisplayWindow(QWidget *parent) :
//    QWidget(parent)
//{
//    image=0;
//    pixmap=0;
//}

wxBEGIN_EVENT_TABLE(DisplayWindow, wxPanel)
	EVT_PAINT(DisplayWindow::paintEvent)
wxEND_EVENT_TABLE()

DisplayWindow::DisplayWindow(wxWindow * parent, const wxPoint & pos, const wxSize & size) :
	wxPanel(parent, wxID_ANY, pos, size)
{
	image = nullptr;
	pixmap = nullptr;
}

void DisplayWindow::paintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	render(dc);
}

void DisplayWindow::render(wxDC & dc)
{
	if (pixmap != nullptr)
	{
		unsigned int wh = image->GetWidth()*image->GetHeight();
		for (unsigned int i = 0; i < wh; i++) 
		{
			unsigned int x = i % image->GetWidth();
			unsigned int y = i / image->GetWidth();
			LightIntensity p = image->GetPixel(x, y);
			p*=255;
			if(p.r>255)p.r=255;
			if(p.g>255)p.g=255;
			if(p.b>255)p.b=255;
			pixmap->SetRGB(x, y, p.r, p.g, p.b);
		}

		wxBitmap bitmap(*pixmap);
		dc.DrawBitmap(bitmap, 0, 0);
	}
}

void DisplayWindow::setImage(Image *img) {
	if (image)
	{
        delete pixmap;
	}

    image=img;
	pixmap = new wxImage(img->GetWidth(), img->GetHeight());
	//pixmap = new wxBitmap((const char*)image->pixels, img->GetWidth(), img->GetHeight(), 1);
    //pixmap = new QImage(img->GetWidth(), img->GetHeight(), QImage::Format_RGB32);
    //setMinimumSize(img->GetWidth(), img->GetHeight());
	this->SetMinSize(wxSize(img->GetWidth(), img->GetHeight()));
}

//void DisplayWindow::paintEvent(QPaintEvent *) {
//    QPainter p(this);
//
//
//    if(image) {
//        QRgb* pixels = (QRgb*)pixmap->bits();
//        for(unsigned int i=0;i<image->GetWidth()*image->GetHeight();i++) {
//            LightIntensity p = image->GetPixel(i%image->GetWidth(), i/image->GetWidth());
//            p*=255;
//            if(p.r>255)p.r=255;
//            if(p.g>255)p.g=255;
//            if(p.b>255)p.b=255;
//            pixels[i] = qRgb(p.r, p.g, p.b);
//        }
//        p.drawImage(0, 0, *pixmap);
//    }
//    else {
//        p.fillRect(rect(), Qt::black);
//    }
//}
