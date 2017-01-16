#include <ctime>
#include <functional>

#include <wx/wxprec.h>
#include <wx/app.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "MainWindow.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Ray.h"
#include "Math/Plane.h"
#include "Geometry/Sphere.h"
#include "Geometry/Triangle.h"
#include "Geometry/CornellBox.h"
#include "Camera.h"
#include "Image.h"
#include "Material.h"
#include "Lights/PointLight.h"
#include "Lights/AreaLight.h"
#include "Lights/AmbientLight.h"
#include "Scene.h"
#include "Geometry/MS3DModel.h"
#include "Geometry/Box.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	srand(time(NULL));
	MainWindow* window = new MainWindow(wxPoint(0, 0), wxSize(1024, 600));
	window->Show(true);
	Logger() << "App start";
	return true;
}