#include<math.h>

#include<Rcpp.h>
#include"Empty.h"

#include"Omega.h"
#include"fpopgaeta.h"

using namespace Rcpp;
using namespace std;


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
List fpopRunge(std::vector<double> vectData, double penalty)
{
  Omega omega = Omega(penalty);
  omega.algo(vectData);

  /// RETURN
  List res = List::create(
    _["changepoints"] = omega.GetChangepoints(),
    _["means"] = omega.GetMeans(),
    _["globalCost"] = omega.GetGlobalCost()
  );

  return res;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// [[Rcpp::export]]
List fpopRomano(std::vector<double> vectData, double penalty)
{

  /// RETURN
  List res = List::create(
    _["changepoints"] = FPOPgaeta(vectData, penalty)
  );

  return res;
}
