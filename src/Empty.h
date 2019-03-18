#ifndef EMPTY_H
#define EMPTY_H

#include "Rcpp.h"

class Empty
{
  public:
    Empty(double beta);
    ~Empty();

    std::vector< int > GetChangepoints() const;
    std::vector< double > GetMeans() const;
    double GetGlobalCost() const;

    void algo(std::vector< double > vectData);

  private:
    double penalty;

    std::vector< int > changepoints; ///vector of changepoints build by fpop (first index of each segment). size c
    std::vector< double > means; ///vector of means build by fpop. size c
    double globalCost;
};

#endif // EMPTY_H
