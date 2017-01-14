#include "rendererpanel.h"

#define WX_ID_RENDERER_NAME 11
#define WX_ID_RENDERER_OPTIONS_STREAM 12
#define WX_ID_RENDERER_OPTIONS_PHOTON 13
#define WX_ID_RENDERER_OPTIONS_STREAM_VISUALIZER 14
#define WX_ID_RENDERER_OPTIONS_PHOTON_VISUALIZER 15
#define WX_ID_TIME_LABEL 16

wxBEGIN_EVENT_TABLE(RendererPanel, wxPanel)
	EVT_CHOICE(WX_ID_RENDERER_NAME, RendererPanel::onCurrentChanged)
wxEND_EVENT_TABLE()

/*
RendererPanel::RendererPanel(QWidget *parent)
    : QWidget(parent)
    , m_rendererName(new QComboBox(this))
    , m_rendererOptionsPanel(new QStackedWidget(this))
    , m_streamRendererOptions(new StreamRendererOptions(this))
    , m_photonMapRendererOptions(new PhotonMapRendererOptions(this))
    , m_streamVisualizerOptions(new StreamVisualizerOptions(this))
    , m_photonMapVisualizerOptions(new PhotonMapVisualizerOptions)
    , m_timeLabel(new QLabel("",this))
{
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    m_timeLabel->setFont(font);

    // Layout stuff
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_rendererName);
    layout->addWidget(m_rendererOptionsPanel);

    layout->addSpacerItem(new QSpacerItem(1,20,
                                          QSizePolicy::Fixed,
                                          QSizePolicy::Fixed));

    layout->addWidget(m_timeLabel);

    layout->addSpacerItem(new QSpacerItem(1,1,
                                          QSizePolicy::Fixed,
                                          QSizePolicy::Expanding));

    // Setup widgets
    m_rendererName->addItem("Stream Rendering");
    m_rendererName->addItem("Photon Map Rendering");
    m_rendererName->addItem("Stream Visualization");
    m_rendererName->addItem("Photon Map Visualization");

    m_rendererOptionsPanel->addWidget(m_streamRendererOptions);
    m_rendererOptionsPanel->addWidget(m_photonMapRendererOptions);
    m_rendererOptionsPanel->addWidget(m_streamVisualizerOptions);
    m_rendererOptionsPanel->addWidget(m_photonMapVisualizerOptions);

    connect(m_rendererName,SIGNAL(currentIndexChanged(int)),
            this,SLOT(onCurrentChanged(int)));
}
*/

RendererPanel::RendererPanel(wxWindow * parent) :
	wxPanel(parent)
	, m_rendererOptionsSizer(new wxBoxSizer(wxVERTICAL))
	, m_streamRendererOptions(new StreamRendererOptions(this))
	, m_photonMapRendererOptions(new PhotonMapRendererOptions(this))
	, m_streamVisualizerOptions(new StreamVisualizerOptions(this))
	, m_photonMapVisualizerOptions(new PhotonMapVisualizerOptions(this))
	, m_timeLabel(new wxStaticText(this, WX_ID_TIME_LABEL, "Rendering time: 0 ms"))
{
	m_timeLabel->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

	wxArrayString rnStrings;
	rnStrings.Add(wxString("Stream Rendering"));
	rnStrings.Add(wxString("Photon Map Rendering"));
	rnStrings.Add(wxString("Stream Visualization"));
	rnStrings.Add(wxString("Photon Map Visualization"));
	m_rendererName = new wxChoice(this, WX_ID_RENDERER_NAME, wxDefaultPosition, wxDefaultSize, rnStrings);
	m_rendererName->SetSelection(0);																		// does not seem to work and I have no idea why.

	m_rendererOptionsSizer->Add(m_streamRendererOptions);
	m_rendererOptionsSizer->Add(m_photonMapRendererOptions);
	m_rendererOptionsSizer->Add(m_streamVisualizerOptions);
	m_rendererOptionsSizer->Add(m_photonMapVisualizerOptions);

	m_rendererOptionsSizer->Hide(1);
	m_rendererOptionsSizer->Hide(2);
	m_rendererOptionsSizer->Hide(3);

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(m_rendererName, wxSizerFlags(1).Expand());
	sizer->AddSpacer(20);
	sizer->Add(m_rendererOptionsSizer, wxSizerFlags().Top().Center());
	sizer->AddSpacer(20);
	sizer->Add(m_timeLabel, wxSizerFlags().Top().Center());
	sizer->AddSpacer(1);

	sizer->SetMinSize(wxSize(350, 0));

	SetSizerAndFit(sizer);
}

void RendererPanel::onCurrentChanged(wxCommandEvent& event)
{
    //m_rendererOptionsPanel->setCurrentIndex(index);
	int index = event.GetInt();
	for (int i = 0; i < 4; ++i)
	{
		if (i == index)
		{
			m_rendererOptionsSizer->Show(static_cast<size_t>(i));
		}
		else
		{
			m_rendererOptionsSizer->Hide(static_cast<size_t>(i));
		}
	}

	SetSizerAndFit(GetSizer());
}

RendererParams RendererPanel::getRendererParams() const
{
    RendererParams params;
	
    if (StreamRenderer == renderingMethod()) {
        params = m_streamRendererOptions->getRendererParams();
    } else if (PhotonMapRenderer == renderingMethod()) {
        params = m_photonMapRendererOptions->getRendererParams();
    } else if (StreamVisualizer == renderingMethod()) {
        params = m_streamVisualizerOptions->getRendererParams();
    } else if (PhotonMapVisualizer == renderingMethod()) {
        params = m_photonMapVisualizerOptions->getRendererParams();
    }
    return params;
}

RenderingMethod RendererPanel::renderingMethod() const
{
	int sel = m_rendererName->GetCurrentSelection();
	if (sel > 0 && sel < 4)
	{
		return static_cast<RenderingMethod>(sel);
	}
	else
	{
		return StreamRenderer;
	}
}

void RendererPanel::updateRenderingTime(int time)
{
    m_timeLabel->SetLabel(wxString::Format("Rendering time: %d ms", time));
}
