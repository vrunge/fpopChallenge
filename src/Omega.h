#ifndef OMEGA_H
#define OMEGA_H

#include"Piece.h"

#include <math.h>
#include<vector>

#include "Rcpp.h"


class Omega
{
  public:
    Omega();
    ~Omega();

    std::vector< int > GetChangepoints() const;
    std::vector< double > GetMeans() const;
    double GetGlobalCost() const;

    void algo(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty);


  private:
    Piece* functionalCost;

    std::vector< int > changepoints; ///vector of changepoints build by fpop (first index of each segment). size c
    std::vector< double > means; ///vector of means build by fpop. size c
    double globalCost;
};

#endif // OMEGA_H
