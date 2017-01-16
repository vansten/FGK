#ifndef RENDEREROPTIONS_H
#define RENDEREROPTIONS_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class wxSpinCtrl;
class wxSpinCtrlDouble;

// -----------------------------------------------------------------------------

struct RendererParams
{
    unsigned int    m_numSamples;
    unsigned int    m_numEmittedGlobalPhotons;
    unsigned int    m_numEmittedCausticPhotons;
    int             m_numAssociatedPhotons;
    float           m_streamRadius;
    float           m_globalSearchingRadius;
    unsigned int    m_numSearchedGlobalPhotons;
    float           m_causticSearchingRadius;
    unsigned int    m_numSearchedCausticPhotons;
    int             m_numPhotons;
    int             m_maxReflections;
};

// -----------------------------------------------------------------------------

class StreamRendererOptions : public wxPanel
{
public:
    explicit StreamRendererOptions(wxWindow* parent = nullptr);

    RendererParams getRendererParams() const;

private:
	wxSpinCtrl*       m_numSamples;
	wxSpinCtrl*       m_numEmittedGlobalPhotons;
	wxSpinCtrl*       m_numEmittedCausticPhotons;
	wxSpinCtrl*       m_numAssociatedPhotons;
	wxSpinCtrlDouble* m_streamRadius;
	wxSpinCtrlDouble* m_globalSearchingRadius;
	wxSpinCtrl*       m_numSearchedGlobalPhotons;
	wxSpinCtrlDouble* m_causticSearchingRadius;
	wxSpinCtrl*       m_numSearchedCausticPhotons;
	wxSpinCtrl*       m_maxReflections;
};

// -----------------------------------------------------------------------------

class PhotonMapRendererOptions : public wxPanel
{
public:
    explicit PhotonMapRendererOptions(wxWindow* parent = nullptr);

    RendererParams getRendererParams() const;

private:
	wxSpinCtrl*       m_numSamples;
	wxSpinCtrl*       m_numEmittedGlobalPhotons;
	wxSpinCtrl*       m_numEmittedCausticPhotons;
};

// -----------------------------------------------------------------------------

class PhotonMapVisualizerOptions : public wxPanel
{
public:
    explicit PhotonMapVisualizerOptions(wxWindow* parent = nullptr);

    RendererParams getRendererParams() const;

private:
	wxSpinCtrl*       m_numPhotons;
	wxSpinCtrl*       m_maxReflections;
};

// -----------------------------------------------------------------------------

class StreamVisualizerOptions : public wxPanel
{
public:
    explicit StreamVisualizerOptions(wxWindow* parent = nullptr);

    RendererParams getRendererParams() const;

private:
	wxSpinCtrl*       m_numAssociatedPhotons;
	wxSpinCtrlDouble* m_streamRadius;
	wxSpinCtrl*       m_numPhotons;
	wxSpinCtrl*       m_maxReflections;
};

// -----------------------------------------------------------------------------

#endif // RENDEREROPTIONS_H
