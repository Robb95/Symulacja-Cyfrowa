#include "CheckingTheChannelBusy.h"



CheckingTheChannelBusy::CheckingTheChannelBusy(WirelessNetwork* network, int id_base_station)
{
	network_ = network;
	id_base_station_ = id_base_station;
}

void CheckingTheChannelBusy::Execute()
{
	if (network_->GetCheckingTheChannelBusy())   //KANAL WOLNY
	{
		PT_ = rand()%10+1;
		if (PT_ <= 4) //wysylamy
		{
			network_->SentPackageBaseStationToRecivingStation(id_base_station_);
		}
		else //nie wysylamy, planujemy wystapienie zdarzenia wolnej szczeliny
		{
			network_->AddToBaseStationWaitingNewSlot(id_base_station_);
		}
	}
	else // zaplanuj kolejne zdarzenie czasowe (sprawdzenie zajetosci kanalu) KANAL ZAJETY
	{

	}
}

void CheckingTheChannelBusy::Print()
{
	cerr << " Checking the channel busy: " << time_<<endl;
}
