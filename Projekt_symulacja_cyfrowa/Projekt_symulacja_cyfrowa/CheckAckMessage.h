#ifndef CHECKACKMESSAGE_H
#define CHECKACKMESSAGE_H
#include "TimeEvent.h"
#include "WirelessNetwork.h"


class CheckAckMessage :
  public TimeEvent
{
public:
  CheckAckMessage(WirelessNetwork* network, double time, int id_base_station);
void Execute();
double GetTime();
void Print();
int ReturnId();
private:
  WirelessNetwork* network_;
  double time_;
  int id_base_station_;
  Package* package_;
  int id_ = 1;
};
#endif

