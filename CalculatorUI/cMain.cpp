#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(0, OnNullButtonClicked)
	EVT_BUTTON(1, OnNumberButtonClicked)
	EVT_BUTTON(2, OnNumberButtonClicked)
	EVT_BUTTON(3, OnNumberButtonClicked)
	EVT_BUTTON(4, OnNumberButtonClicked)
	EVT_BUTTON(5, OnNumberButtonClicked)
	EVT_BUTTON(6, OnNumberButtonClicked)
	EVT_BUTTON(7, OnNumberButtonClicked)
	EVT_BUTTON(8, OnNumberButtonClicked)
	EVT_BUTTON(9, OnNumberButtonClicked)
	EVT_BUTTON(10, OnClearButtonClicked)
	EVT_BUTTON(11, OnBSButtonClicked)
	EVT_BUTTON(12, OnPerButtonClicked)
	EVT_BUTTON(13, OnEqButtonClicked)
	EVT_BUTTON(20, OnOpButtonClicked)
	EVT_BUTTON(21, OnOpButtonClicked)
	EVT_BUTTON(22, OnOpButtonClicked)
	EVT_BUTTON(23, OnOpButtonClicked)
	EVT_BUTTON(25, OnOpButtonClicked)
	EVT_BUTTON(27, OnOpButtonClicked)
	EVT_BUTTON(29, OnOpButtonClicked)
	EVT_BUTTON(31, OnOpButtonClicked)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "CalculatorUI", wxPoint(30, 30), wxSize(306, 570), wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX)
{
	textBox = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 10), wxSize(273, 70), wxTE_RIGHT);

	opButton = new wxButton*[20];
	nrButton = new wxButton*[9];
	clearButton = new wxButton(this, 10, "C", wxPoint(10, 100), wxSize(132, 60));
	bsButton = new wxButton(this, 11, "←-", wxPoint(150, 100), wxSize(132, 60));
	nullButton = new wxButton(this, 0, "0", wxPoint(10, 450), wxSize(60, 60));
	perButton = new wxButton(this, 12, ".", wxPoint(80, 450), wxSize(60, 60));
	eqButton = new wxButton(this, 13, "=", wxPoint(150, 450), wxSize(60, 60));

	wxFont font(16, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false);

	textBox->SetFont(font);
	clearButton->SetFont(font);
	bsButton->SetFont(font);
	nullButton->SetFont(font);
	perButton->SetFont(font);
	eqButton->SetFont(font);

	char sNr[3] = "1";
	int nID = 1;

	for (int i = 0; i < nNrFieldWidth; i++)
	{
		for (int j = 0; j < nNrFieldHeight; j++)
		{

			nrButton[j * nNrFieldWidth + i] = new wxButton(this, nID, sNr, wxPoint(10 + i * 70, 380 - j * 70), wxSize(60, 60));
			nrButton[j * nNrFieldWidth + i]->SetFont(font);
			sNr[0] += 3;
			nID += 3;
		}
		sNr[0] -= 8;
		nID -= 8;
	}

	wxString sSymbol;
	sNr[0] = ' ';
	nID = 20;

	for (int i = 0; i < nOpFieldWidth; i++)
	{
		for (int j = 0; j < nOpFieldHeight; j++)
		{
			if (i >= 0 && j == 4 || j <= 4 && i == 3)
			{
				switch (nID)
				{
				case 20:
					sSymbol = "log(x)";
					break;
				case 21:
					sSymbol = "|x|";
					break;
				case 22:
					sSymbol = "√x";
					break;
				case 23:
					sSymbol = "+";
					break;
				case 25:
					sSymbol = "-";
					break;
				case 27:
					sSymbol = "x";
					break;
				case 29:
					sSymbol = "÷";
					break;
				case 31:
					sSymbol = "x^y";
					break;
				}

				opButton[j * nNrFieldWidth + i] = new wxButton(this, nID, sSymbol, wxPoint(10 + i * 70, 450 - j * 70), wxSize(60, 60));
				opButton[j * nNrFieldWidth + i]->SetFont(font);
				nID += 2;
			}
		}
		nID -= 1;
	}


}

