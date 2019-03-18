#ifndef COSTGAUSS_H
#define COSTGAUSS_H

#include "Interval.h"

#include<vector>

class CostGauss
{
  public:
    CostGauss();
    CostGauss(double y);

    double getM_A() const;
    double getM_B() const;
    double getConstant() const;

    double minimum() const;
    double arg_minimum() const;

    Interval intervalInterRoots(double level);


    ///OPERATIONS
    void operator+=(CostGauss const& cost);
    void operator+=(double number);

    void show() const;

  private:
    double m_A;
    double m_B;
    double constant;
};


#endif // COSTGAUSS_H
