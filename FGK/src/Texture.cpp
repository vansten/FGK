#include "Texture.h"
#include <wx/wfstream.h>

Texture::Texture() {
    image=0;
    width=0;
    height=0;
}

Texture::Texture(const char* name) {
    image=0;
    Load(name);
}

Texture::Texture(unsigned int w, unsigned int h) {
	image = new wxImage(w, h);
	image->AddHandler(new wxPNGHandler());
    width = w;
    height = h;
}


void Texture::Load(const char* name) {
    if(image)
        delete image;
	wxFileInputStream* str = new wxFileInputStream(wxString(name));
	image = new wxImage(*str);
	delete str;
	width = image->GetWidth();
    height = image->GetHeight();
}

Texture::~Texture() {
    if(image)
        delete image;
}

Color Texture::Sample(float u, float v) {
    if(image) {
        int x, y;
        x = u*width;
        y = v*height;
	
        Color result(float(image->GetRed(x, y))/255,
                     float(image->GetGreen(x, y))/255,
                     float(image->GetBlue(x, y))/255);
	
        return result;
    }
    return Color(1, 1, 1);
}

Color Texture::SampleSpherical(const Vector3 &pos) {
    float theta = acos(pos.y);
    float phi = atan2(pos.x, pos.z);
    if(phi<0.0) {
        phi += 2*M_PI;
    }

    float u = phi*(1.0f/(2*M_PI));
    float v = 1.0f - theta * (1.0f/M_PI);

    return Sample(1.0f-u,1.0f-v);
}

void Texture::SetPixel(unsigned x, unsigned y, Color color) {
	image->SetRGB(x, y, color.r * 255, color.g * 255, color.b * 255);
}

void Texture::SaveToFile(const char*  filename) 
{
	if(!image->SaveFile(wxString(filename), wxBITMAP_TYPE_PNG))
	{
		printf("Cannot save image to file %s", filename);
	}
}


float Texture::GetWhiteToBlackPixelRatio() const {
    float all = width*height;
    float white = 0;

    for(int i=0;i<width*height;i++) {
		unsigned char r = image->GetRed(i%width, i / width);
		unsigned char g = image->GetGreen(i%width, i / width);
		unsigned char b = image->GetBlue(i%width, i / width);
        if(r == 255 && g == 255 && b == 255)
            white++;
    }

    return white/all;
}
