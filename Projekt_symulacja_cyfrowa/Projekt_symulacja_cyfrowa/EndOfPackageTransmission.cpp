#include "EndOfPackageTransmission.h"

void EndOfPackageTransmission::Execute()
{
	int tmp = network_->SentPackageToReceivingStation((network_->ReturnChannel())->ReturnCurrentPackage());
	cerr << "ACK" << endl;
	network_->AddACKFromReceivingStation(tmp);
}

void EndOfPackageTransmission::Print()
{
	cerr << " Checking package transmission: " << time_ << endl;
}
