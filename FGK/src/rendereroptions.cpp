#include "rendereroptions.h"

#include <wx/spinctrl.h>

#define WX_SPINBOX_MAX_SIZE 120

// -----------------------------------------------------------------------------
/*
StreamRendererOptions::StreamRendererOptions(QWidget *parent)
    : QWidget(parent)
    , m_numSamples(new QSpinBox(this))
    , m_numEmittedGlobalPhotons(new QSpinBox(this))
    , m_numEmittedCausticPhotons(new QSpinBox(this))
    , m_numAssociatedPhotons(new QSpinBox(this))
    , m_streamRadius(new QDoubleSpinBox(this))
    , m_globalSearchingRadius(new QDoubleSpinBox(this))
    , m_numSearchedGlobalPhotons(new QSpinBox(this))
    , m_causticSearchingRadius(new QDoubleSpinBox(this))
    , m_numSearchedCausticPhotons(new QSpinBox(this))
    , m_maxReflections(new QSpinBox(this))
{
    // setup input widgets
    m_numSamples->setMinimum(0);
    m_numSamples->setMaximum(100000);
    m_numSamples->setValue(1);

    m_numEmittedGlobalPhotons->setMinimum(0);
    m_numEmittedGlobalPhotons->setMaximum(2000000);
    m_numEmittedGlobalPhotons->setValue(1000);

    m_numEmittedCausticPhotons->setMinimum(0);
    m_numEmittedCausticPhotons->setMaximum(100000);
    m_numEmittedCausticPhotons->setValue(0);

    m_numAssociatedPhotons->setMinimum(0);
    m_numAssociatedPhotons->setMaximum(100000);
    m_numAssociatedPhotons->setValue(10);

    m_streamRadius->setMinimum(0.001);
    m_streamRadius->setMaximum(10000.0);
    m_streamRadius->setValue(5.0);

    m_globalSearchingRadius->setMinimum(0.001);
    m_globalSearchingRadius->setMaximum(10000.0);
    m_globalSearchingRadius->setValue(3.0);

    m_numSearchedGlobalPhotons->setMinimum(0);
    m_numSearchedGlobalPhotons->setMaximum(100000);
    m_numSearchedGlobalPhotons->setValue(100);

    m_causticSearchingRadius->setMinimum(0.001);
    m_causticSearchingRadius->setMaximum(10000.0);
    m_causticSearchingRadius->setValue(1.0);

    m_numSearchedCausticPhotons->setMinimum(0);
    m_numSearchedCausticPhotons->setMaximum(100000);
    m_numSearchedCausticPhotons->setValue(100);

    m_maxReflections->setMinimum(0);
    m_maxReflections->setMaximum(100000);
    m_maxReflections->setValue(4);

    // layout them
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Number of samples"),0,0);
    layout->addWidget(m_numSamples,0,1);
    layout->addWidget(new QLabel("Number of emitted photon streams"),1,0);
    layout->addWidget(m_numEmittedGlobalPhotons,1,1);
    layout->addWidget(new QLabel("Number of emitted caustic photons"),2,0);
    layout->addWidget(m_numEmittedCausticPhotons,2,1);
    layout->addWidget(new QLabel("Number of associated photons"),3,0);
    layout->addWidget(m_numAssociatedPhotons,3,1);
    layout->addWidget(new QLabel("Radius of photon stream"),4,0);
    layout->addWidget(m_streamRadius,4,1);
    layout->addWidget(new QLabel("Stream map searching radius"),5,0);
    layout->addWidget(m_globalSearchingRadius,5,1);
    layout->addWidget(new QLabel("Number of searched photon streams"),6,0);
    layout->addWidget(m_numSearchedGlobalPhotons,6,1);
    layout->addWidget(new QLabel("Caustic map searching radius"),7,0);
    layout->addWidget(m_causticSearchingRadius,7,1);
    layout->addWidget(new QLabel("Number of searched caustic photons"),8,0);
    layout->addWidget(m_numSearchedCausticPhotons,8,1);
    layout->addWidget(new QLabel("Number of stream reflections"),9,0);
    layout->addWidget(m_maxReflections,9,1);

    layout->addItem(new QSpacerItem(1,1,
                                    QSizePolicy::Fixed,
                                    QSizePolicy::Expanding),10,0,1,2);
}
*/

