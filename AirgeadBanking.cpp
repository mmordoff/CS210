#include <string>
#include <iostream>
#include "DataInput.h"
#include "Calculations.h"
#include "ReportGenerator.h"
#include "InvestmentInfo.h"

using namespace std;

void startApp() {
	bool restart = true;

	try {
		do {
			//prompt user for input and store results
			DataInput userData;
			userData.promptUser();

			//pass the user input on to make calculations
			Calculations calculations;
			InvestmentInfo acctWithNoMonthlyDep = calculations.calculateAnnualInvestment(userData, false);
			InvestmentInfo acctWithMonthlyDep = calculations.calculateAnnualInvestment(userData, true);

			//user report generator objects to relay interest info back to the user
			ReportGenerator balanceAndInterestReport;
			balanceAndInterestReport.reportGenerator(acctWithNoMonthlyDep, acctWithMonthlyDep);

			//promt user to continue or exit program
			restart = balanceAndInterestReport.additionalSessionCheck();
		} while (restart);
	}

	catch (runtime_error& except) {
		cout << "Oops! Something went wrong. Exception: " << except.what() << endl;
	}
}

int main() {
	startApp();
	
	return 0;
}