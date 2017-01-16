#include "MainWindow.h"
#include "Geometry/Sphere.h"
#include "Geometry/Box.h"
#include "Lights/AreaLight.h"
#include "Geometry/CornellBox.h"
//#include "omp.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Geometry/MS3DModel.h"
#include "Geometry/CornellBox.h"

//#include <QTWidgets/QMessageBox>

//MainWindow::MainWindow(QWidget *parent)
//    : QWidget(parent)
//    , m_rendererPanel(new RendererPanel(this))
//{
//
//    setlocale(LC_ALL,"C");
//    //omp_set_dynamic(1);
//    display.resize(512,512);
//    layout = new QHBoxLayout;
//    layout->addWidget(&display);
//
//    layout->addWidget(m_rendererPanel);
//
//    mainLayout = new QVBoxLayout;
//    renderButton = new QPushButton("Render");
//    mainLayout->addLayout(layout);
//    mainLayout->addWidget(renderButton);
//
//    setLayout(mainLayout);
//
//    m_image = new Image(512, 512);
//    display.setImage(m_image);
//
//    connect(renderButton, SIGNAL(clicked()), this, SLOT(renderScene()));
//
//
//
//}

#define WX_ID_RENDERBUTTON 5

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
EVT_BUTTON(WX_ID_RENDERBUTTON, MainWindow::renderScene)
wxEND_EVENT_TABLE()

MainWindow::MainWindow(const wxPoint & pos, const wxSize & size) :
	wxFrame(NULL, wxID_ANY, "GuzekRenderer", pos, size),
	display(new DisplayWindow(this, wxPoint(20, 20), wxSize(512, 512))),
	renderButton(new wxButton(this, WX_ID_RENDERBUTTON, "Render", wxDefaultPosition, wxSize(200, 60))),
	m_rendererPanel(new RendererPanel(this)),
	m_consolePanel(new ConsolePanel(this))
{
	wxBoxSizer* sizerVeryMain = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* sizerMain = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer* sizerPanel = new wxBoxSizer(wxVERTICAL);

	sizerPanel->Add(
		m_rendererPanel,
		wxSizerFlags(0).Align(wxTOP).Border(wxDirection::wxALL, 10)
	);
	sizerPanel->Add(
		renderButton,
		wxSizerFlags(0).Align(wxBOTTOM).Border(wxALL, 10).Center()
	);

	sizerMain->Add(display, wxSizerFlags(wxSHAPED).Align(wxLEFT));

	sizerMain->Add(sizerPanel, wxSizerFlags(0).Align(wxRIGHT));

	m_image = new Image(512, 512);
	display->setImage(m_image);

	sizerVeryMain->Add(sizerMain, wxSizerFlags(0).Align(wxTOP));

	sizerVeryMain->Add(m_consolePanel, wxSizerFlags(1).Align(wxTOP).Expand());

	SetSizerAndFit(sizerVeryMain);

	SetBackgroundColour(*wxWHITE);

	display->Refresh();
}

MainWindow::~MainWindow()
{
	display->Destroy();
	renderButton->Destroy();

    delete m_image;
    m_image = nullptr;
}

