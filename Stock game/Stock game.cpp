#include "pch.h"
#include <iostream>

const string STOCKLISTINGFILELOCATION = "stocklist.txt";
const int PAGELENGTH = 6;
const int DEFAULTSTARTMONEY = 10000;

void menu(vector<listing> listings);
void gameloop(vector<listing> listings);
vector<Stock> initializestocks(vector<listing> listings);
vector<Stock> iteratestocks(vector<Stock> listings);
void displayinfo(vector<Stock> listings, int page, int day, int money);
int inputstage(int* money, vector<Stock>* stocks, int* page);

int main(){
	vector<listing> listings = getList(STOCKLISTINGFILELOCATION);
	
	menu(listings);

	return 0;
}

void menu(vector<listing> listings){
	loop:
	cout << "===============================" << endl;
	cout << "                               " << endl;
	cout << "@@@@@  @@@  @  @ @ @   @  @@@@@" << endl;
	cout << "  @   @   @ @ @  @ @@  @ @     " << endl;
	cout << "  @   @@@@@ @@   @ @ @ @ @   @@" << endl;
	cout << "  @   @   @ @ @  @ @  @@ @    @" << endl;
	cout << "  @   @   @ @  @ @ @   @  @@@@@" << endl;
	cout << "                               " << endl;
	cout << " @@@  @@@@@   @@@    @@@@  @  @" << endl;
	cout << "@       @    @   @  @      @ @ " << endl;
	cout << " @@@    @    @   @  @      @@  " << endl;
	cout << "    @   @    @   @  @      @ @ " << endl;
	cout << " @@@    @     @@@    @@@@  @  @" << endl;
	cout << "                               " << endl;
	cout << "===============================" << endl;
	cout << "Press 1 to play" << endl;
	cout << "Press 2 to exit" << endl;
	cout << ">";
	int x;
	tryagain:
	cin >> x;
	cout << "==========" << endl;
	switch(x){
	case 1:
		gameloop(listings);
		goto loop;
	case 2:
		return;
	default:
		cout << "Invalid" << endl;
		cout << "==========" << endl;
		goto tryagain;
	}
}

void gameloop(vector<listing> listings){
	vector<Stock> stocks = initializestocks(listings);

	int day = 1;
	int page = 1;
	int money = DEFAULTSTARTMONEY;

	int code; // To determine next course of action, 0 for next day, 1 for refresh, or 2 for exit

	while(true){
		refresh:
		displayinfo(stocks, page, day, money);

		code = inputstage(&money, &stocks, &page);

		if(code == 1) goto refresh;
		if(code == 2) return;

		stocks = iteratestocks(stocks);
		day++;
	}
}

vector<Stock> initializestocks(vector<listing> listings){ // Turn the listings into Stock objects with a value
	vector<Stock> x;
	for(const auto& item : listings){
		x.push_back(Stock(item));
	}
	return x;
}

vector<Stock> iteratestocks(vector<Stock> listings){ // Change the values according to their properties
	for(auto& item : listings){
		item.iterateValue();
	}
	return listings;
}

void displayinfo(vector<Stock> listings, int page, int day, int money){ // Start of the main screen, showing the stock listings POSSIBILITY FOR PAGE MUST ALREADY BE FIGURED OUT

	cout << "Day " << day << endl;
	cout << "$" << money << endl;

	int count = (page - 1) * PAGELENGTH; // The first listing displayed
	for(int i = count; i < count + PAGELENGTH && i < (signed) listings.size(); i++){ // For each listing up to the page length or the last listing
		cout << i + 1 << ". " << listings[i].name << " " << listings[i].value << endl; // eg. '4. My stock 1000'
		if(listings[i].owned != 0){
			cout << "   You own: " << listings[i].owned << endl;
		}
	}
	cout << "==========" << endl;
	return;
}

int inputstage(int* money, vector<Stock>* stocks, int* page){ // Return 0 for next day, 1 for refresh, or 2 for exit

	double x = (double)(stocks->size()) / PAGELENGTH; // For case 2
	int num; // For case 3

	int input;
	cout << "1: prev. page" << endl;
	cout << "2: next page" << endl;
	cout << "3: buy/sell stock" << endl;
	cout << "4: next day" << endl;
	cout << "5: quit game" << endl;
	wronginput:
	cout << ">";
	cin >> input;
	cout << "==========" << endl;

	switch(input){
	case 1: // Back a page
		if(*page != 1){
			*page = *page - 1;
		}
		return 1;
	case 2: // Forward a page
		if(*page < x){
			*page = *page + 1;
		}
		return 1;
	case 3: // Stock exchanging

		cout << "Select a stock by it's number" << endl << ">";
		cin >> num;
		cout << "==========" << endl;
		cout << num << ". " << stocks->at(num - 1).name << endl;
		cout << "Worth: " << stocks->at(num - 1).value << endl;
		cout << "Money: " << *money << endl;
		cout << "You have: " << stocks->at(num - 1).owned << endl;
		cout << "Buy(1) or sell?(2)" << endl << ">";
		cin >> input;
		cout << "==========" << endl;
		if(input == 1){
			if(*money < stocks->at(num - 1).value){
				cout << "You can't even afford one!" << endl << "==========" << endl;
				return 1;
			}
			cout << "How much?" << endl << ">";
			cin >> input;
			if(input * stocks->at(num - 1).value <= *money && input != 0){
				*money -= input * stocks->at(num - 1).value;
				stocks->at(num - 1).owned += input;
				cout << "Success!" << endl << "==========" << endl;
			} else{
				cout << "Error" << endl << "==========" << endl;
			}
		} else if(input == 2){
			if(stocks->at(num - 1).owned == 0){
				cout << "You have none to sell" << endl << "==========" << endl;
				return 1;
			}
			cout << "How much?" << endl << ">";
			cin >> input;
			if(input <= stocks->at(num - 1).owned && input != 0){
				stocks->at(num - 1).owned -= input;
				*money += input * stocks->at(num - 1).value;
				cout << "Success!" << endl << "==========" << endl;
			} else{
				cout << "Error" << endl << "==========" << endl;
			}
		} else{
			cout << "error" << endl << "==========" << endl;
		}

		return 1;
	case 4: // Next day
		return 0;
	case 5: // Quit the game
		return 2;
	default:
		cout << "error" << endl;
		goto wronginput;
	}
}