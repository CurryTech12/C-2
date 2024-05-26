//This c++ program display a menu that gives the user options for a credit card report
//one option generates a spending.txt which will be the input file into the functions that allows us
//to pull specfic data from it to display or give an output file report from. Some menu functions include 
//showing account information such as credit card information and letting the user pick a certain day 
//inside the spending.txt file to display on the console, as well as see a yearly report with a bar graph
//and a monthly report
//CECS 275 Spring 2024
//@Brandon J
//@Daniel B
//@version 2.3.4 
//Last updatesd 3/17/24 8:00 - 9:06pm
//Copyright no one is allowed to distrbute or copy this code



#include <iostream>
#include <string>
#include <fstream>
#include "myUtlis.h"

using namespace std;
int main(){
    while(true){
        menu();
        string month;
        string NewMonthChosen;
        cout << "Pick an option: " << endl;
        int choice;
        cin >> choice;
        cout << "\n" << endl;
        switch(static_cast<Option>(choice)){
            case Option::NONE:
                break;
            case Option::A:
                accountDetails();
                break;
            case Option::VIEW_MONTH:
                cout << "What Month Would you like to View (Jan)(Feb)(Mar)(Apr)(May)(Jun)(Jul)(Aug)(Sept)(Oct)(Nov)(Dec):" << endl;
                cin >> month;
                monthlySpending(month);
                break;
            case Option:: MONTH_SPEND:
                cout << "What month would you like ex(Jan)(Feb)(Mar)(Nov)(Dec)...etc" << endl;
                cin >> NewMonthChosen;
                monthlyReport(NewMonthChosen);
                break;
            case Option::YEARLY_SPEND:
                yearlySpend();
                break;
            case Option:: YEARLY_AVERAGE:
                yearlyReport();
                break;
            case Option:: SEARCH:
                searchDate();
                break;
            case Option:: Gen_TXT:
                cout << "GENERATING........." << endl;
                generateSpendtxt();
                cout << "GENERATING IS DONE!!!!" << endl;
                break;
            case Option:: EXIT:
                cout << "Thank you for using our program\n";
                exit(0);//when user presses four exits program
                break;
            default:
                break;        
        
       
        }
    }
    return 0;
}