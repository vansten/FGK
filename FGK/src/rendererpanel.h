#ifndef RENDERERPANEL_H
#define RENDERERPANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

//#include <QtWidgets/QWidget>
//#include <QtWidgets/QStackedWidget>
//#include <QtWidgets/QLayout>
//#include <QtWidgets/QComboBox>
//#include <QtWidgets/QLabel>

#include "rendereroptions.h"

enum RenderingMethod {
    StreamRenderer,
    PhotonMapRenderer,
    StreamVisualizer,
    PhotonMapVisualizer
};

/**
 *  @brief Side widget that allows choosing rendering method
 */
class RendererPanel : public wxPanel
{
public:
    //explicit RendererPanel(QWidget *parent = 0);
	explicit RendererPanel(wxWindow* parent = nullptr);

    RendererParams getRendererParams() const;

    RenderingMethod renderingMethod() const;
    
public:
    void onCurrentChanged(wxCommandEvent& event);

    void updateRenderingTime(int time);

private:
	wxChoice*					m_rendererName;
	wxBoxSizer*					m_rendererOptionsSizer;
    //QComboBox*                  m_rendererName;
    //QStackedWidget*             m_rendererOptionsPanel;
    StreamRendererOptions*      m_streamRendererOptions;
    PhotonMapRendererOptions*   m_photonMapRendererOptions;
    StreamVisualizerOptions*    m_streamVisualizerOptions;
    PhotonMapVisualizerOptions* m_photonMapVisualizerOptions;
    //QLabel*                     m_timeLabel;
	wxStaticText*				m_timeLabel;

	wxDECLARE_EVENT_TABLE();
};

#endif // RENDERERPANEL_H
