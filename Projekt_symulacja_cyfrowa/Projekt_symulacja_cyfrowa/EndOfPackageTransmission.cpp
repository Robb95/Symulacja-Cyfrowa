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
		
		
		//zdarzenie warunkowe wys³anie wiadomoœci ACK oraz zaplanowanie zdarzenia czasowego konca przesy³ania wiadomoœci ACK
		network_->AddPackageToReceivingStation(id_base_station_, package_);
		int seed = network_->GetSeedForChannel();
		if (network_->ZeroOneGenerator(0.8, seed,-1))
		{
			package_->SaveReceivingTime(time_);
			network_->DeleteBaseStationCheckingChannel(package_->ReturnIdBaseStation());
			network_->AddAllRate(id_base_station_); //zmienna zapisujaca poprawnie dostarczone pakiety
			channel_->SendAckMessage();
			event_ = new FinishSendingAckChannel(network_, id_base_station_, time_ + 1);
			list_->AddTimeEvent(event_);
			//event_ = new CheckingTheChannelBusy(network_, list_, id_base_station_, time_ + 0.5, false);
			//list_->AddTimeEvent(event_);

		}
		else
		{


			if (network_->GetTypeInfo() ==2 )
			{
				if (network_->GetTypePrint() == 1)
				{
					cerr << "Incorrectly sent packet through the channel from : " << id_base_station_  << endl;
				}
				else
				{
					ofstream save("logs.txt", ios_base::app);
					save << "Incorrectly sent packet through the channel from : " << id_base_station_ << endl;
					save.close();
				}
			}
		}
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
				double time= time_ + (((rand() % 10) + 1) * (rand() % 2 ^ package_->ReturnNumberCurrentRetransmission() - 1));
				event_ = new CheckingTheChannelBusy(network_, list_, package_->ReturnIdBaseStation(), time, false);
				list_->AddTimeEvent(event_);
				network_->SentPackageToRetransmission(package_);

			}
			else //przekroczona liczba retransmisji
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
					network_->AddErrorRate(package_->ReturnIdBaseStation());
					network_->DeleteBaseStationCheckingChannel(package_->ReturnIdBaseStation());
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

int EndOfPackageTransmission::ReturnIdBaseStation()
{
  return -1;
}
