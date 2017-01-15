#include "ConsolePanel.h"

#define WX_ID_LOG_TEXT 21

ConsolePanel* ConsolePanel::m_instance = nullptr;

ConsolePanel* ConsolePanel::Get()
{
	if(!m_instance)
	{
		m_instance = new ConsolePanel();
	}
	return m_instance;
}

ConsolePanel::ConsolePanel(wxWindow* parent) :
	wxPanel(parent),
	m_logText(new wxStaticText(this, WX_ID_LOG_TEXT, ""))
{
	if(m_instance)
	{
		delete this;
		return;
	}
	m_instance = this;

	m_logText->SetFont(wxFont(10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(m_logText, wxSizerFlags().Expand());
}

ConsolePanel::~ConsolePanel()
{
	if(m_logText)
	{
		delete m_logText;
		m_logText = 0;
	}

	if(m_instance && m_instance == this)
	{
		m_instance = 0;
	}
}

ConsolePanel& ConsolePanel::operator<<(std::string log)
{
	if(m_logText)
	{
		m_logText->SetLabel(m_logText->GetLabel() + wxString(log.c_str()));
	}

	return *this;
}

ConsolePanel& ConsolePanel::operator<<(float floatValue)
{
	return operator<<(std::to_string(floatValue));
}

ConsolePanel& ConsolePanel::operator<<(double doubleValue)
{
	return operator<<(std::to_string(doubleValue));
}

ConsolePanel& ConsolePanel::operator<<(bool boolValue)
{
	return operator<<(std::to_string(boolValue));
}

ConsolePanel& ConsolePanel::operator<<(int intValue)
{
	return operator<<(std::to_string(intValue));
}

ConsolePanel& Logger()
{
	static ConsolePanel* cp = (ConsolePanel::Get());
	return *cp;
}
