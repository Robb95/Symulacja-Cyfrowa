#include "EndOfPackageTransmission.h"

EndOfPackageTransmission::EndOfPackageTransmission(WirelessNetwork* network, double time)
{
	network_ = network;
	time_ = time;
}

void EndOfPackageTransmission::Execute()
{
	int tmp = network_->SentPackageToReceivingStation((network_->ReturnChannel())->ReturnCurrentPackage());
	cerr << "ACK" << endl;
	network_->AddACKFromReceivingStation(tmp);
}

double EndOfPackageTransmission::GetTime()
{
	return time_;
}

void EndOfPackageTransmission::Print()
{
	cerr << " Checking package transmission: " << time_ << endl;
}
