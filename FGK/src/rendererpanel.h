#ifndef RENDERERPANEL_H
#define RENDERERPANEL_H

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
class RendererPanel //: public QWidget
{
    //Q_OBJECT
public:
    //explicit RendererPanel(QWidget *parent = 0);

    RendererParams getRendererParams() const;

    RenderingMethod renderingMethod() const;
    
public:
    void onCurrentChanged(int index);

    void updateRenderingTime(int time);

private:
    //QComboBox*                  m_rendererName;
    //QStackedWidget*             m_rendererOptionsPanel;
    StreamRendererOptions*      m_streamRendererOptions;
    PhotonMapRendererOptions*   m_photonMapRendererOptions;
    StreamVisualizerOptions*    m_streamVisualizerOptions;
    PhotonMapVisualizerOptions* m_photonMapVisualizerOptions;
    //QLabel*                     m_timeLabel;
};

#endif // RENDERERPANEL_H
