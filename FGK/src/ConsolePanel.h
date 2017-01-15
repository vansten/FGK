#ifndef CONSOLEPANEL_H
#define CONSOLEPANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ConsolePanel : public wxPanel
{
protected:
	static ConsolePanel* m_instance;

public:
	static ConsolePanel* Get();

public:
	explicit ConsolePanel(wxWindow* parent = nullptr);
	~ConsolePanel();

	ConsolePanel& operator<<(std::string log);
	ConsolePanel& operator<<(float floatValue);
	ConsolePanel& operator<<(double doubleValue);
	ConsolePanel& operator<<(bool boolValue);
	ConsolePanel& operator<<(int intValue);

private:
	wxStaticText* m_logText;
};

ConsolePanel& Logger();

#endif