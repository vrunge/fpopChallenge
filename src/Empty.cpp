#include "Empty.h"

Empty::Empty(double beta){penalty = beta;}
Empty::~Empty(){}

std::vector< int > Empty::GetChangepoints() const {return(changepoints);}
std::vector< double > Empty::GetMeans() const {return(means);}
double Empty::GetGlobalCost() const {return(globalCost);}


void Empty::algo(std::vector< double > vectData)
{
  changepoints.push_back(10);
  changepoints.push_back(20);
  means.push_back(2.1);
  means.push_back(5.2);

  globalCost = 12.34;
}
