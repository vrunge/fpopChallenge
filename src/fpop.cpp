#include<math.h>

#include<Rcpp.h>
#include"Empty.h"

#include"Omega.h"

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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// [[Rcpp::export]]
List fpopRunge(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty)
{
  Omega omega = Omega();
  omega.algo(vectData, vectWeight, penalty);

  /// RETURN
  List res = List::create(
    _["changepoints"] = omega.GetChangepoints(),
    _["means"] = omega.GetMeans(),
    _["globalCost"] = omega.GetGlobalCost()
  );

  return res;
}




