#include "Omega.h"
#include "CostGauss.h"
#include "Piece.h"
#include "Track.h"

#include <algorithm>    // std::reverse
#include<iostream>
#include <stdlib.h>

//####### constructor #######////####### constructor #######////####### constructor #######//
//####### constructor #######////####### constructor #######////####### constructor #######//

Omega::Omega(double beta)
{
  penalty = beta;
  functionalCost = new Piece(Interval(-INFINITY, INFINITY));
}

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


void Omega::algo(std::vector< double > vectData)
{
  int n = vectData.size();

  ///INITIALIZATION
  Track track = Track();
  track.setMinimum(0);
  int* chpts = new int[n]; ///vector of changepoints build by fpop
  double* ms = new double[n]; ///vector of means build by fpop

  functionalCost -> show();

  for(unsigned int i = 0; i < n; i++)
  {
    functionalCost = functionalCost -> cut(track.getMinimum() + penalty);
    functionalCost -> addDataPoint(vectData[i], track); /// + update track

    ///
    chpts[i] = i - track.getNbSteps();
    ms[i] = track.getArgminimum();
  }

  globalCost = track.getMinimum();


  ///backtracking
  int tau = n - 1;

  while(tau != -1)
  {
    changepoints.push_back(tau + 1);
    means.push_back(ms[tau]);
    tau = chpts[tau];
  }

  std::reverse(changepoints.begin(), changepoints.end());
  std::reverse(means.begin(), means.end());


}





