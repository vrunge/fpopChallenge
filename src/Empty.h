#ifndef EMPTY_H
#define EMPTY_H

#include "Rcpp.h"
#include <vector>

class Empty
{
  public:
    Empty();
    ~Empty();

    std::vector< int > GetChangepoints() const;
    std::vector< double > GetMeans() const;
    double GetGlobalCost() const;

    void algo(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty);

  private:

    std::vector< int > changepoints; ///vector of changepoints build by fpop (first index of each segment). size c
    std::vector< double > means; ///vector of means build by fpop. size c
    double globalCost;
};

#endif // EMPTY_H
