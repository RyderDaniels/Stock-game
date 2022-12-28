#include "pch.h"

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> dist(0.0, 1.0);

Stock::Stock(listing info)
	:name(info.name), min(info.min), max(info.max), inst(info.inst), value(randRange(min, max)), owned(0){
}

int Stock::randRange(int min, int max){ // Random number between min and max
	return (int)(dist(gen) * (max - min) + min + 0.5); // + 0.5 is to correct C++ always rounding down when converting to int
}

double Stock::randRange(double min, double max){ // Overload for double variables
	return (dist(gen) * (max - min) + min);
}

void Stock::iterateValue(){

	double currentlog = log10(value); // The mathamatical log of the current value
	double nextlog = randRange(currentlog - inst, currentlog + inst); // The log of the new value, based on the instability
	value = (int)pow(10, nextlog); // Convert back to normal number

	//int r =	(int)((max - min) * inst / 2 + 0.5);	Old linear algorithm
	//value = randRange(value - r, value + r);

	if(value > max){ // To implement minimum and maximum values
		value = randRange((int)pow(10, log10(max) - inst / 2), max); // I don't know how to describe what I've done here I really hope it works
	}
	if(value < min){
		value = randRange(min, (int)pow(10, log10(min) + inst / 2));
	}
}

Stock::~Stock(){}
