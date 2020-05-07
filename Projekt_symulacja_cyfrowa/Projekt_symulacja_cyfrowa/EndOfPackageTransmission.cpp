#include "EndOfPackageTransmission.h"

EndOfPackageTransmission::EndOfPackageTransmission(WirelessNetwork* network, TimeEventList* list, double time)
{
	network_ = network;
	time_ = time;
	channel_ = network_->ReturnChannel();
	list_ = list;
}

void EndOfPackageTransmission::Execute()
{
	temp_ = channel_->GetVectorSize();
	if (temp_ <= 1)// brak kolizji (przesy�amy wiadomo�� ACK)
	{
		package_ = channel_->ReturnCurrentPackage(channel_->GetIdPackageFromVector(0));
		id_base_station_ = package_->ReturnIdBaseStation();
		cerr << "Pakiet zosta� dostarczony bez kolizji ze stacji o id: " << id_base_station_ << " pakiet ma id: " << package_->ReturnIdPackage() << endl;
		network_->AddPackageToReceivingStation(id_base_station_, package_);
		//zdarzenie warunkowe wys�anie wiadomo�ci ACK oraz zaplanowanie zdarzenia zasowego konca przesy�ania wiadomo�ci ACK
		channel_->SendAckMessage();
		event_ = new FinishSendingAckChannel(network_, id_base_station_, time_ + 1);
		list_->AddTimeEvent(event_);
	}
	else // wyst�pi�a kolizja (zwracamy pakiety do retransmisji)
	{
		for (unsigned i = 0; i < temp_; i++)
		{
			cerr << "WYSTAPILA KOLIZJA" << endl;
			package_ =channel_->ReturnCurrentPackage(channel_->GetIdPackageFromVector(0));
			if (package_->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision())
			{
				package_->IncrementLR();
				network_->SentPackageToRetransmission(package_); //zaplanuj kolejne zdarzenie czasowe, wygenerowanie CRP

			}
			else
			{
				delete package_;
				cerr << "The package deleted [Package retransmission limit exceeded]" << endl;
			}
		}
	

	}
	//sprawdzanie czy nie wystapi�a kolizja!
	//int tmp = network_->SentPackageToReceivingStation((network_->ReturnChannel())->ReturnCurrentPackage());
	cerr << "ACK" << endl;
	//network_->AddACKFromReceivingStation(tmp);
}

double EndOfPackageTransmission::GetTime()
{
	return time_;
}

void EndOfPackageTransmission::Print()
{
	cerr << " End of package transmission: " << time_  << endl;
}
