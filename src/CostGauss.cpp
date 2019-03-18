#include "CostGauss.h"

#include"math.h"
#include <iostream>
#include<vector>

CostGauss::CostGauss(): m_A(0), m_B(0), constant(0){}
CostGauss::CostGauss(double y)
{
  m_A = 1;
  m_B = -2*y;
  constant = y*y;
}


double CostGauss::getM_A() const {return(m_A);}
double CostGauss::getM_B() const {return(m_B);}
double CostGauss::getConstant() const {return(constant);}


//####### min arg_min #######////####### min arg_min #######////####### min arg_min #######//
//####### min arg_min #######////####### min arg_min #######////####### min arg_min #######//

double CostGauss::minimum() const
{
  return(-(m_B*m_B/(4*m_A)) + constant);
}

double CostGauss::arg_minimum() const
{
  return(-m_B/(2*m_A));
}

//####### comparisons #######////####### comparisons #######////####### comparisons #######//
//####### comparisons #######////####### comparisons #######////####### comparisons #######//

Interval CostGauss::intervalInterRoots(double level)
{

  Interval newElement = Interval();
  double Delta = m_B*m_B - 4*m_A*(constant - level);

  if(Delta > 0)
  {
    double argmin = arg_minimum();
    double R = sqrt(Delta)/(2*m_A);
    newElement = Interval(argmin - fabs(R), argmin + fabs(R));
  }

  return(newElement);
}




//####### operations #######////####### operations #######////####### operations #######//
//####### operations #######////####### operations #######////####### operations #######//

/// m_A*THETA^2 + m_B*THETA + constant

void CostGauss::operator+=(CostGauss const& cost)
{
  m_A = m_A + cost.getM_A();
  m_B = m_B + cost.getM_B();
  constant = constant + cost.getConstant();
}

void CostGauss::operator+=(double number)
{constant = constant + number;}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void CostGauss::show() const
{
  std::cout << "#GAUSS# #A# " << m_A << " #B# "<< m_B << " #C# " << constant;
  std::cout << " #MIN# "<< minimum();
  std::cout << " #ARGMIN# "<< arg_minimum() << std::endl;
}



