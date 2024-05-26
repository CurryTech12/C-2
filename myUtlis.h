#ifndef MY_UTILS_H//defines are header files also called the guards
#define MY_UTILS_H//if else makes this compile once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <set>
#include <map>
#include <cmath>
#include <cfloat>
#include <random>


enum class Option{
    NONE,
    A,
    VIEW_MONTH,
    MONTH_SPEND,
    YEARLY_SPEND,
    YEARLY_AVERAGE,
    SEARCH,
    Gen_TXT,
    EXIT
};
std::string optionToString(Option o);
void menu();
void showBanner();
void cardInformation();
int LuhnFunction(int everyNum, int everyEnd);
void generateSpendtxt();
void accountDetails();
void monthlySpending(std::string monthPicked);
void yearlySpend();
void searchDate();
void monthlyReport();
void yearlyReport();

std::string optionToString(Option o){
    switch(o){
        case Option::NONE:
            return "";
        case Option::A:
            return "Account Information";
       case Option::VIEW_MONTH:
            return "View Monthly spending";
        case Option:: MONTH_SPEND:
            return "Monthly Spending Reports";
        case Option:: YEARLY_SPEND:
            return "View Yearly Spending";
        case Option:: YEARLY_AVERAGE:
            return "Yearly Spending Report Average";
         case Option:: SEARCH:
            return "Search for particular date";
        case Option:: Gen_TXT:
            return "Generate spending.txt";
        case Option:: EXIT:
            return "Exit";
        default:
            return "Invalid Option"; 
    }
}
/*
    Displays the menu
*/
void menu(){
    for(Option op = Option::A; op <= Option::EXIT; op = static_cast<Option>(static_cast<int>(op) + 1)){
        std::cout << static_cast<int>(op)<< ". " << optionToString(op) << std::endl;
    }
}
void cardInformation(){
    int check = 0;
    while(check == 0){
        srand(time(NULL));//randomize the number that we get when generating the credit card
        std::string Number = "23456", NumberResult = "";//string that we pull the numbers from to make that news string
        std::string EveryEnd = "";
        std::string EveryOther = "";
        
        int randNum = rand() % Number.size();//index between the length of the string
        NumberResult += Number[randNum];//now first digit of card will always be in range of 2 - 6
        //for major credit card companies

        std::string NewNumbers = "0123456789";
        std::vector<int> LenghtOfCardDigits_after = {14,15};//picks random number inside this vector
        int LenghtPosistion = rand() % LenghtOfCardDigits_after.size();
        for(int i = 0; i < LenghtOfCardDigits_after[LenghtPosistion]; i++){//then add 15 digits after the first one to the string 0 - 9
            int newRand = rand() % NewNumbers.size();
            NumberResult += NewNumbers[newRand];
        }
        reverse(NumberResult.begin(),NumberResult.end());//reverses the string 

        for(int i = 1; i < NumberResult.size(); i += 2){//this is startin at the end of the reverse line
            EveryEnd += (NumberResult[i]);
        }    
        for(int j = 0; j < NumberResult.size(); j += 2){//this is starting from second to last digit of reverse lined
            EveryOther += (NumberResult[j]);
        }
        int everyNum = stoi(EveryOther);//change the string to an integer type
        int everyEnd = stoi(EveryEnd);
        int combinedReturn;
        combinedReturn = LuhnFunction(everyNum,everyEnd);
        reverse(NumberResult.begin(),NumberResult.end());
        char CheckDigit = NumberResult.at(0);
        if((combinedReturn % 10) == 0 || 1){//if total + total1 divided by 10 == 0 then its a valid credit card number ex.20,10,30,40
            check += 1;
            std::string CardType = "";
            std::vector<std::string> First_name = {"Brandon","Daniel","Kenneth","Asia","David","Taylor","Rusell","Jane",
            "Timothy","Wendy","Eric","Tamanth","Alan","Brian","Diego","Airis"};
            std::vector<std::string> Last_name = {"Jamjampour","Estrella","Nguyen","John","Smith","Brown",
            "Williams","Garcia","Thompson","Thomas","Kim","Bellen"};
            std::vector<std::string> Exp = {"1/30","2/30","3/30","4/30","5/30","6/30","7/30","8/30","9/30","10/30","11/30","12/30"};
            srand(time(NULL));//allows for randomize 
            int Exp_posistion = rand() % Exp.size();//picks random exp date
            int First_name_posistion = rand() % First_name.size();//indexes throught the vector randomly and stores that position as 

            //int in First name posistion
            /*
                Check the first digit and gets that ascii value
                if equal to values through 2-6 CardType is whatever the first digit was
            */
            char FirstChar_Credit = NumberResult.at(0);
            if(FirstChar_Credit == 50 || FirstChar_Credit == 53){
                CardType = "MasterCard";
            }else if(FirstChar_Credit == 54){
                CardType = "Discover";
            }else if(FirstChar_Credit == 51){
                CardType = "American Express";
            }else if(FirstChar_Credit == 52){
                CardType = "Visa";
            }
            int Last_name_posistion = rand() % Last_name.size();//gets a random int posistion of a string name stored int the vector
            std::ofstream output;
            output.open("spending.txt");
            output.close();
            output.open("spending.txt",std::ios::app);//clears any old data inside 
            output << First_name[First_name_posistion] << " " << Last_name[Last_name_posistion] << std::endl;
            output << "Card number: " << NumberResult << "\n" << "Card type: " << CardType << "\n" << "Exp: " << Exp[Exp_posistion] << std::endl;
            output << "Status: Active" << std::endl;
            output << "\n" << "Date" << std::setw(35) << "Category" << std::setw(45) << "Withdrawals" << std::endl;
            output.close();
        }
    }
}
int LuhnFunction(int everyNum, int everyEnd){
    int each,doubled = 0,newEach,sep,combined,total = 0,total1 = 0;
        while(everyNum != 0){//check if everyNum has a value in it
            each = everyNum % 10;//get the first digit of everynum and store it into each
            doubled += (2 * each);//double that digit
            if(doubled >= 10){//if digit is greater than 10 we need to split it 10 - 1 + 0
                newEach = doubled % 10;//get the doubled number and split it and get first digit
                total += newEach;//add it to total
                doubled /= 10;//get only the remaining number example 10 we got 0 so now get 1 
                total += doubled;//add it to total
                doubled /= 10;//get rid of any number thats left in doubled so its zero
            }
            if(doubled <= 10){//if the everynum digit is doubled and isnt 10 or < then add it to total
                total += doubled;
                doubled /= 10;//then get rid of it
            }
            everyNum /= 10;//updates everynum to get the next digit
        }
       //change the string of numbers taken from the end of the generated credit card and every other after
        while(everyEnd != 0){
            sep = everyEnd % 10;//get every digit and add it to total1
            total1 += sep;
            everyEnd /= 10;
        }
        combined = total1 + total;
        return combined;
}
struct Date {//define a struct that has month,day, and year in it
    int month;
    int day;
    int year;

