#include <ctime>
#include <functional>

#include <gtk/gtk.h>

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

static void activate(GtkApplication* app, gpointer userData)
{
	GtkWidget *window;
	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "GuzekRenderer");
	gtk_window_set_default_size(GTK_WINDOW(window), 1024, 640);
	gtk_widget_show_all(window);
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
   //QApplication a(argc, argv);
   //
   //MainWindow window;
   //window.show();
   //
   //return a.exec();

	GtkApplication* app;
	int32_t status;

	app = gtk_application_new("org.gtk.renderer", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run(G_APPLICATION(app), argc, argv);

	g_object_unref(app);

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
	return status;
}