cMain::~cMain()
{
	delete[] opButton;
	delete[] nrButton;
}

void cMain::OnNullButtonClicked(wxCommandEvent& evt)
{
	textBox->AppendText(nullButton->GetLabel());
	evt.Skip();
}

void cMain::OnNumberButtonClicked(wxCommandEvent& evt)
{
	int a = evt.GetId();
	a--;
	textBox->AppendText(nrButton[a]->GetLabel());
	evt.Skip();
}

void cMain::OnClearButtonClicked(wxCommandEvent& evt)
{
	textBox->Clear();
	evt.Skip();
}

void cMain::OnBSButtonClicked(wxCommandEvent& evt)
{
	textBox->Remove(textBox->GetLineLength(0) - 1, textBox->GetLineLength(0));
	evt.Skip();
}

void cMain::OnPerButtonClicked(wxCommandEvent& evt)
{
	textBox->AppendText(perButton->GetLabel());
	evt.Skip();
}

void cMain::OnEqButtonClicked(wxCommandEvent& evt)
{
	wxString sResult = textBox->GetLineText(0);
	std::vector<int> nPos;
	char cOperator;
	int vectorCount = 0;
	double* fResult = new double;
	double* fNumber = new double;

	if (isdigit(sResult.at(0)) == false)
		sResult = sResult.SubString(1, sResult.Len());

	for (int i = 0; i < sResult.Len(); i++)
		if (isdigit(sResult.at(i)) == false)
			nPos.push_back(i);

	nPos.push_back(sResult.Len());


	for (int i = 0; i < sResult.Len(); i++)
		if (i == nPos.at(vectorCount))
		{
			sResult.substr(0, i).ToDouble(fResult);
			vectorCount++;
			sResult.SubString(i + 1, nPos.at(vectorCount)).ToDouble(fNumber);
			cOperator = sResult.at(i);
			sResult.Remove(0, nPos.at(vectorCount));
			//sResult = sResult.SubString(i + 1, nPos.at(vectorCount));


			switch (cOperator)
			{
			case '+':
				*fResult += *fNumber;
				break;
			case '-':
				*fResult -= *fNumber;
				break;
			case 'x':
				*fResult *= *fNumber;
				break;
			case '÷':
				*fResult /= *fNumber;
				break;
			case '^':
				*fResult = cFunctions::power(*fResult, *fNumber);
				break;
			case 'l':

				break;
			case '√':
				textBox->Clear();
				*fResult = cFunctions::root2(*fResult);
				break;
			case 'm':
				textBox->Clear();
				textBox->AppendText("|x|");
				*fResult = cFunctions::mod(*fResult);
				break;
			}
			*fNumber = 0.0f;
			
		}


	textBox->Clear();
	textBox->AppendText(eqButton->GetLabel());

	if (*fResult == *(int*)fResult)
		sResult << *(int*)fResult;
	else
		sResult << *fResult;

	textBox->AppendText(sResult);

	*fResult = 0.0f;
	*fNumber = 0.0f;

	delete fResult;
	delete fNumber;

	evt.Skip();
}

void cMain::OnOpButtonClicked(wxCommandEvent& evt)
{

	switch (evt.GetId())
	{
	case 20:
		textBox->AppendText("log(");
		break;
	case 21:
		textBox->AppendText("|x|");
		break;
	case 22:
		textBox->AppendText("√x");
		break;
	case 23:
		textBox->AppendText("+");
		break;
	case 25:
		textBox->AppendText("-");
		break;
	case 27:
		textBox->AppendText("x");
		break;
	case 29:
		textBox->AppendText("÷");
		break;
	case 31:
		textBox->AppendText("^");
		break;
	}
	evt.Skip();
}