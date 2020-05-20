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
	if (network_->GetTypeInfo() < 3)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "Finish sending ACK channel, time: " << time_ << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "Finish sending ACK channel, time: " << time_ << endl;
			save.close();
		}
	}
}

int FinishSendingAckChannel::ReturnId()
{
	return id_;
}

int FinishSendingAckChannel::ReturnIdBaseStation()
{
  return -1;
}
