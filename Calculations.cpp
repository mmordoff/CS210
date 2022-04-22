#include <vector>
#include <iostream>
#include <string>

#include "Calculations.h"
#include "InvestmentInfo.h"

using namespace std;

const long MAX_AMOUNT = 999999999999999;

//Default Constructor
Calculations::Calculations() {}

/*Takes users input and build investment info object that contains user balance and interest info
t_userData
t_monthlyDep
@return investmentSansMonthlyDep*/

InvestmentInfo Calculations::calculateAnnualInvestment(DataInput& t_userData, bool t_monthlyDep) {
	//sort user input
	double openAmt = t_userData.getMInitialInvestAmt();
	double depAmt = t_userData.getMMonthlyDep();
	int intRate = t_userData.getMAnnualInt();
	int numYears = t_userData.getMNumYears();
	vector<int> years;
	vector<vector<double>> yearEndBals;

	//creat an object to store data for report
	InvestmentInfo investmentDetails;
	try {
		//return years as array of ints for display to user
		for (int i = 0; i < numYears; ++i) {
			years.push_back(i + 1);
		}

		if (t_monthlyDep == false) {
			//calculate without monthly deposit
			yearEndBals = annualBalWithInt(openAmt, 0, intRate, numYears);
		}

		else {
			//calculate with monthly deposits
			yearEndBals = annualBalWithInt(openAmt, depAmt, intRate, numYears);
		}

		//populate investment object properties
		investmentDetails.setMYears(years);
		investmentDetails.setMYearEndEarnedInterests(yearEndBals.at(0));
		investmentDetails.setMYearEndBalances(yearEndBals.at(1));

		return investmentDetails;
	}

	catch(runtime_error & except) {
		cout << except.what() << endl;
	}
}

/*calculates annual account balance and earned interest*/
vector<vector<double>> Calculations::annualBalWithInt(double t_openAmount, double t_depositAmount, int t_intRate, int t_years) {
	//local vars to manipulate data for accurate calculations
	vector<vector<double>> balanceAndInts;
	vector<double> annualInterestOnly;
	vector<double> annualBalWithInterest;
	double newBal;
	double yearEndInt;
	double precIntRate = (t_intRate / 100.00) / 12.00;
	double intTracker = 0;
	double intOnly = 0;

	//loop over months in requested time frame and calculate annual balance and earned interest
	for (int i = 0; i < (t_years * 12); ++i) {
		yearEndInt += ((intTracker + t_openAmount) + (t_depositAmount * (i + 1))) * precIntRate;
		//allows tracking earned interest back into principle
		intTracker = yearEndInt;
		if (((i + 1) % 12) == 0) {
			annualInterestOnly.push_back(yearEndInt - intOnly); // add just the annual interest to one vector first
			intOnly = yearEndInt;
			newBal = t_openAmount + (t_depositAmount * (i + 1)) + yearEndInt; //add interest, opening and monthly amount
			annualBalWithInterest.push_back(newBal); //add annual balance with interest to a second vector
		}
	}

	if (newBal > MAX_AMOUNT) {
		throw runtime_error("Unable to complete calculation due to amount is too large!");
	}

	balanceAndInts.push_back(annualInterestOnly); //one vector for tracking interest
	balanceAndInts.push_back(annualBalWithInterest); //one vector for tracking interest and balance

	//pass vectors back to fill out investment info objects
	return balanceAndInts;
}