#include "Omega.h"
#include "CostGauss.h"
#include "Piece.h"
#include "Track.h"

#include<iostream>
#include <iomanip> ///Set Precision scientific

#include<typeinfo>
#include <stdlib.h>

//####### constructor #######////####### constructor #######////####### constructor #######//
//####### constructor #######////####### constructor #######////####### constructor #######//

Omega::Omega(){functionalCost = new Piece();}


//####### destructor #######////####### destructor #######////####### destructor #######//
//####### destructor #######////####### destructor #######////####### destructor #######//

Omega::~Omega(){delete(functionalCost);}

//####### accessors #######////####### accessors #######////####### accessors #######//
//####### accessors #######////####### accessors #######////####### accessors #######//

std::vector< int > Omega::GetChangepoints() const {return(changepoints);}
std::vector< double > Omega::GetMeans() const {return(means);}
double Omega::GetGlobalCost() const {return(globalCost);}


//####### algo #######////####### algo #######////####### algo #######//
//####### algo #######////####### algo #######////####### algo #######//


void Omega::algo(Rcpp::NumericVector vectData, Rcpp::NumericVector vectWeight, double penalty)
{
  Track track = Track();
  std::vector< int > chpts; ///vector of changepoints build by fpop
  std::vector< double > ms; ///vector of means build by fpop


  for(unsigned int i = 0; i < vectData.length(); i++)
  {
    track.setMinimum(INFINITY);
    functionalCost -> addDataPoint(vectData[i],vectWeight[i], track); ///level = minimum of the functionalCost
    functionalCost -> cut(track.getMinimum() + penalty);
  }

  globalCost = track.getMinimum();
}




