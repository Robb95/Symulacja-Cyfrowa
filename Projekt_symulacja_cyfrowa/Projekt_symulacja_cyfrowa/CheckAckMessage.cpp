#include "CheckAckMessage.h"

CheckAckMessage::CheckAckMessage(WirelessNetwork* network, double time,int id_base_station)
{
  network_ = network;
  id_base_station_ = id_base_station;
  time_ = time;

}

void CheckAckMessage::Execute()
{
	if (!(network_->GetInfoAboutACKInReceivingStation(id_base_station_))) 
	{
	package_ = network_->GetPackageTer(id_base_station_);
		if (package_->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision())
		{
		package_->IncrementLR();
		network_->SentPackageToRetransmission(package_); 
		}
		else
		{
		delete package_;
		cerr << "The package deleted [Package retransmission limit exceeded]" << endl;
		}
	}
	else
	{
		cerr << "wiadomosc ack poprawnie dostarczona" << endl;
	}
}

double CheckAckMessage::GetTime()
{
  return time_;
}

void CheckAckMessage::Print()
{
  cerr << "Sprawdzanie wiadomosci ack po czasie ctiz bla bla bla id stacji"<<id_base_station_ << endl;
}
