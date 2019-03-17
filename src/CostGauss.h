#ifndef COSTGAUSS_H
#define COSTGAUSS_H

#include "Interval.h"

#include<vector>

struct Point
{
  double y;
  double w;
};

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

    double point_eval(double number) const;

    Interval intervalInterRoots(double level);

    int sign_Q2_Minus_Q1(CostGauss const& cost_Q2, double leftBound) const;

    ///OPERATIONS
    void operator+=(CostGauss const& cost);
    void operator+=(double number);

    void shift(double parameter);
    void axisSymmetry();
    void opposition();

    CostGauss minus(CostGauss const& mycost);
    bool isEqual(CostGauss const& mycost) const;

    void show() const;

  private:
    double m_A;
    double m_B;
    double constant;
};


#endif // COSTGAUSS_H
