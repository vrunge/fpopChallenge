#ifndef TRACK_H
#define TRACK_H

#include"math.h"

class Track
{
  public:
    Track();

    double getMinimum() const;
    double getArgminimum() const;
    int getLabel() const;

    void setMinimum(double mini);
    void setArgminimum(double argmini);
    void setLabel(int newlabel);

  private:
    double minimum;
    double argminimum;
    int label;
};

#endif // TRACK_H
