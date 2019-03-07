#ifndef INTERVAL_H
#define INTERVAL_H

#include"math.h"

class Interval
{
  public:
    Interval();
    Interval(double a, double b);

    void seta(double a);
    void setb(double b);
    double geta() const;
    double getb() const;

    bool isEmpty() const;
    bool isInside(double x) const;

    void intersection(Interval const& inter);

    double internPoint() const;

    void show() const;

  private:
    double m_a;
    double m_b;
};

#endif // INTERVAL_H
