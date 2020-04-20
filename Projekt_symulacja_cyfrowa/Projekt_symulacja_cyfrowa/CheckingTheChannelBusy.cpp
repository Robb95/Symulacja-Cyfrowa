#include "CheckingTheChannelBusy.h"



CheckingTheChannelBusy::CheckingTheChannelBusy(WirelessNetwork* network)
{
	network_ = network;
}

void CheckingTheChannelBusy::Execute()
{
	if (network_->GetCheckingTheChannelBusy())
	{

	}
	else // zaplanuj kolejne zdarzenie czasowe (sprawdzenie zajetosci kanalu)
	{

	}
}

void CheckingTheChannelBusy::Print()
{
	cerr << " Checking the channel busy: " << time_<<endl;
}
