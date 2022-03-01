#include <vector>
#include <random>
#include <algorithm>
#include "randengine.h"

using namespace std;

RandEngine::RandEngine(int lowest, int highest)
: rd{}, mt(rd()), dist(lowest, highest)
{
	this->lowest = lowest;
	this->highest = highest;
}

int RandEngine::generate_int()
{
	return dist(this->mt);
}

vector<int> RandEngine::generate_permutation()
{
	vector<int> list;
	while (list.size() < (unsigned long int)(highest - lowest + 1)) {
		auto rn = dist(mt);
		if (any_of(list.begin(), list.end(),
		    [rn](int s){ return s==rn; }))
			continue;
		list.push_back(rn);
	}
	return list;
}
