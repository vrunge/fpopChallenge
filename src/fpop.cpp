#include<math.h>

#include<Rcpp.h>
#include"Empty.h"

#include"Omega.h"
#include"fpopgaeta.h"

using namespace Rcpp;
using namespace std;


// [[Rcpp::export]]
List fpopChallenge(std::vector<double> vectData, double penalty)
{
  Empty empty = Empty(penalty);
  empty.algo(vectData);

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
List fpopRunge(std::vector<double> vectData, double penalty,  int algoType = 1)
{
  Omega omega = Omega(penalty);
  if(algoType == 1){omega.algo(vectData);}
  if(algoType == 2){omega.algo2(vectData);}
  if(algoType == 3){omega.algo3(vectData);}

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
