#ifndef PIECE_H
#define PIECE_H

#include "Interval.h"
#include "CostGauss.h"
#include "Track.h"

#include<vector>
#include<string>

class Piece
{
  public:
    Piece(Interval const& inter = Interval(), CostGauss const& cost = CostGauss());
    Piece(const Piece* piece); ///COPY CONSTRUCTOR => copy only the first Piece. piece -> nxt = NULL

    ~Piece();

    Interval getInterval() const;
    CostGauss getCost() const;
    CostGauss& getRefCost();

    void addDataPoint(double y, double w, Track& track);
    void cut(double level);

  private:

    Interval m_interval;
    CostGauss m_cost;  /// pointer to the cost associated to the current piece
    Piece *nxt;   /// pointer to next piece

};


#endif // PIECE_H
