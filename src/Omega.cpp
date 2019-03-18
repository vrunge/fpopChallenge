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


void Omega::algo(std::vector< double >& vectData)
{
  int n = vectData.size();

  ///INITIALIZATION
  Track track = Track();
  track.setMinimum(0);
  int* chpts = new int[n]; ///vector of changepoints build by fpop
  double* ms = new double[n]; ///vector of means build by fpop

  for(unsigned int i = 0; i < n; i++)
  {
    functionalCost = functionalCost -> cut(track.getMinimum() + penalty);
    functionalCost -> addDataPoint(vectData[i], track); /// + update track

    ///
    chpts[i] = i - track.getNbSteps();
    ms[i] = track.getArgminimum();
  }

  globalCost = track.getMinimum() - penalty;

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

  delete(chpts);
  delete(ms);
}



//####### algo2 #######////####### algo2 #######////####### algo2 #######//
//####### algo2 #######////####### algo2 #######////####### algo2 #######//

void Omega::algo2(std::vector< double >& vectData)
{
  int n = vectData.size();

  ///INITIALIZATION
  Track track = Track();
  track.setMinimum(0);
  int* chpts = new int[n]; ///vector of changepoints build by fpop
  double* ms = new double[n]; ///vector of means build by fpop

  for(unsigned int i = 0; i < n; i++)
  {
    functionalCost = functionalCost -> cut2(track.getMinimum() + penalty);
    functionalCost -> addDataPoint(vectData[i], track); /// + update track

    ///
    chpts[i] = i - track.getNbSteps();
    ms[i] = track.getArgminimum();
  }

  globalCost = track.getMinimum() - penalty;


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

  delete[] chpts;
  chpts = NULL;
  delete[] ms;
  ms = NULL;

}


//####### algo3 #######////####### algo3 #######////####### algo3 #######//
//####### algo3 #######////####### algo3 #######////####### algo3 #######//

void Omega::algo3(std::vector< double >& vectData)
{
  int n = vectData.size();

  ///INITIALIZATION
  Track track = Track();
  int* chpts = new int[n]; ///vector of changepoints build by fpop
  double* ms = new double[n]; ///vector of means build by fpop

  ///
  /// FIRST STEP
  ///
  functionalCost ->getRefCost() += penalty;
  functionalCost -> addDataPoint(vectData[0], track); /// + update track
  chpts[0] =  - track.getNbSteps();
  ms[0] = track.getArgminimum();

  ///
  /// INTERN STEPS
  ///
  bool Delta; /// argminimum - vectData[i] > 0
  for(unsigned int i = 1; i < n; i++)
  {
    Delta = track.getArgminimum() - vectData[i] > 0;
    functionalCost = functionalCost -> cut3(track.getMinimum() + penalty, track.getArgminimum(), Delta);
    //functionalCost -> show();
    functionalCost -> addDataPoint(vectData[i], track); /// + update track

    ///
    chpts[i] = i - track.getNbSteps();
    ms[i] = track.getArgminimum();
    //std::cout <<  ms[i] << " -- " << chpts[i] << " --- " << Delta << std::endl;
  }



  globalCost = track.getMinimum() - penalty;


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

  delete[] chpts;
  chpts = NULL;
  delete[] ms;
  ms = NULL;

}
