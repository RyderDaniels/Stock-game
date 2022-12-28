#include "pch.h"

using namespace std;
using std::string;

/*File list fomatting as follows
Name
Minimum value
Maximum value
Instability (How much the log10 of the value is allowed to go up or down, reletively how much the player stands to win/lose on any given day)
	A space for readability
Next item...
...
...
*/

ifstream getFile(string location){ //Grabs the appropriate file
	ifstream file;
	file.open(location);
	return file;
}

vector<listing> getList(string location){ //Generates the vector containing the stock listing information
	ifstream file = getFile(location); //Grabs file
	
	vector<listing> list; //Creates vector

	listing nextListing; //A listing that gets copied to the list

	while(!file.eof()){ //Until the end of file
		file >> nextListing.name;
		file >> nextListing.min;
		file >> nextListing.max;
		file >> nextListing.inst; //The next listing is read

		list.push_back(nextListing); //The listing is added to the list
	}
	return list;
}