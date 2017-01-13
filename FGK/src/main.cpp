#include <ctime>
#include <functional>

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

int main(int argc, char *argv[])
{
	srand(time(NULL));
   //QApplication a(argc, argv);
   //
   //MainWindow window;
   //window.show();
   //
   //return a.exec();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}

