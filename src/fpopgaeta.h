#include "quadratic.h"

std::vector<quad> prune(std::vector<quad>& costS, std::vector<quad>& costR);
std::vector<int> backtracking(std::vector<int>& taus);
std::vector<int> FPOPgaeta (std::vector<double> &y, double &penalty);