#include<Rcpp.h>
#include"Empty.h"

using namespace Rcpp;

// [[Rcpp::export]]
List fpopChallenge(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty)
{
  Empty empty = Empty();
  empty.algo(vectData, vectWeight, penalty);

  /// RETURN
  List res = List::create(
    _["changepoints"] = empty.GetChangepoints(),
    _["means"] = empty.GetMeans(),
    _["globalCost"] = empty.GetGlobalCost()
  );

  return res;
}


