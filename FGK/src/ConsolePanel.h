#ifndef CONSOLEPANEL_H
#define CONSOLEPANEL_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

class ConsolePanel : public wxTextCtrl
{
protected:
	static ConsolePanel* m_instance;

public:
	static ConsolePanel* Get();

public:
	explicit ConsolePanel(wxWindow* parent = nullptr, wxStandardID id = wxID_ANY);
	~ConsolePanel();

private:
};

ConsolePanel& Logger();

#endif