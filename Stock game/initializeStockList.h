#ifndef INITIALIZESTOCKLIST_H
#define INITIALIZESTOCKLIST_H

#include<string>
#include<fstream>
#include<vector>

using namespace std;
using std::string;

struct listing{
	string name;
	int min;
	int max;
	double inst;
};

ifstream getFile(string location);
vector<listing> getList(string location);

#endif // !INITIALIZESTOCKLIST_H