void MainWindow::renderScene(wxCommandEvent& ev)
{
    // Setup scene
    Camera camera (Vector3(0.0,0.0,-29.0),
                   Vector3(0.0,0.0,0.0),
                   0.01f, 500.0, 55.0);
    camera.SetImage(m_image);
    //camera.SetResultFileName("output_image");  //default filename of output image, particular rendering methods override it using actual params for filename
    camera.SetPhotonMappingParams(5, 400, 3, 100); //default setup of parameters (searching radius and number of searched photons for global and caustic map


    //SCENA PIRAMIDA Z BOXOW
    /*
    Scene scene;
    Box* box1111 = new Box(Vector3(-4.5,-9,-5),Vector3(2,2,2));
    Box* box2111 = new Box(Vector3(-1.5,-9,-5),Vector3(2,2,2));
    Box* box3111 = new Box(Vector3(1.5,-9,-5),Vector3(2,2,2));
    Box* box4111 = new Box(Vector3(4.5,-9,-5),Vector3(2,2,2));
    Box* box111 = new Box(Vector3(-3,-7,-4),Vector3(2,2,2));
    Box* box211 = new Box(Vector3(0,-7,-4),Vector3(2,2,2));
    Box* box311 = new Box(Vector3(3,-7,-4),Vector3(2,2,2));
    Box* box11 = new Box(Vector3(-1.5,-5,-3),Vector3(2,2,2));
    Box* box21 = new Box(Vector3(1.5,-5,-3),Vector3(2,2,2));
    Box* box4 = new Box(Vector3(0,-3,-2),Vector3(2,2,2));
    ReflectiveMaterial mat;
    RefractiveMaterial mat2(0.45f);
    DiffuseMaterial mat3(Color(1,1,1),Color(1,1,1),Color(0,0,0), 15, 0.0f);
    //cornell box musi byc na poczatku listy geometrii aby przy renderingu (funkcja traceraystream)z listy usuwane byly dwa ostatnie trojkaty sciany frontowej
    scene.AddGeometry(new CornellBox(Vector3(0,0,0), Vector3(20,20,20)));
    box1111->SetMaterial(&mat3);
    box2111->SetMaterial(&mat3);
    box3111->SetMaterial(&mat3);
    box4111->SetMaterial(&mat3);
    box111->SetMaterial(&mat3);
    box211->SetMaterial(&mat3);
    box311->SetMaterial(&mat3);
    box11->SetMaterial(&mat3);
    box21->SetMaterial(&mat3);
    box4->SetMaterial(&mat3);
    scene.AddGeometry(box1111);
    scene.AddGeometry(box2111);
    scene.AddGeometry(box3111);
    scene.AddGeometry(box4111);
    scene.AddGeometry(box111);
    scene.AddGeometry(box211);
    scene.AddGeometry(box311);
    scene.AddGeometry(box11);
    scene.AddGeometry(box21);
    scene.AddGeometry(box4);
    //POINT LIGHT
    //scene.AddLight(new PointLight(Vector3(0, 9.5, -3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f)));
    //AREA LIGHT
    scene.AddLight(new AreaLight(Vector3(0, 9.5, -4),Vector2(3,3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f),4));
    */


    //SCENA DYFUZYJNA
    /*
    Scene scene;
    //Sphere* sphere1 = new Sphere(Vector3(-3,-7,2), 3);
    Sphere* sphere2 = new Sphere(Vector3(4.6,-6.8,-2), 3.5);
    //Sphere* sphere3 = new Sphere(Vector3(-4,-7,-6), 3);
    //Box* box1 = new Box(Vector3(-4,-8,0),Vector3(6,6,6));
    MS3DModel* model = new MS3DModel();
    model->Load("box.ms3d");
    ReflectiveMaterial mat;
    RefractiveMaterial mat2(0.45f);
    DiffuseMaterial mat3(Color(1,1,1),Color(1,1,1),Color(0,0,0), 15, 0.0f);
    //cornell box musi byc na poczatku listy geometrii aby przy renderingu (funkcja traceraystream)z listy usuwane byly dwa ostatnie trojkaty sciany frontowej
    scene.AddGeometry(new CornellBox(Vector3(0,0,0), Vector3(20,20,20)));
    //sphere1->SetMaterial(&mat);
    sphere2->SetMaterial(&mat3);
    //sphere3->SetMaterial(&mat3);
    //box1->SetMaterial(&mat3);
    model->SetMaterial(&mat3);
    model->SetPositionAndScale(Vector3(-4,-7.2,-2), 3);
    //POINT LIGHT
    //scene.AddLight(new PointLight(Vector3(0, 9.5, -3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f)));
    //AREA LIGHT
    scene.AddLight(new AreaLight(Vector3(0, 9.5, -3),Vector2(3,3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f),4));
    //scene.AddGeometry(sphere1);
    //scene.AddGeometry(box1);
    //SFERA DO TESTOW
    scene.AddGeometry(sphere2);    
    //BOX DO TESTOW
    scene.AddGeometry(model);
    */

    //SCENA KAUSTYCZNA DWIE SFERY

    Scene scene;
    Sphere* sphere1 = new Sphere(Vector3(-4.6,-6.8,-2), 3.5);
    Sphere* sphere2 = new Sphere(Vector3(4.6,-6.8,-2), 3.5);

    ReflectiveMaterial mat;
    RefractiveMaterial mat2(0.45f);
    DiffuseMaterial mat3(Color(1,1,1),Color(1,1,1),Color(0,0,0), 15, 0.0f);
    //cornel box musi byc na poczatku listy geometrii aby przy renderingu (funkcja traceraystream)z listy usuwane byly dwa ostatnie trojkaty sciany frontowej
    scene.AddGeometry(new CornellBox(Vector3(0,0,0), Vector3(20,20,20)));
    sphere1->SetMaterial(&mat);
    sphere2->SetMaterial(&mat2);
    scene.AddGeometry(sphere1);
    scene.AddGeometry(sphere2);
    //POINT LIGHT
    //scene.AddLight(new PointLight(Vector3(0, 9.5, -3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f)));
    //AREA LIGHT
    scene.AddLight(new AreaLight(Vector3(0, 9.5, -3),Vector2(3,3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f),4));


    //SCENA KATAKAUSTYCZNA
    /*
    Scene scene;
    ReflectiveMaterial mat1;
    RefractiveMaterial mat2(0.45f);
    DiffuseMaterial mat3(Color(1,1,1),Color(1,1,1),Color(0,0,0), 15, 0.0f);
    //cornel box musi byc na poczatku listy geometrii aby przy renderingu (funkcja traceraystream)z listy usuwane byly dwa ostatnie trojkaty sciany frontowej
    scene.AddGeometry(new CornellBox(Vector3(0,0,0), Vector3(20,20,20)));
    //1 scianka od prawej
    Triangle* t1 = new Triangle(Vector3(2,-10,4), Vector3(0,-10,5), Vector3(0,-2,5));
    Triangle* t2 = new Triangle(Vector3(0,-2,5), Vector3(2,-2,4), Vector3(2,-10,4));
    //2 scianka
    Triangle* t3 = new Triangle(Vector3(0,-10,5), Vector3(-2,-10,5), Vector3(-2,-2,5));
    Triangle* t4 = new Triangle(Vector3(-2,-2,5), Vector3(0,-2,5), Vector3(0,-10,5));
    //3 scianka
    Triangle* t5 = new Triangle(Vector3(-2,-10,5), Vector3(-4,-10,4), Vector3(-4,-2,4));
    Triangle* t6 = new Triangle(Vector3(-4,-2,4), Vector3(-2,-2,5), Vector3(-2,-10,5));
    //4 scianka
    Triangle* t7 = new Triangle(Vector3(-4,-10,4), Vector3(-5,-10,2), Vector3(-5,-2,2));
    Triangle* t8 = new Triangle(Vector3(-5,-2,2), Vector3(-4,-2,4), Vector3(-4,-10,4));
    //5 scianka
    Triangle* t9 = new Triangle(Vector3(-5,-10,2), Vector3(-5,-10,0), Vector3(-5,-2,0));
    Triangle* t10 = new Triangle(Vector3(-5,-2,0), Vector3(-5,-2,2), Vector3(-5,-10,2));
    //6 scianka
    Triangle* t11 = new Triangle(Vector3(-5,-10,0), Vector3(-4,-10,-2), Vector3(-4,-2,-2));
    Triangle* t12 = new Triangle(Vector3(-4,-2,-2), Vector3(-5,-2,0), Vector3(-5,-10,0));
    t1->SetMaterial(&mat1);
    scene.AddGeometry(t1);
    t2->SetMaterial(&mat1);
    scene.AddGeometry(t2);
    t3->SetMaterial(&mat1);
    scene.AddGeometry(t3);
    t4->SetMaterial(&mat1);
    scene.AddGeometry(t4);
    t5->SetMaterial(&mat1);
    scene.AddGeometry(t5);
    t6->SetMaterial(&mat1);
    scene.AddGeometry(t6);
    t7->SetMaterial(&mat1);
    scene.AddGeometry(t7);
    t8->SetMaterial(&mat1);
    scene.AddGeometry(t8);
    t9->SetMaterial(&mat1);
    scene.AddGeometry(t9);
    t10->SetMaterial(&mat1);
    scene.AddGeometry(t10);
    t11->SetMaterial(&mat1);
    scene.AddGeometry(t11);
    t12->SetMaterial(&mat1);
    scene.AddGeometry(t12);
    //POINT LIGHT
    //scene.AddLight(new PointLight(Vector3(0, 9.5, -3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f)));
    //AREA LIGHT
    scene.AddLight(new AreaLight(Vector3(0, 9.5, -3),Vector2(3,3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f),4));
    */

    // SCENA STANFORD BUNNY
    /*
    Scene scene;
    DiffuseMaterial mat3(Color(1,1,1),Color(1,1,1),Color(0,0,0), 15, 0.0f);
    //cornel box musi byc na poczatku listy geometrii aby przy renderingu (funkcja traceraystream)z listy usuwane byly dwa ostatnie trojkaty sciany frontowej
    scene.AddGeometry(new CornellBox(Vector3(0,0,0), Vector3(20,20,20)));
    MS3DModel* model = new MS3DModel();
    model->Load("bunny.ms3d");
    model->SetPositionAndScale(Vector3(-2,-13,-2), 4);
    model->SetMaterial(&mat3);
    scene.AddGeometry(model);
    //POINT LIGHT
    //scene.AddLight(new PointLight(Vector3(0, 9.5, -3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f)));
    //AREA LIGHT
    scene.AddLight(new AreaLight(Vector3(0, 9.5, -3),Vector2(3,3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f),4));
    */

    // SCENA UTAH TEAPOT
    /*
    Scene scene;
    DiffuseMaterial mat3(Color(1,1,1),Color(1,1,1),Color(0,0,0), 15, 0.0f);
    //cornel box musi byc na poczatku listy geometrii aby przy renderingu (funkcja traceraystream)z listy usuwane byly dwa ostatnie trojkaty sciany frontowej
    scene.AddGeometry(new CornellBox(Vector3(0,0,0), Vector3(20,20,20)));
    MS3DModel* model = new MS3DModel();
    model->Load("teapot.ms3d");
    model->SetPositionAndScale(Vector3(0,-10,-2), 5);
    model->SetMaterial(&mat3);
    scene.AddGeometry(model);
    //POINT LIGHT
    //scene.AddLight(new PointLight(Vector3(0, 9.5, -3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f)));
    //AREA LIGHT
    scene.AddLight(new AreaLight(Vector3(0, 9.5, -3),Vector2(3,3),Color(1.0,1.0,1.0),Vector3(1,0.1f,0.0f),4));
    */

    // Render image using selected method
    if (StreamRenderer == m_rendererPanel->renderingMethod()) {
        RendererParams params = m_rendererPanel->getRendererParams();
        camera.SetPhotonMappingParams(params.m_globalSearchingRadius, params.m_numSearchedGlobalPhotons, params.m_causticSearchingRadius, params.m_numSearchedCausticPhotons);
        camera.RenderSceneStream(&scene,
                                 params.m_numSamples,
                                 params.m_numEmittedGlobalPhotons,
                                 params.m_numEmittedCausticPhotons,
                                 params.m_numAssociatedPhotons,
                                 params.m_streamRadius,
                                 params.m_maxReflections);
        m_rendererPanel->updateRenderingTime(camera.renderingTime());
    } else if (PhotonMapRenderer == m_rendererPanel->renderingMethod()) {
        RendererParams params = m_rendererPanel->getRendererParams();
        camera.RenderScene(&scene,
                           params.m_numSamples,
                           params.m_numEmittedGlobalPhotons,
                           params.m_numEmittedCausticPhotons);
        m_rendererPanel->updateRenderingTime(camera.renderingTime());
    } else if (StreamVisualizer == m_rendererPanel->renderingMethod()) {
        RendererParams params = m_rendererPanel->getRendererParams();
        camera.VisualizeStreamPhotonMap(&scene,
                                        params.m_numPhotons,
                                        params.m_maxReflections,
                                        params.m_numAssociatedPhotons,
                                        params.m_streamRadius);
        m_rendererPanel->updateRenderingTime(camera.renderingTime());
    } else if (PhotonMapVisualizer == m_rendererPanel->renderingMethod()) {
        RendererParams params = m_rendererPanel->getRendererParams();
        camera.VisualizePhotonMap(&scene,
                                  params.m_numPhotons,
                                  params.m_maxReflections);
        m_rendererPanel->updateRenderingTime(camera.renderingTime());
    } else {
		wxMessageBox("Wrong rendering method", "Error");
    }

	display->Refresh();
}