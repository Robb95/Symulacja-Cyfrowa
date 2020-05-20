#ifndef CHECKACKMESSAGE_H
#define CHECKACKMESSAGE_H
#include "TimeEvent.h"
#include "WirelessNetwork.h"
#include "TimeEventList.h"
#include "CheckingTheChannelBusy.h"


class CheckAckMessage :
  public TimeEvent
{
public:
  CheckAckMessage(WirelessNetwork* network, TimeEventList* list, double time, int id_base_station);
void Execute();
double GetTime();
void Print();
int ReturnId();
int ReturnIdBaseStation();
private:
  WirelessNetwork* network_;
  double time_;
  int id_base_station_;
  Package* package_;
  TimeEventList* list_;
  int id_ = 1;
};
#endif

