#pragma once

#include "wx/wx.h"
#include "cFunctions.h"
#include <string>
#include <vector>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	int nNrFieldWidth = 3, nNrFieldHeight = 3;
	int nOpFieldWidth = 4, nOpFieldHeight = 5;

	wxButton** opButton;
	wxButton** nrButton;
	wxButton* clearButton;
	wxButton* nullButton;
	wxButton* perButton;
	wxButton* bsButton;
	wxButton* eqButton;

	//penis

	wxTextCtrl* textBox;

public:
	void OnNullButtonClicked(wxCommandEvent& evt);
	void OnNumberButtonClicked(wxCommandEvent& evt);
	void OnClearButtonClicked(wxCommandEvent& evt);
	void OnBSButtonClicked(wxCommandEvent& evt);
	void OnPerButtonClicked(wxCommandEvent& evt);
	void OnOpButtonClicked(wxCommandEvent& evt);
	void OnEqButtonClicked(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

