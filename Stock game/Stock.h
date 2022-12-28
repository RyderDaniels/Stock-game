#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <random>

class Stock{
public:
	Stock(listing info);
	~Stock();

	std::string name;
	int value;
	int owned;

	void iterateValue();

private:

	int randRange(int min, int max);
	double randRange(double min, double max);

	int min;
	int max;
	double inst;

};

#endif // !STOCK_H