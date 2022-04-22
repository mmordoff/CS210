#include <iostream>
#include <vector>
#include "DataInput.h"

using namespace std;

//Default Constructor
DataInput::DataInput() {
	DataInput::m_userPrompts = {
		"Initial Investment Amount: ",
		"Monthly Deposit: ",
		"Annual Interest: ",
		"Number of Years: "
	};
};

const vector<string>& DataInput::getMUserPrompts() const {
	return m_userPrompts;
}

//getters and setters
double DataInput::getMInitialInvestAmt() const {
	return m_initialInvestAmt;
}

void DataInput::setMInitialInvestAmt(double t_initialInvestAmt) {
	m_initialInvestAmt = t_initialInvestAmt;
}

double DataInput::getMMonthlyDep() const {
	return m_monthlyDep;
}

void DataInput::setMMonthlyDep(double t_monthlyDep) {
	m_monthlyDep = t_monthlyDep;
}

double DataInput::getMAnnualInt() const {
	return m_annualInt;
}

void DataInput::setMAnnualInt(double t_annualInt) {
	m_annualInt = t_annualInt;
}

double DataInput::getMNumYears() const {
	return m_numYears;
}

void DataInput::setMNumYears(double t_numYears) {
	m_numYears = t_numYears;
}

//print header for user input prompt
void DataInput::printHeader() {
	cout << string(36, '*') << endl;
	cout << string(12, '*') << " Data Input " << string(12, '*') << endl;
}

//capture user input and set class members
void DataInput::promptUser() {
	vector<double> depositDetails;
	char quitCmd = 'a'; //indicates infinite loop until the user satisfies input requirements
	
	while (quitCmd != 'q') {
		try {
			//clear any previous unfinished collections of user input
			depositDetails.clear();
			//display interface header
			printHeader();
			//collect user input
			depositDetails = inputCapture();
		}

		//catch any invalid arguments 
		catch (invalid_argument& except) {
			cin.clear();//clear error flags
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clears out the input buffer
			cout << except.what() << endl;
		}

		//check that deposit details vector is full and user decides to continue
		if (depositDetails.size == 4 && enterCheck()) {
			//sets class private members
			setMInitialInvestAmt(depositDetails.at(0));
			setMMonthlyDep(depositDetails.at(1));
			setMAnnualInt(depositDetails.at(2));
			setMNumYears(depositDetails.at(3));

			//exit this class and return to main
			quitCmd = 'q';
		}
	}
}

//loop over user prompts and store responses
vector<double> DataInput::inputCapture() {
	//collect user input and organize in vector
	vector<double>  responses;
	vector<string> prompts = getMUserPrompts();

	for (int i = 0; i < prompts.size(); ++i) {
		string prompt = prompts.at(i);
		double userInput;
		cout << prompt;
		cin >> userInput;

		//check for valid user input
		if (!cin || userInput < 0.01) {
			throw invalid_argument("\n\nAlphabetical characters and amounts less than 0.01 are not allowed. \n\n Please try again.\n\n");
		}

		//add user input to vector
		responses.push_back(userInput);
	}

	return responses;
}

//abstracted method for validating specific enter key presses
bool DataInput::enterCheck() {
	cout << "Press enter to continue . . .  \n\n\n";
	return cin.get() == '\n';
}