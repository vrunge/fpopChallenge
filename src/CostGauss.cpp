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
  double minimum = constant;
  if(m_A > 0){minimum = -(m_B*m_B/(4*m_A)) + constant;}

  return(minimum);
}

double CostGauss::arg_minimum() const
{
  double argmin = INFINITY;
  if(m_A == 0)
  {
    ///if(m_B<=0){argmin = INFINITY;}
    if(m_B > 0){argmin = -INFINITY;}
  }
  else
  {
    argmin = -m_B/(2*m_A);
  }

  return(argmin);
}
/// ARGMIN of a constant = + INFINITY


//####### point_eval #######////####### point_eval #######////####### point_eval #######//
//####### point_eval #######////####### point_eval #######////####### point_eval #######//

double CostGauss::point_eval(double number) const {return((m_A*number*number) + (m_B*number) + constant);}


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
/// pt.w*(THETA^2 - 2*pt.y*THETA + pt.y*pt.y)

void CostGauss::operator+=(CostGauss const& cost)
{
  m_A = m_A + cost.getM_A();
  m_B = m_B + cost.getM_B();
  constant = constant + cost.getConstant();
}

void CostGauss::operator+=(double number)
{constant = constant + number;}

//bool operator==(CostGauss const& cost1, CostGauss const& cost2)
//{
//  if (cost1.getM_A() == cost2.getM_A() && cost1.getM_B() == cost2.getM_B() && cost1.getConstant() == cost2.getConstant())
//    return true;
//  else
//    return false;
//}


//####### minus #######////####### minus #######////####### minus #######//
//####### minus #######////####### minus #######////####### minus #######//


CostGauss CostGauss::minus(CostGauss const& mycost)
{
  CostGauss gaussNew = CostGauss();
  gaussNew.m_A = m_A - mycost.getM_A();
  gaussNew.m_B = m_B - mycost.getM_B();
  gaussNew.constant = constant - mycost.getConstant();

  return(gaussNew);
}




//####### isEqual #######////####### isEqual #######////####### isEqual #######//
//####### isEqual #######////####### isEqual #######////####### isEqual #######//

bool CostGauss::isEqual(CostGauss const& mycost) const
{
  bool res = false;
  res = (mycost.getM_A() == m_A)&&(mycost.getM_B() == m_B)&&(mycost.getConstant() == constant);
  return(res);
}



////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void CostGauss::show() const
{
  std::cout << "#GAUSS# #A# " << m_A << " #B# "<< m_B << " #C# " << constant;
  std::cout << " #MIN# "<< minimum();
  std::cout << " #ARGMIN# "<< arg_minimum() << std::endl;
}



