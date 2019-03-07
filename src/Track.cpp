#include "Track.h"

Track::Track()
{
  minimum = INFINITY;
  argminimum = INFINITY;
  label = 0;
}

double Track::getMinimum() const {return(minimum);}
double Track::getArgminimum() const {return(argminimum);}
int Track::getLabel() const {return(label);}

void Track::setMinimum(double mini){minimum = mini;}
void Track::setArgminimum(double argmini){argminimum = argmini;}
void Track::setLabel(int newlabel){label = newlabel;}

