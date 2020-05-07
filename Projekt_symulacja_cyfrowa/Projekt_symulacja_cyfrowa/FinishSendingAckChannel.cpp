#include "FinishSendingAckChannel.h"

FinishSendingAckChannel::FinishSendingAckChannel(WirelessNetwork* network, int id_base_station, double time)
{
  id_base_station_ = id_base_station;
  network_ = network;
  channel_ = network_->ReturnChannel();
  time_ = time;
}

void FinishSendingAckChannel::Execute()
{
  channel_->FinishAckMessage();
  network_->SetInfoAboutACKInReceivingStation(id_base_station_);
}

double FinishSendingAckChannel::GetTime()
{
  return time_;
}

void FinishSendingAckChannel::Print()
{
  cerr << "FinishSendingAckChannel time: " <<time_ << endl;
}
