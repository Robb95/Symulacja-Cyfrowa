#include "ErrorTER.h"

ErrorTER::ErrorTER(WirelessNetwork* network)
{
	network_ = network;
}

double ErrorTER::GetTime()
{
	return time_;
}

void ErrorTER::Print()
{
	cerr << " Error TER: " << time_ << endl;
}

void ErrorTER::Execute()
{
	Channel* tmp = network_->ReturnChannel();
	Package* tmp2 = tmp->ReturnCurrentPackage();
	tmp->DeleteCurrentPackage();
	if (tmp2->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision())
	{
		tmp2->IncrementLR();
		network_->SentPackageToRetransmission(tmp2);
	}
	else
	{
		delete tmp2;
		cerr << "The package deleted [Package retransmission limit exceeded]" << endl;
	}
}
