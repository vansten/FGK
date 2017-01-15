#include "Image.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

Image::Image()
{
    width = 640;
    height = 480;
    pixels = new LightIntensity[640*480];
}

Image::Image(unsigned int w, unsigned int h) {
    width = w;
    height = h;
    pixels = new LightIntensity[w*h];
}

Image::~Image() {
    delete[] pixels;
}

void Image::SetPixel(unsigned int x, unsigned int y, const LightIntensity &li) {
    if(x<width && y<height) {
        pixels[width*y+x] = li;
    }
}

LightIntensity Image::GetPixel(unsigned int x, unsigned int y) {
    return pixels[y*width+x];
}

void Image::Clear(LightIntensity clearColor) {
    for(unsigned int i=0;i<width*height;i++)
        pixels[i] = clearColor;
}

void Image::SaveToFile(std::string fileName) {

	wxImage resultImage(width, height);
	unsigned char* p = resultImage.GetData();

    for(unsigned int i=0;i<width*height;i++) {
        unsigned int r = pixels[i].r*255;
        unsigned int g = pixels[i].g*255;
        unsigned int b = pixels[i].b*255;

        if(r>255)r=255;
        if(g>255)g=255;
        if(b>255)b=255;


		*p += r;
		p++;
		*p += g;
		p++;
		*p += b;
        p++;
    }

	resultImage.SaveFile(wxString(fileName) + ".png", wxBITMAP_TYPE_PNG);
}
