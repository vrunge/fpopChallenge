#include "Piece.h"

#include <math.h>
#include <stdlib.h>
#include<iostream>

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


//####### addConstant #######////####### addConstant #######////####### addConstant #######//
//####### addConstant #######////####### addConstant #######////####### addConstant #######//

void Piece::addConstant(double& myconstant)
{
  this -> getRefCost() += myconstant;
}

//####### addDataPoint #######////####### addDataPoint #######////####### addDataPoint #######//
//####### addDataPoint #######////####### addDataPoint #######////####### addDataPoint #######//

void Piece::addDataPoint(double& y, Track& track)
{
  //Initialize minimum to +Inf
  track.setMinimum(INFINITY);

  ///Build Cost to add
  CostGauss newCost = CostGauss(y);

  Piece* tmp = this;
  double minimum;

  while(tmp != NULL)
  {
    tmp -> getRefCost() += newCost; /// update the cost
    minimum = tmp -> m_cost.minimum(); /// find the minimum
    if(minimum < track.getMinimum())
      {
        track.setMinimum(minimum);
        track.setArgminimum(tmp -> m_cost.arg_minimum());
        track.setNbSteps(tmp -> m_cost.getM_A());
      }
    tmp = tmp -> nxt;
  }
}


//####### cut #######////####### cut #######////####### cut #######//
//####### cut #######////####### cut #######////####### cut #######//

Piece* Piece::cut(double level)
{
  Piece* tmp = this;
  Piece* ToDeletePiece = NULL;
  int type;

  /// intervals
  Interval interRoots = Interval();
  Interval saveInterval;

  //INITIALIZATION of FirstPiece
  Piece* FirstPiece = new Piece();
  FirstPiece -> addConstant(level);
  FirstPiece -> m_interval.seta(-INFINITY);
  FirstPiece -> nxt = tmp;
  tmp = FirstPiece;

  while(tmp -> nxt != NULL)
  {
    saveInterval = tmp -> nxt -> m_interval;
    tmp -> nxt -> m_interval.intersection(interRoots, type);

    if(type != 0)
    {
      tmp -> nxt -> m_interval = saveInterval;
      interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level); //recompute interRoots
      tmp -> nxt -> m_interval.intersection(interRoots, type);
    }

    switch(type)
    {
    case -1:
    {
      ToDeletePiece = tmp -> nxt;
      tmp -> nxt = ToDeletePiece -> nxt;
      ToDeletePiece -> nxt = NULL;
      delete(ToDeletePiece);
      break;
    }

    case 0:
      {
      tmp = tmp -> nxt;
      break;
      }

    case 1:
      tmp -> m_interval.setb(interRoots.geta());
      tmp = tmp -> nxt;
      break;

    case 2:
      {
      Piece* newConstPiece2 = new Piece();
      newConstPiece2 -> addConstant(level);
      newConstPiece2 -> m_interval.seta(interRoots.getb());
      newConstPiece2 -> nxt = tmp -> nxt -> nxt;
      tmp -> nxt -> nxt = newConstPiece2;
      tmp = newConstPiece2;
      break;
      }
    case 3:
      {
      tmp -> m_interval.setb(interRoots.geta());
      Piece* newConstPiece3 = new Piece();
      newConstPiece3 -> addConstant(level);
      newConstPiece3 -> m_interval.seta(interRoots.getb());
      newConstPiece3 -> nxt = tmp -> nxt -> nxt;
      tmp -> nxt -> nxt = newConstPiece3;
      tmp = newConstPiece3;
      break;
      }
    }
  }
  return(FirstPiece);
}


//####### cut2 #######////####### cut2 #######////####### cut2 #######//
//####### cut2 #######////####### cut2 #######////####### cut2 #######//

Piece* Piece::cut2(double level)
{
  Piece* tmp = this;
  Piece* ToDeletePiece = NULL;
  int type;

  /// intervals
  Interval interRoots = Interval();

  //INITIALIZATION of FirstPiece
  Piece* FirstPiece = new Piece();
  FirstPiece -> addConstant(level);
  FirstPiece -> m_interval.seta(-INFINITY);
  FirstPiece -> nxt = tmp;
  tmp = FirstPiece;

  while(tmp -> nxt != NULL)
  {
    interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level); //recompute interRoots
    tmp -> nxt -> m_interval.intersection(interRoots, type);

    switch(type)
    {
    case -1:
    {
      ToDeletePiece = tmp -> nxt;
      tmp -> nxt = ToDeletePiece -> nxt;
      ToDeletePiece -> nxt = NULL;
      delete(ToDeletePiece);
      ToDeletePiece = NULL;
      break;
    }

    case 0:
    {
      tmp = tmp -> nxt;
      break;
    }

    case 1:
      tmp -> m_interval.setb(interRoots.geta());
      tmp = tmp -> nxt;
      break;

    case 2:
      {
        Piece* newConstPiece2 = new Piece();
        newConstPiece2 -> addConstant(level);
        newConstPiece2 -> m_interval.seta(interRoots.getb());
        newConstPiece2 -> nxt = tmp -> nxt -> nxt;
        tmp -> nxt -> nxt = newConstPiece2;
        tmp = newConstPiece2;
        break;
      }
    case 3:
      {
        tmp -> m_interval.setb(interRoots.geta());
        Piece* newConstPiece3 = new Piece();
        newConstPiece3 -> addConstant(level);
        newConstPiece3 -> m_interval.seta(interRoots.getb());
        newConstPiece3 -> nxt = tmp -> nxt -> nxt;
        tmp -> nxt -> nxt = newConstPiece3;
        tmp = newConstPiece3;
        break;
      }
    }
  }
  return(FirstPiece);
}



