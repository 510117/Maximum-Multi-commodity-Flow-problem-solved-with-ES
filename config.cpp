#include "config.h"

const ll INF = 1e9;
const double EPS = 1e-6;
const bool debug = false;

default_random_engine gen(time(NULL));
uniform_int_distribution<int> unif(0, 1e9);