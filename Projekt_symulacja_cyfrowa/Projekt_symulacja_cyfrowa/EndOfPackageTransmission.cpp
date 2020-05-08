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
	cerr << temp_ << endl;
	if (temp_ <= 1)// brak kolizji (przesy³amy wiadomoœæ ACK)
	{
		package_ = channel_->ReturnCurrentPackage(channel_->GetIdPackageFromVector(0));
		id_base_station_ = package_->ReturnIdBaseStation();
		if (network_->GetTypeInfo() < 3)
		{
			if (network_->GetTypePrint() == 1)
			{
				cerr << "The package was delivered without collision from the station with id : " << id_base_station_ << " package has id : " << package_->ReturnIdPackage() << endl;
			}
			else
			{
				ofstream save("logs.txt", ios_base::app);
				save << "The package was delivered without collision from the station with id : " << id_base_station_ << " package has id : " << package_->ReturnIdPackage() << endl;
				save.close();
			}
		}
		
		network_->AddPackageToReceivingStation(id_base_station_, package_);
		//zdarzenie warunkowe wys³anie wiadomoœci ACK oraz zaplanowanie zdarzenia czasowego konca przesy³ania wiadomoœci ACK
		channel_->SendAckMessage();
		event_ = new FinishSendingAckChannel(network_, id_base_station_, time_ + 1);
		list_->AddTimeEvent(event_);
	}
	else // wyst¹pi³a kolizja (zwracamy pakiety do retransmisji)
	{
		list_->DeleteCheckACK();
		while (channel_->GetVectorSize())
		{
			package_ =channel_->ReturnCurrentPackage(channel_->GetIdPackageFromVector(0));
			if (network_->GetTypeInfo() < 3)
			{
				if (network_->GetTypePrint() == 1)
				{
					cerr << "There is a collision in the channel, sent packets for retransmission. "  << endl;
				}
				else
				{
					ofstream save("logs.txt", ios_base::app);
					save << "There is a collision in the channel, sent packets for retransmission. "  << endl;
					save.close();
				}
			}
			if (package_->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision())
			{
				package_->IncrementLR();
				network_->SentPackageToRetransmission(package_);

			}
			else
			{
				if (network_->GetTypeInfo() == 2)
				{
					if (network_->GetTypePrint() == 1)
					{
						cerr << "Packet with id: " << package_->ReturnIdPackage() << " exceeded the allowable number of transmissions and was deleted from the system. " << endl;

					}
					else
					{
						ofstream save("logs.txt", ios_base::app);
						save << "Packet with id: " << package_->ReturnIdPackage() << " exceeded the allowable number of transmissions and was deleted from the system. " << endl;
						save.close();
					}
				}
				delete package_;
			}
		}
	}
}

double EndOfPackageTransmission::GetTime()
{
	return time_;
}

void EndOfPackageTransmission::Print()
{
	if (network_->GetTypeInfo() <3)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "End of package transmission : " << time_  << endl;

		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "End of package transmission : " << time_ << endl;
			save.close();
		}
	}
}

int EndOfPackageTransmission::ReturnId()
{
	return id_;
}
