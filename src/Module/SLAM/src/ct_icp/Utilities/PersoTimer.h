#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <ctime>


class PersoTimer
{
public:
	PersoTimer();
	~PersoTimer();

	void   tic();
	double toc(bool print=true);
	double toc(std::string str, bool print=true);

private:
	clock_t _t;
	double  _dt;
};
