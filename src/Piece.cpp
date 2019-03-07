#include "Piece.h"

#include <math.h>
#include <stdlib.h>
#include<iostream>
#include<typeinfo>

#include <fstream> ///write in a file
#include<vector>

Piece::Piece(Interval const& inter, CostGauss const& cost)
{
  m_interval = inter;
  m_cost = cost;
  nxt = NULL;
}

Piece::Piece(const Piece* piece)
{
  m_interval = piece -> m_interval;
  m_cost = piece -> m_cost;
  nxt = NULL;
}


//####### destructor #######////####### destructor #######////####### destructor #######//
//####### destructor #######////####### destructor #######////####### destructor #######//

Piece::~Piece()
{
  delete(nxt);
  nxt = NULL;
}


//####### accessors #######////####### accessors #######////####### accessors #######//
//####### accessors #######////####### accessors #######////####### accessors #######//

Interval Piece::getInterval() const {return(m_interval);}
CostGauss Piece::getCost() const {return(m_cost);}
CostGauss& Piece::getRefCost(){return(m_cost);}

//####### addDataPoint #######////####### addDataPoint #######////####### addDataPoint #######//
//####### addDataPoint #######////####### addDataPoint #######////####### addDataPoint #######//

void Piece::addDataPoint(double y, double w, Track& track)
{
  Piece* tmp = this;
  CostGauss newCost = CostGauss(y,w);
  double minimum;

  while(tmp != NULL)
  {
    tmp -> getRefCost() += newCost; /// update the cost
    minimum = tmp -> m_cost.minimum(); /// find the minimum
    if(minimum < track.getMinimum())
      {
        track.setMinimum(minimum);
        track.setArgminimum(tmp -> m_cost.arg_minimum());
        track.setLabel(tmp -> m_cost.getM_A()); ///
      } /// update if necessary
    tmp = tmp -> nxt;
  }
}



//####### cut #######////####### cut #######////####### cut #######//
//####### cut #######////####### cut #######////####### cut #######//

void Piece::cut(double level)
{
  Piece* tmp = this;

  while(tmp != NULL)
  {
    tmp = tmp -> nxt;
  }
}



