#pragma once
#include "TimeEvent.h"
#include "WirelessNetwork.h"

class FinishSendingAckChannel :
  public TimeEvent
{
public:
  FinishSendingAckChannel(WirelessNetwork* network, int id_base_station, double time);
  void Execute();
	 double GetTime();
	 void Print();
   int ReturnId();
private:
  int id_base_station_;
  WirelessNetwork* network_;
  Channel* channel_;
  double time_;
  int id_;
};

