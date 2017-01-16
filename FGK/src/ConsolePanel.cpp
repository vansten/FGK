#include "ConsolePanel.h"

#define WX_ID_LOG_TEXT 21

ConsolePanel* ConsolePanel::m_instance = nullptr;

ConsolePanel* ConsolePanel::Get()
{
	//if(!m_instance)
	//{
		//m_instance = new ConsolePanel();
		// a UI control cannot be a singleton this way as it cannot be just spawned without any parent, this would cause an assertion error probably and a memory leak too
		
	//}
	assert(m_instance != nullptr);
	return m_instance;
}

ConsolePanel::ConsolePanel(wxWindow* parent, wxStandardID id)
{
	Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP | wxTE_LEFT | wxUSE_MARKUP);
	assert(m_instance == nullptr);
	m_instance = this;

	SetMinSize(wxSize(0, 128));
	SetBackgroundColour(wxColour(32, 32, 32));
	SetForegroundColour(wxColour(255, 255, 255));
	SetFont(wxFont(10, wxFontFamily::wxFONTFAMILY_MODERN, wxFontStyle::wxFONTSTYLE_NORMAL, wxFontWeight::wxFONTWEIGHT_NORMAL, false, wxEmptyString, wxFONTENCODING_SYSTEM));
	SetEditable(false);
}

ConsolePanel::~ConsolePanel()
{
	if(m_instance && m_instance == this)
	{
		m_instance = nullptr;
	}
}

ConsolePanel& Logger()
{
	static ConsolePanel* cp = (ConsolePanel::Get());
	return *cp;
}
