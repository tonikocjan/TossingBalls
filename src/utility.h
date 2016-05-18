#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <ctime>
#include <GLFW/glfw3.h>
#include "SOIL.h"
#include "Camera.h"

using namespace std;

#define TODEGREES 180 / M_PI
#define TORAD M_PI / 180

template<class T>
inline string NumberToString(T x) {
	stringstream ss;
	ss << x;
	return ss.str();
}

inline string CurrentTimeAndDate() {
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	return string(asctime (timeinfo));
}


inline void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


inline vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}