StreamRendererOptions::StreamRendererOptions(wxWindow* parent) :
	wxPanel(parent)
	, m_numSamples(new wxSpinCtrl(this))
	, m_numEmittedGlobalPhotons(new wxSpinCtrl(this))
	, m_numEmittedCausticPhotons(new wxSpinCtrl(this))
	, m_numAssociatedPhotons(new wxSpinCtrl(this))
	, m_streamRadius(new wxSpinCtrlDouble(this))
	, m_globalSearchingRadius(new wxSpinCtrlDouble(this))
	, m_numSearchedGlobalPhotons(new wxSpinCtrl(this))
	, m_causticSearchingRadius(new wxSpinCtrlDouble(this))
	, m_numSearchedCausticPhotons(new wxSpinCtrl(this))
	, m_maxReflections(new wxSpinCtrl(this))
{
	// setup input widgets
	m_numSamples->SetMin(0);
	m_numSamples->SetMax(100000);
	m_numSamples->SetValue(1);
	m_numSamples->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numEmittedGlobalPhotons->SetMin(0);
	m_numEmittedGlobalPhotons->SetMax(2000000);
	m_numEmittedGlobalPhotons->SetValue(1000);
	m_numEmittedGlobalPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numEmittedCausticPhotons->SetMin(0);
	m_numEmittedCausticPhotons->SetMax(100000);
	m_numEmittedCausticPhotons->SetValue(0);
	m_numEmittedCausticPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numAssociatedPhotons->SetMin(0);
	m_numAssociatedPhotons->SetMax(100000);
	m_numAssociatedPhotons->SetValue(10);
	m_numAssociatedPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_streamRadius->SetRange(0.001, 10000.0);
	m_streamRadius->SetValue(5.0);
	m_streamRadius->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_globalSearchingRadius->SetRange(0.001, 10000.0);
	m_globalSearchingRadius->SetValue(3.0);
	m_globalSearchingRadius->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numSearchedGlobalPhotons->SetMin(0);
	m_numSearchedGlobalPhotons->SetMax(100000);
	m_numSearchedGlobalPhotons->SetValue(100);
	m_numSearchedGlobalPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_causticSearchingRadius->SetRange(0.001, 10000.0);
	m_causticSearchingRadius->SetValue(1.0);
	m_causticSearchingRadius->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numSearchedCausticPhotons->SetMin(0);
	m_numSearchedCausticPhotons->SetMax(100000);
	m_numSearchedCausticPhotons->SetValue(100);
	m_numSearchedCausticPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_maxReflections->SetMin(0);
	m_maxReflections->SetMax(100000);
	m_maxReflections->SetValue(4);
	m_maxReflections->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	// TODO: Add description to spin ctrls.
	wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 10, 10);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of samples"));
	sizer->Add(m_numSamples);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of emitted photon streams"));
	sizer->Add(m_numEmittedGlobalPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of emitted caustic photons"));
	sizer->Add(m_numEmittedCausticPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of associated photons"));
	sizer->Add(m_numAssociatedPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Radius of photon stream"));
	sizer->Add(m_streamRadius);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Stream map searching radius"));
	sizer->Add(m_globalSearchingRadius);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of searched photon streams"));
	sizer->Add(m_numSearchedGlobalPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Caustic map searching radius"));
	sizer->Add(m_causticSearchingRadius);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of searched caustic photons"));
	sizer->Add(m_numSearchedCausticPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of stream reflections"));
	sizer->Add(m_maxReflections);

	SetSizerAndFit(sizer);
}

RendererParams StreamRendererOptions::getRendererParams() const
{
    //RendererParams params;
	//
    //params.m_numSamples             = m_numSamples->value();
    //params.m_numEmittedGlobalPhotons    = m_numEmittedGlobalPhotons->value();
    //params.m_numEmittedCausticPhotons   = m_numEmittedCausticPhotons->value();
    //params.m_numAssociatedPhotons   = m_numAssociatedPhotons->value();
    //params.m_streamRadius           = m_streamRadius->value();
    //params.m_globalSearchingRadius  = m_globalSearchingRadius->value();
    //params.m_numSearchedGlobalPhotons     = m_numSearchedGlobalPhotons->value();
    //params.m_causticSearchingRadius = m_causticSearchingRadius->value();
    //params.m_maxReflections = m_maxReflections->value();
	
	RendererParams params;

	params.m_numSamples					= m_numSamples->GetValue();
	params.m_numEmittedGlobalPhotons    = m_numEmittedGlobalPhotons->GetValue();
	params.m_numEmittedCausticPhotons   = m_numEmittedCausticPhotons->GetValue();
	params.m_numAssociatedPhotons		= m_numAssociatedPhotons->GetValue();
	params.m_streamRadius				= m_streamRadius->GetValue();
	params.m_globalSearchingRadius		= m_globalSearchingRadius->GetValue();
	params.m_numSearchedGlobalPhotons   = m_numSearchedGlobalPhotons->GetValue();
	params.m_causticSearchingRadius		= m_causticSearchingRadius->GetValue();
	params.m_maxReflections				= m_maxReflections->GetValue();

    return params;
}

// -----------------------------------------------------------------------------

/*
PhotonMapRendererOptions::PhotonMapRendererOptions(QWidget *parent)
    : QWidget(parent)
    , m_numSamples(new QSpinBox(this))
    , m_numEmittedGlobalPhotons(new QSpinBox(this))
    , m_numEmittedCausticPhotons(new QSpinBox(this))
{
    // setup input widgets
    m_numSamples->setMinimum(0);
    m_numSamples->setMaximum(100000);
    m_numSamples->setValue(1);

    m_numEmittedGlobalPhotons->setMinimum(0);
    m_numEmittedGlobalPhotons->setMaximum(1000000);
    m_numEmittedGlobalPhotons->setValue(120); //default 12000

    m_numEmittedCausticPhotons->setMinimum(0);
    m_numEmittedCausticPhotons->setMaximum(1000000);
    m_numEmittedCausticPhotons->setValue(5); //default 5000

    // layout them
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Number of samples"),0,0);
    layout->addWidget(m_numSamples,0,1);
    layout->addWidget(new QLabel("Number of global map photons"),1,0);
    layout->addWidget(m_numEmittedGlobalPhotons,1,1);
    layout->addWidget(new QLabel("Number of caustic map photons"),2,0);
    layout->addWidget(m_numEmittedCausticPhotons,2,1);

    layout->addItem(new QSpacerItem(1,1,
                                    QSizePolicy::Fixed,
                                    QSizePolicy::Expanding),3,0,1,2);
}
*/

PhotonMapRendererOptions::PhotonMapRendererOptions(wxWindow* parent)
	: wxPanel(parent)
	, m_numSamples(new wxSpinCtrl(this))
	, m_numEmittedGlobalPhotons(new wxSpinCtrl(this))
	, m_numEmittedCausticPhotons(new wxSpinCtrl(this))
{
	m_numSamples->SetMin(0);
	m_numSamples->SetMax(100000);
	m_numSamples->SetValue(1);
	m_numSamples->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numEmittedGlobalPhotons->SetMin(0);
	m_numEmittedGlobalPhotons->SetMax(1000000);
	m_numEmittedGlobalPhotons->SetValue(120); //default 12000
	m_numEmittedGlobalPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numEmittedCausticPhotons->SetMin(0);
	m_numEmittedCausticPhotons->SetMax(1000000);
	m_numEmittedCausticPhotons->SetValue(5); //default 5000
	m_numEmittedCausticPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 10, 10);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of samples"));
	sizer->Add(m_numSamples);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of global map photons"));
	sizer->Add(m_numEmittedGlobalPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of caustic map photons"));
	sizer->Add(m_numEmittedCausticPhotons);

	SetSizerAndFit(sizer);
}

RendererParams PhotonMapRendererOptions::getRendererParams() const
{
    //RendererParams params;
	//
    //params.m_numSamples             = m_numSamples->value();
    //params.m_numEmittedGlobalPhotons    = m_numEmittedGlobalPhotons->value();
    //params.m_numEmittedCausticPhotons   = m_numEmittedCausticPhotons->value();

	RendererParams params;

	params.m_numSamples = m_numSamples->GetValue();
	params.m_numEmittedGlobalPhotons = m_numEmittedGlobalPhotons->GetValue();
	params.m_numEmittedCausticPhotons = m_numEmittedCausticPhotons->GetValue();

	return params;
}

// -----------------------------------------------------------------------------

/*
PhotonMapVisualizerOptions::PhotonMapVisualizerOptions(QWidget *parent)
    : QWidget(parent)
    , m_numPhotons(new QSpinBox(this))
    , m_maxReflections(new QSpinBox(this))
{
    // setup input widgets
    m_numPhotons->setMinimum(0);
    m_numPhotons->setMaximum(100000);
    m_numPhotons->setValue(25000);

    m_maxReflections->setMinimum(0);
    m_maxReflections->setMaximum(10000);
    m_maxReflections->setValue(6);

    // layout them
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Number of photons"),0,0);
    layout->addWidget(m_numPhotons,0,1);
    layout->addWidget(new QLabel("Max number of reflections"),1,0);
    layout->addWidget(m_maxReflections,1,1);

    layout->addItem(new QSpacerItem(1,1,
                                    QSizePolicy::Fixed,
                                    QSizePolicy::Expanding),2,0,1,2);
}
*/

PhotonMapVisualizerOptions::PhotonMapVisualizerOptions(wxWindow* parent)
	: wxPanel(parent)
	, m_numPhotons(new wxSpinCtrl(this))
	, m_maxReflections(new wxSpinCtrl(this))
{
	m_numPhotons->SetMin(0);
	m_numPhotons->SetMax(100000);
	m_numPhotons->SetValue(25000);
	m_numPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_maxReflections->SetMin(0);
	m_maxReflections->SetMax(10000);
	m_maxReflections->SetValue(6);
	m_maxReflections->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 10, 10);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of samples"));
	sizer->Add(m_numPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Max number of reflections"));
	sizer->Add(m_maxReflections);

	SetSizerAndFit(sizer);
}

RendererParams PhotonMapVisualizerOptions::getRendererParams() const
{
    RendererParams params;
	
    params.m_numPhotons             = m_numPhotons->GetValue();
    params.m_maxReflections         = m_maxReflections->GetValue();

    return params;
}

// -----------------------------------------------------------------------------

/*
StreamVisualizerOptions::StreamVisualizerOptions(QWidget *parent)
    : QWidget(parent)
    , m_numPhotons(new QSpinBox(this))
    , m_maxReflections(new QSpinBox(this))
    , m_numAssociatedPhotons(new QSpinBox(this))
    , m_streamRadius(new QDoubleSpinBox(this))
{
    // setup input widgets
    m_numPhotons->setMinimum(0);
    m_numPhotons->setMaximum(100000);
    m_numPhotons->setValue(12000);

    m_maxReflections->setMinimum(0);
    m_maxReflections->setMaximum(10000);
    m_maxReflections->setValue(6);

    m_numAssociatedPhotons->setMinimum(-100000);
    m_numAssociatedPhotons->setMaximum(100000);
    m_numAssociatedPhotons->setValue(50);

    m_streamRadius->setMinimum(-10000.0);
    m_streamRadius->setMaximum(10000.0);
    m_streamRadius->setValue(0.5);

    // layout them
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(new QLabel("Number of photons"),0,0);
    layout->addWidget(m_numPhotons,0,1);
    layout->addWidget(new QLabel("Max number of reflections"),1,0);
    layout->addWidget(m_maxReflections,1,1);
    layout->addWidget(new QLabel("Number of associated photons"),2,0);
    layout->addWidget(m_numAssociatedPhotons,2,1);
    layout->addWidget(new QLabel("Radius of photon stream"),3,0);
    layout->addWidget(m_streamRadius,3,1);

    layout->addItem(new QSpacerItem(1,1,
                                    QSizePolicy::Fixed,
                                    QSizePolicy::Expanding),4,0,1,2);
}
*/

StreamVisualizerOptions::StreamVisualizerOptions(wxWindow* parent)
	: wxPanel(parent)
	, m_numPhotons(new wxSpinCtrl(this))
	, m_maxReflections(new wxSpinCtrl(this))
	, m_numAssociatedPhotons(new wxSpinCtrl(this))
	, m_streamRadius(new wxSpinCtrlDouble(this))
{
	// setup input widgets
	m_numPhotons->SetMin(0);
	m_numPhotons->SetMax(100000);
	m_numPhotons->SetValue(12000);
	m_numPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_maxReflections->SetMin(0);
	m_maxReflections->SetMax(10000);
	m_maxReflections->SetValue(6);
	m_maxReflections->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_numAssociatedPhotons->SetMin(-100000);
	m_numAssociatedPhotons->SetMax(100000);
	m_numAssociatedPhotons->SetValue(50);
	m_numAssociatedPhotons->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	m_streamRadius->SetRange(-10000.0, 10000.0);
	m_streamRadius->SetValue(0.5);
	m_streamRadius->SetMaxSize(wxSize(WX_SPINBOX_MAX_SIZE, WX_SPINBOX_MAX_SIZE));

	wxFlexGridSizer* sizer = new wxFlexGridSizer(2, 10, 10);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of samples"));
	sizer->Add(m_numPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Max number of reflections"));
	sizer->Add(m_maxReflections);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Number of associated photons"));
	sizer->Add(m_numAssociatedPhotons);
	sizer->Add(new wxStaticText(this, wxID_ANY, "Radius of photon stream"));
	sizer->Add(m_streamRadius);

	SetSizerAndFit(sizer);
}

RendererParams StreamVisualizerOptions::getRendererParams() const
{
    RendererParams params;
	
    params.m_numAssociatedPhotons   = m_numAssociatedPhotons->GetValue();
    params.m_streamRadius           = m_streamRadius->GetValue();
    params.m_numPhotons             = m_numPhotons->GetValue();
    params.m_maxReflections         = m_maxReflections->GetValue();

    return params;
}

// -----------------------------------------------------------------------------