    //this sorts the dates by month and day
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;//if month not equal to the other month return that month
        return day < other.day;
    }
};

void generateSpendtxt() {
    std::set<Date> dates; //define date to be in a set
    srand(time(NULL));
    for (int i = 0; i < 365; ++i) {//generates random dates
        int month = rand() % 12 + 1;//pick a random number from 1 to 12 add one to start from 1 not zero
        int day;
        //makes sure that depdning on the month it has the correct max value of days 
        if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
            day = rand() % 31 + 1;// day from 1 to 31
        }else if(month == 2){
            day = rand() % 28 + 1;
        }else{
            day = rand() % 30 + 1;
        }
        int year = 2023;//same year

        Date date;//define struct date
        date.month = month;//update the struct with the random month value
        date.day = day;//update with random day value
        date.year = year;//update with 2024

        dates.insert(date); // insert this into the set
    }
    cardInformation();//calls the card generating
     //std::random_device rd;
     //std::mt19937 gen(rd());

     // Create a uniform distribution between 1 and 10000
     //std::uniform_int_distribution<> dist(1, 100000);
    //std::random_device rd;
    //std::mt19937 gen(rd());
  // Generate a random number
    std::ofstream output("spending.txt",std::ios::app); //puts it in append mode open the file
    for (const Date& date : dates) {
        //for each date creates a rand amount of money until the for loop fails
        int rand_Money = rand() % 100000;
        //std::uniform_int_distribution<> dist(1, 10000000);
        //int rand_Money = rand() % dist(gen);
        double Money = rand_Money / 10.00;
        rand_Money = rand() % 9;
        Money += rand_Money / 100.00;
        std::vector<std::string> Category = {"Utilities","Insurance","Groceries","Entertainment","Mortgage","Travel"};
        //vector of categories to randomly select
        int Category_Position = rand() % Category.size();//this gets it
        //this formats everything into spending.txt
        output << std::setw(2) << std::setfill('0') << std::right << date.month << std::setw(1) << "-" << std::setw(2) << std::setfill('0') << std::right << date.day << std::setw(1) << "-" << std::setw(25) << std::setfill(' ') << std::left << date.year <<
        std::setw(42) << std::setfill(' ') << std::left << Category[Category_Position] << std::setw(1) << std::setfill(' ') << std::left << "$" << std::fixed << std::setprecision(2) << Money << std::endl;
    }

}
void accountDetails(){
    std::ifstream input;
    input.open("spending.txt");
    if(!input){
        std::cout << "FILE CAN NOT BE OPEN!!!" << std::endl;
    }
    while(input){//while some input continue
        std::string line;//define a line to store everything into a string 
        for(int i = 0; i < 5; ++i){//iterate through the first five lines 
            getline(input,line);//get each line store it into line
            std::cout << line << std::endl;//then display it 
        }
        break;//once all 5 iterations done break the while to cont the program
    }
    input.close();
}
void monthlySpending(std::string monthPicked){
    std::ifstream input;
    input.open("spending.txt");
    if(!input){
        std::cout << "File cannot be opened" << std::endl;
    }
    while(input){
        std::string line;//define line as a string
        for(int i = 0; i < 6; ++i){
            getline(input,line);//for the first 6 lines just get them and do nothing
        }
        getline(input,line);//this line gets the next one which is the header
        std::cout << line << std::endl;//prints the header
        while(getline(input,line)){//while get the line when theres some input and store it into line
            char ASCII = line.at(0);//get the ascii value of line at posistion 0 with at function
            if(ASCII == 48 && (monthPicked == "Jan" || monthPicked == "jan")){//if zero and jan
                char ASCII_NExt = line.at(1);//peak the next position to confirm its 01
                if(ASCII_NExt == 49){//if one 
                    std::cout << line << std::endl;//we print out that line and while keeps going until it fails
                }
                /*
                    Same structure as before in January except the ASCII value is 
                    different depnding on the month selected
                */
            }else if(ASCII == 48 &&(monthPicked == "Feb" || monthPicked == "feb")){//same as jan just with diff ascii
                char ASCII_NExt = line.at(1);//value
                if(ASCII_NExt == 50){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "mar" || monthPicked == "Mar")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 51){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "Apr" || monthPicked == "apr")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 52){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "May" || monthPicked == "may")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 53){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "Jun" || monthPicked == "jun")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 54){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "Jul" || monthPicked == "jul")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 55){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "Aug" || monthPicked == "aug")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 56){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 48 &&(monthPicked == "Sept" || monthPicked == "sept")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 57){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 49 &&(monthPicked == "Oct" || monthPicked == "oct")){//if ascii is 1 and oct
                char ASCII_NExt = line.at(1);//check next position 1 
                if(ASCII_NExt == 48){//if zero
                    std::cout << line << std::endl;//print out all october spending
                }
            }else if(ASCII == 49 &&(monthPicked == "Nov" || monthPicked == "nov")){// same as oct just diff value
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 49){
                    std::cout << line << std::endl;
                }
            }else if(ASCII == 49 &&(monthPicked == "Dec" || monthPicked == "dec")){
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 50){
                    std::cout << line << std::endl;
                }
            }
        }
        input.close();
        break;
    }
}
void yearlySpend(){
    std::ifstream input;
    std::ofstream output;
    input.open("spending.txt");
    if(!input){
        std::cout << "File cannot be opened" << std::endl;
    }
    while(input){
        std::string line;
        for(int i = 0; i < 6; ++i){//skipp over first 6 lines
            getline(input,line);
        }
        getline(input,line);//output header
        std::cout << line << std::endl;
        while(getline(input,line)){//get the rest of file bc it has the whole years spending
            std::cout << line << std::endl;//print each line
        }
        input.close();
        break;
    }
}
void searchDate(){
    std::cout << "Type in a date you would like to see what you spent in the Year 2023 (mm-dd-2023)" << std::endl;
    std::string searchDate;
    std::cin >> searchDate;
    std::ifstream input;
    input.open("spending.txt");
    std::string date;
    std::string ignore;
    std::string Header = "";
    for(int i = 0; i < 6; ++i){//skips first 6 lines
        getline(input,ignore);
    }
    for(int i = 0; i < 1; ++i){//skips first 6 lines
        getline(input,ignore);
        Header = ignore;
    }
    int flag = 0;
    while(getline(input,date)){
        if(date.find(searchDate) != std::string::npos){//these means if .find doesnt equal to no posistion found
        //means that the user defined string was found inside the file
            std::cout << "\n" << Header << std::endl;
            std::cout << date << std::endl;//print that string if that if statement returns true
            flag += 1;
        }
    }
    if(date.find(searchDate) == std::string::npos && flag == 0){//these means if .find doesnt find a position matching 
        std::cout << "Zero dollars was spent on this day" << std::endl;
        }
}
void monthlyReport(std::string Picked) {
    std::map<std::string,double> Cat;//make a map that has string and double in it for the cateogry and amount total for that cateogry
    std::string Temp,Double,Name = "",Card = "";
    double amount = 0,total = 0,month_avg = 0,monthavgNew = 0;
    std::ifstream input;
    std::ofstream output,output1;
    input.open("spending.txt");
    std::string FileName = "";
    std::string FileName1 = "";
    std::string FileCap = "";
    output.open(" .txt");//opens a file not named anything
    std::string line,skip;
    int month;
    if(!input){
        std::cout << "File failed to open" << std::endl;
    }
    for(int i = 0; i < 1; ++i){//output name lines
        getline(input,skip);
        Name = skip;//stores the first line into the string name
    }
    for(int i = 0; i < 1; ++i){//credit card info lines
        getline(input,skip);
        Card = skip;//stores card info into another string that i call later ThiS IS YOU DANIEL
        //use the string and mainuplate it before so blur it out
    }
    output.close();
    for(int i = 0; i < 5; ++i){//skipp over first 7 lines
        getline(input,skip);
    }
    while(getline(input,line) && line != ""){//while get the line when theres some input and store it into line
            char ASCII = line.at(0);//get the ascii value of line at posistion 0 with at function
            if(ASCII == 48 && (Picked == "Jan" || Picked == "jan")){//if zero and jan
                FileCap = "January";
                FileName = "january";
                char ASCII_NExt = line.at(1);//peak the next position to confirm its 01
                if(ASCII_NExt == 49){//if one 
                   //we print out that line and while keeps going until it fails
                    //get cat
                    ASCII = line.at(31);//sees at pos 31 for the cateogry
                    ASCII_NExt = line.at(74);//withdrawl amount
                    int i = 0;
                    Temp = "";//make these strings both empty
                    Double = "";
                    while(ASCII != 32){//if no space
                        ASCII = line.at(31 + i);//indexes until a space is seen
                        Temp += ASCII;//gets the cateogry until a space is met
                        i += 1;//inc the index
                    }
                    i = 0;
                    while(ASCII_NExt != 46){//no decimal point
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;//grabs the everything in front of decimal number
                        i += 1;//inc index
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));//grabs the next two digits after
                    /*
                        Calc month_avg inside the if statment
                    */
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;//add amount to the map next to Category
                    total += amount;//adds amount to total used later
                }
                /*
                    Once January was made we can just copy paste the same format but change the ASCII value
                    that we are looking for so we can differ between each month
                */
            }else if(ASCII == 48 &&(Picked == "Feb" || Picked == "feb")){//same as jan just with diff ascii
                FileCap = "February";
                FileName = "febuary";
                char ASCII_NExt = line.at(1);//value
                if(ASCII_NExt == 50){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 28;//calculates the average of the month
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "mar" || Picked == "Mar")){
                FileCap = "March";
                FileName = "march";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 51){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "Apr" || Picked == "apr")){
                FileCap = "April";
                FileName = "april";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 52){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 30;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "May" || Picked == "may")){
                FileCap = "May";
                FileName = "may";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 53){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "Jun" || Picked == "jun")){
                FileCap = "June";
                FileName = "june";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 54){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 30;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "Jul" || Picked == "jul")){
                char ASCII_NExt = line.at(1);
                FileCap = "July";
                FileName = "july";
                if(ASCII_NExt == 55){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "Aug" || Picked == "aug")){
                FileCap = "August";
                FileName = "august";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 56){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 48 &&(Picked == "Sept" || Picked == "sept")){
                FileCap = "September";
                FileName = "september";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 57){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 30;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 49 &&(Picked == "Oct" || Picked == "oct")){//if ascii is 1 and oct
                FileCap = "October";
                FileName = "october";
                char ASCII_NExt = line.at(1);//check next position 1 
                if(ASCII_NExt == 48){//if zero
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 49 &&(Picked == "Nov" || Picked == "nov")){// same as oct just diff value
                FileCap = "November";
                FileName = "november";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 49){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 30;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }else if(ASCII == 49 &&(Picked == "Dec" || Picked == "dec")){
                FileCap = "Decemember";
                FileName = "december";
                char ASCII_NExt = line.at(1);
                if(ASCII_NExt == 50){
                    ASCII = line.at(31);
                    ASCII_NExt = line.at(74);
                    int i = 0;
                    Temp = "";
                    Double = "";
                    while(ASCII != 32){
                        ASCII = line.at(31 + i);
                        Temp += ASCII;
                        i += 1;
                    }
                    i = 0;
                    while(ASCII_NExt != 46){
                        ASCII_NExt = line.at(74 + i);
                        Double += ASCII_NExt;
                        i += 1;
                    }
                    amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));
                    month_avg += amount;
                    monthavgNew = month_avg / 31;
                    Cat[Temp] += amount;
                    total += amount;
                }
            }
        }
    /*
        This code gets the highest and lowest cateogry as well as the total money spent for that 
        cateogry
    */
    std::string Expensive = "",Cheap = "";
    double HIGH = 0,LOW = DBL_MAX;
    int K = 0,L = 0,i = 0;
    for (const auto& category : Cat) {//inside the map called Cat which has two things string cateogies and double type for
    //the withdrawal
        if(category.second > HIGH){//if money is greater than HIGH
            HIGH = category.second;//make high equal to the double type value
            Expensive = category.first;//store into the empy string Expensive so we have the cateogry
        }
        /*
            Same as top except getst the lowest
        */
        if(category.second < LOW){
            LOW = category.second;
            Cheap = category.first;
        }
    }
    FileName1 = "monthly_spending_report_" + FileName + ".txt";//puts the file name dep. on month
    const char* fileNameChar = FileName1.c_str();//changes from string to const char
    rename(" .txt", fileNameChar);//renames the previos close .txt to whatever the month is
    /*
        These next two lines clears any content in the file if there is any
    */
    output.open(fileNameChar);
    output.close();
    output.open(fileNameChar,std::ios::app);//opens the file again in append mode adds new stuff to it
    size_t found = Card.find("Card number:");//gets the string card and finds Card number: get the size
    //since we took it by getline
    std::string cardNumber = Card.substr(found + 13);//make new string cardNumber + 13 to skip over the Card Number:
    std::string censor = "";//create empty string
    for(int i = 0; i < cardNumber.length() - 4; i++){//get the length of cardnumber and - 4 
    //to show last four digits adds x to the rest
            censor += "X";//add each X into censor
    }
    std::string lastFourDigits = cardNumber.substr(cardNumber.length() - 4);//length of card - 4 extracts last four digits
    output << Name << "\n" <<  "Card Number: " << censor << lastFourDigits << std::endl;//before we output card we need to get the length to 
    //blur output x and the last fourdigits of the card
    /*
        outputs everyting to the file all expenses highest and lowest as well as stars
    */
    output << "Month: " << FileCap << "\n" << std::endl;//depending on what month pick FileCap equals a string month
    output << "Average Monthly spending: " << "$" << std::fixed << std::setprecision(2) << monthavgNew << std::endl;
    output << "You spent the most in: " << Expensive << " @ " << "$" << HIGH << " " << "\n" << "You spent the least in: " << Cheap << " @ " << "$" << LOW << "\n" << std::endl;
    
    for(const auto& Balls:Cat){
        //outputs the categorys and alligns them to the right
        output << std::setw(15) << std::right << Balls.first << std::setw(1) << std::left; //<< Balls.second << std::endl debug
        for(int i = 0; i < round(Balls.second/total * 100); ++i){//keeps going until the amount is reached for that month which Balls.second has
            output << "*";//outputs the star
        }
        output << std::endl;
    }
    output.close();
}
void yearlyReport(){
    std::ifstream input;
    std::ofstream output;
    std::string skip,line,Double;
    output.open("yearly_spending_report_2023.txt");
    double amount = 0,total = 0,total_avg = 0;
    /*
        Init both arrays to be 0 at indexes 0 - 11
    */
    double month[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//create an array double type month to store the amounts of each month
    int starYear[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//also create an int type array size 12 for the 12 months as well for the stars 
    input.open("spending.txt");
     if(!input){
        std::cout << "File failed to open" << std::endl;
    }
    for(int i = 0; i < 1; ++i){//gets the name of the spending.txt
        getline(input,skip);
        output << skip << std::endl;
    }
    /*
        This is the same blur code from monthspending report
    */
    for(int i = 0; i < 1; ++i){//skipp over first 7 lines
        getline(input,skip);
        size_t found = skip.find("Card number:");//gets the string card and finds Card number: get the size
        //since we took it by getline
        std::string cardNumber = skip.substr(found + 13);//make new string cardNumber + 13 to skip over the Card Number:
        std::string censor = "";//create empty string
        for(int i = 0; i < cardNumber.length() - 4; i++){//get the length of cardnumber and - 4 
        //to show last four digits adds x to the rest
            censor += "X";//add each X into censor
    }
    std::string lastFourDigits = cardNumber.substr(cardNumber.length() - 4);//length of card - 4 extracts last four digits
    output << "Card Number: " << censor << lastFourDigits << std::endl;

    }
    output << "Year: 2023" << "\n" << std::endl;
    for(int i = 0; i < 5; ++i){//skipp over first 7 lines
        getline(input,skip);//gets the line and stores into string and writes over it 
    }
    while(getline(input,line) && line != ""){
        char firstDigit = line.at(0);//see what month it is
        char secondDigit = line.at(1);//sees the next digit to now what month 01..02..etc
        char ASCII = line.at(74);//sees at pos 74 before $ sign
        int i = 0;
        Double = "";//create empty string
        while(ASCII != 46){// when theres not a decimal point
            ASCII = line.at(74 + i); //grabs everything after $ and before decimal point
            Double += ASCII;//stores it into the string Double
            i += 1;//increment the index
            //std::cout << Double << std::endl;debug
        }
        //int TEST = static_cast<int>(firstDigit) - 48; debug
        //int TEST2 = static_cast<int>(secondDigit) - 48; debug
        //std::cout << "First DIGIT " << TEST << "\n" << "Second Digit " << TEST2 << std::endl;debug
        amount = std::stod(Double + line.at(74 + i) + line.at(75 + i));//change from string to double type
        //grabs everything before decimal and then the 2 digits after the decimal point 
        total += amount;//total equals to each amount added up from spending.txt to get the total of year
        total_avg = total;//stores total into a new var called avg
        total_avg = total_avg / 12;//divides it by 12
        month[stoi(std::to_string(static_cast<int>(firstDigit) - 48) + std::to_string(static_cast<int>(secondDigit) - 48)) - 1] += amount;
        //std::cout << "TEST: " << stoi(std::to_string(static_cast<int>(firstDigit) - 48) + std::to_string(static_cast<int>(secondDigit) - 48)) - 1 << " " << amount << std::endl;
    }
    //for(double mo:month){
        //std::cout << mo << std::endl;debug purpose see if it gets the total of the 12 months
    //}
    int monthTrackMost = 0,monthTrackLeast = 0;
    double True = month[0],False = month[0];//init two double type array with the array month at pos [0]
    int size = sizeof(month) / sizeof(month[0]);//this gets the size of the array so we can for loop through it
    for(int i = 0; i < size; ++i){//for loop to loop through the array we created
        if(month[i] > True){//if this month money value in the index is greater than the first month[0]
             True = month[i];//update true to be the higher month at whatever index 
             monthTrackMost = i;//tracks the posistion of the index of the array so we can get the Month as well
             //for the highest spent
        }
        /*
            Same as top except find the lowest spent month
        */
        if(month[i] < False){
            False = month[i];//update false to be the lower value that was stored in the array for that month
            monthTrackLeast = i;//stores the lowest month using the index inside the array
        }
    }
    /*
        This code below allows us to use the array posistion and match it to
        an actual month name like January,February..etc for the highest and lowest month spent
    */
    std::string Month = "";
    std::string MonthLeast = "";
    //lowest month if statements
    if(monthTrackLeast == 0){//monthTractLeast index which we did above equals to a number like 0 - 11
        MonthLeast = "January";//0 is jan, 1 is feb..etc
    }else if(monthTrackLeast == 1){
        MonthLeast = "February";
    }else if(monthTrackLeast == 2){
        MonthLeast = "March";
    }else if(monthTrackLeast == 3){
        MonthLeast = "April";
    }else if(monthTrackLeast == 4){
        MonthLeast = "May";
    }else if(monthTrackLeast == 5){
        MonthLeast = "June";
    }else if(monthTrackLeast == 6){
        MonthLeast = "July";
    }else if(monthTrackLeast == 7){
        MonthLeast = "August";
    }else if(monthTrackLeast == 8){
        MonthLeast = "September";
    }else if(monthTrackLeast == 9){
        MonthLeast = "October";
    }else if(monthTrackLeast == 10){
        MonthLeast = "November";
    }else if(monthTrackLeast == 11){
        MonthLeast = "December";
    }
    //Most spent month if/else statements
    if (monthTrackMost == 0){//uses the monthTractMost value from above
        Month = "January";
    }else if(monthTrackMost == 1){
        Month = "February";
    }else if(monthTrackMost == 2){
        Month = "March";
    }else if(monthTrackMost == 3){
        Month = "April";
    }else if(monthTrackMost == 4){
        Month = "May";
    }else if(monthTrackMost == 5){
        Month = "June";
    }else if(monthTrackMost == 6){
        Month = "July";
    }else if(monthTrackMost == 7){
        Month = "August";
    }else if(monthTrackMost == 8){
        Month = "September";
    }else if(monthTrackMost == 9){
        Month = "October";
    }else if(monthTrackMost == 10){
        Month = "November";
    }else if(monthTrackMost == 11){
        Month = "December";
    }
    /*
        Next two lines outputs the total_avg with two decimal places
        the most spent month which is a string from above like January,Feb..etc
        True,False which is the actual dollar amount which is a double for those months
    */
    output << "Average Yearly spending: " << std::fixed << std::setprecision(2) << "$" <<  total_avg << std::endl;
    output << "You spent the most in: " << Month << " @ " << "$" << True << " " << "\n" << "You spent the least in: " << MonthLeast << " @ " << "$" << False << "\n" << std::endl;
    /*
    Code for the stars for loops 12 times for the 12 months
    rounds the month at each index divdies by the total * 100 so makes 100 stars
    for the 12 months
    */
    for (int i = 0; i < 12; ++i) {
        starYear[i] = round((month[i] / total) * 100);//stores it in the starYear array we made previous
    }
    output << " Jan  Feb  Mar  Apr  May  Jun  Jul  Aug  Sep  Oct  Nov  Dec" << std::endl;//header for bar graph
    bool stars_gazing = false;//init var star_gazing as a bool and makes it false
    while (!stars_gazing) {//while not false 
        stars_gazing = true;//make it true so it will print all the stars out for each month
        for (int i = 0; i < 12; ++i) {//for loop 12 times for the 12 months 0 - 11
            if (starYear[i] > 0) {//starYear at each index has a certain rounded value if > 0 add a star
                output << "  *  ";
                --starYear[i];//sub an index
                stars_gazing = false;//change to false 
            } else {
                output << "     ";//add a space for that month if it has no more each time
            }
        }
        output << std::endl;
    }
    output.close();
}
#endif