//####### cut3 #######////####### cut3 #######////####### cut3 #######//
//####### cut3 #######////####### cut3 #######////####### cut3 #######//

Piece* Piece::cut3(double level, double currentArgmin, bool Delta)
{
  Piece* FirstPiece;
  Piece* tmp = this;
  int type;

  /// intervals
  Interval interRoots = Interval();
  Interval saveInterval;

  switch(Delta)
  {
  ///
  /// level cut for means < argminimum
  ///
  case true:
  {
    //INITIALIZATION of FirstPiece
    FirstPiece = new Piece();
    FirstPiece -> addConstant(level);
    FirstPiece -> m_interval.seta(-INFINITY);
    FirstPiece -> nxt = tmp;
    tmp = FirstPiece;

    while((tmp -> nxt != NULL) && (tmp -> nxt -> m_interval.isInside(currentArgmin) == false))
    {
      //interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level); //recompute interRoots
      //tmp -> nxt -> m_interval.intersection(interRoots, type);

      saveInterval = tmp -> nxt -> m_interval;
      tmp -> nxt -> m_interval.intersection(interRoots, type);

      if(type != 0)
      {
        tmp -> nxt -> m_interval = saveInterval;
        interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level); //recompute interRoots
        tmp -> nxt -> m_interval.intersection(interRoots, type);
      }

      tmp = tmp -> ProcessNxt(interRoots, level, type);
    }

    ///piece of the currentArgmin
    interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level);
    if(tmp -> nxt -> m_interval.geta() < interRoots.geta())
    {
      tmp -> m_interval.setb(interRoots.geta());
      tmp -> nxt -> m_interval.seta(interRoots.geta());
    }


    break;
  }

  ///
  /// level cut for means > argminimum
  ///
  case false:
  {
    FirstPiece = tmp;
    while(tmp -> m_interval.isInside(currentArgmin) == false){tmp = tmp -> nxt;}

    ///piece of the currentArgmin
    interRoots = tmp  -> m_cost.intervalInterRoots(level);
    if(interRoots.getb() < tmp -> m_interval.getb()) ///type = 2
    {
      Piece* newConstPiece2 = new Piece();
      newConstPiece2 -> addConstant(level);
      newConstPiece2 -> m_interval.seta(interRoots.getb());
      newConstPiece2 -> nxt = tmp -> nxt;
      tmp -> m_interval.setb(interRoots.getb());
      tmp -> nxt = newConstPiece2;
      tmp = newConstPiece2;
    }

    ///right pieces
    while(tmp -> nxt != NULL)
    {
      //interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level); //recompute interRoots
      //tmp -> nxt -> m_interval.intersection(interRoots, type);

      saveInterval = tmp -> nxt -> m_interval;
      tmp -> nxt -> m_interval.intersection(interRoots, type);

      if(type != 0)
      {
        tmp -> nxt -> m_interval = saveInterval; ///delete intersection
        interRoots = tmp -> nxt -> m_cost.intervalInterRoots(level); //recompute interRoots
        tmp -> nxt -> m_interval.intersection(interRoots, type);
      }

      tmp = tmp -> ProcessNxt(interRoots, level, type);
    }

    break;
  }


  }

  return(FirstPiece);
}



//####### show #######////####### show #######////####### show #######//
//####### show #######////####### show #######////####### show #######//

Piece* Piece::ProcessNxt(Interval& interRoots, double& level, int& type)
{
  Piece* tmp = this;

  switch(type)
  {
    case -1:
    {
      Piece* ToDeletePiece = tmp -> nxt;
      tmp -> nxt = ToDeletePiece -> nxt;
      ToDeletePiece -> nxt = NULL;
      delete(ToDeletePiece);
      break;
    }
    case 0:
    {
      tmp = tmp -> nxt;
      break;
    }
    case 1:
    {
      tmp -> m_interval.setb(interRoots.geta());
      tmp = tmp -> nxt;
      break;
    }
    case 2:
    {
      Piece* newConstPiece2 = new Piece();
      newConstPiece2 -> addConstant(level);
      newConstPiece2 -> m_interval.seta(interRoots.getb());
      newConstPiece2 -> nxt = tmp -> nxt -> nxt;
      tmp -> nxt -> nxt = newConstPiece2;
      tmp = newConstPiece2;
      break;
    }
    case 3:
    {
      tmp -> m_interval.setb(interRoots.geta());
      Piece* newConstPiece3 = new Piece();
      newConstPiece3 -> addConstant(level);
      newConstPiece3 -> m_interval.seta(interRoots.getb());
      newConstPiece3 -> nxt = tmp -> nxt -> nxt;
      tmp -> nxt -> nxt = newConstPiece3;
      tmp = newConstPiece3;
      break;
    }
  }

  return(tmp);
}



//####### show #######////####### show #######////####### show #######//
//####### show #######////####### show #######////####### show #######//

void Piece::show()
{
  Piece* tmp = this;
  if(tmp == NULL){std::cout << "#NULL EMPTY POINTER# "<< std::endl;}
  while(tmp != NULL)
  {
    std::cout << "#INTERVAL# "<< tmp -> m_interval.geta() << " -- " << tmp -> m_interval.getb() << " && ";
    std::cout << "#COST# "<<  tmp -> m_cost.getM_A() << " -- " <<  tmp -> m_cost.getM_B() << " -- " <<  tmp -> m_cost.getConstant() << std::endl;
    tmp = tmp -> nxt;
  }
}

