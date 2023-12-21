#ifndef __CONFIG_H
#define __CONFIG_H

#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")

#include <vector>
#include <algorithm>
#include <ctime>
#include <map>
#include <random>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <queue>
#include <set>

using namespace std;
using SDpair = pair<int, int>;
using ll = long long int;

extern const ll INF;
extern const double EPS;
extern const bool debug;

extern default_random_engine gen;
extern uniform_int_distribution<int> unif;

#endif