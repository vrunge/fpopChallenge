#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>
#include <tuple>
#include "quadratic.h"
using namespace std;


std::vector<quad> prune(std::vector<quad>& costS, std::vector<quad>& costR) {
  std::vector<quad> outcost (3 * costS.size(), quad(0, 0, 0, 0, 0, 0));
  int i = 0; // index for the previous cost function
  int j = 0; // index for the contraint function (this will always be equal to 0 in FPOP)
  int k = 0; // index for the outcost
  double low = -INFINITY; // index for the linesearch
  double upp;
  
  while (low != INFINITY) {
    upp = min(u(costS[i]), u(costR[j]));
    // we will always have to check a piecewise quadtratic with a line in case of FPOP
    auto minS = get<0>(getminimum(costS[i]));
    auto minCr = get<0>(getminimum(costR[j]));
    
    auto inters = getintersections(costS[i], minCr);
    auto left_in_range = (get<0>(inters) > low) && (get<0>(inters) < upp);
    auto right_in_range = (get<1>(inters) > low) && (get<1>(inters) < upp);
    auto in_range = left_in_range + right_in_range;
    
    if (in_range == 0) {
      // we do not have any interaction in range, so a check is needed to see if
      // the cost or the constraint are greater
      if (minCr <= minS) {
        outcost[k] = quad(tau(costR[j]), low, upp, a(costR[j]), b(costR[j]), c(costR[j])); k++;
      } else {
        outcost[k] = quad(tau(costS[i]), low, upp, a(costS[i]), b(costS[i]), c(costS[i])); k++;
      }
      
    } else if (in_range == 1) {
      // in this case we have only one interaction and we have to understand if it's
      // the right one or the left one
      if (right_in_range) {
        // in this case it's the right
        outcost[k] = quad(tau(costS[i]), low,            get<1>(inters), a(costS[i]), b(costS[i]), c(costS[i])); k++;
        outcost[k] = quad(tau(costR[j]), get<1>(inters), upp,            a(costR[j]), b(costR[j]), c(costR[j])); k++;
      } else {
        // in this case is the left
        outcost[k] = quad(tau(costR[j]), low,            get<0>(inters), a(costR[j]), b(costR[j]), c(costR[j])); k++;
        outcost[k] = quad(tau(costS[i]), get<0>(inters), upp,            a(costS[i]), b(costS[i]), c(costS[i])); k++;
      }
      
    } else if (in_range == 2) {
      // in this case we have two interactions, so first the constraint, then the costf, then the constraint
      outcost[k] = quad(tau(costR[j]), low,            get<0>(inters), a(costR[j]), b(costR[j]), c(costR[j])); k++;
      outcost[k] = quad(tau(costS[i]), get<0>(inters), get<1>(inters), a(costS[i]), b(costS[i]), c(costS[i])); k++;
      outcost[k] = quad(tau(costR[j]), get<1>(inters), upp,            a(costR[j]), b(costR[j]), c(costR[j])); k++;
    } else {std::cout << "THIS SHOULD NOT HAPPEN" << '\n';}
    
    // updating i, j and l
    if (u(costS[i]) == upp) {
      i++;
    } else {
      j++;
      std::cout << "THIS SHOULD NOT HAPPEN IN FPOP" << '\n';
    }
    
    // sliding to the next window
    low = upp;
  }
  
  outcost.resize(k);
  
  // picking the unique values
  std::vector<int> to_select (outcost.size(), true);
  
  for (int k = 1; k < outcost.size(); k++) {
    if (a(outcost[k]) == a(outcost[k - 1])) {
      get<1>(outcost[k]) = get<1>(outcost[k - 1]);
      to_select[k - 1] = false;
    }
  }
  
  std::vector<quad> output;
  for (int i=0; i < outcost.size(); i++) {
    if (to_select[i]) {
      output.push_back(outcost[i]);
    }
  }
  //auto it = copy_if(outcost.begin(), outcost.end(), to_select.begin(), outcost.begin(), [](auto& val, auto& cond){return cond;});
  //outcost.resize(std::distance(outcost.begin(), it));
  return (output);
}


std::vector<int> backtracking(std::vector<int>& taus) {
  std::vector<int> cp;
  int s = taus.size();
  cp.push_back(s);
  
  while (taus[s - 1] != 0) {
    cp.push_back(taus[s - 1]);
    s = taus[s - 1];
  }
  reverse(cp.begin(), cp.end());
  return cp;
}



// main GFPOP function, takes a vector of data by reference and a penalty as a double
vector<int> FPOPgaeta (vector<double> &y, double &penalty) {
  int N = y.size();
  vector<quad> Q = {quad(0, -INFINITY, INFINITY, 0, 0, 0)};
  vector<int> taus;

  for (size_t t = 0; t < N; t++) {

    // updating the values in each piecewise quadtratic in Q
    transform(Q.begin(), Q.end(), Q.begin(), [&y, &t](quad& q){return update(q, y[t]);});

    //getting the minimum in Q and the relative tau
    std::vector<double> mins(Q.size());
    transform(Q.begin(), Q.end(), mins.begin(), [](quad& q){return get<0>(getminimum(q));});
    auto tau_ind = distance(mins.begin(), min_element(mins.begin(), mins.end()));
    taus.push_back(tau(Q[tau_ind]));

    // performing the minimization (pruning with a line at height F + beta)
    vector<quad> constraint (1, quad(t + 1, -INFINITY, INFINITY, 0, 0, mins[tau_ind] + penalty));
    Q = prune(Q, constraint);

  }
  //print_costf(Q);

  auto cp = backtracking(taus);

  return cp;
}

