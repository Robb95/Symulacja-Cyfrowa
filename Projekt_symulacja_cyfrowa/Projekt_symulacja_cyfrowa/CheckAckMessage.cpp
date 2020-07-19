#include "CheckAckMessage.h"

CheckAckMessage::CheckAckMessage(WirelessNetwork* network, TimeEventList* list, double time,int id_base_station)
{
  network_ = network;
  id_base_station_ = id_base_station;
  time_ = time;
  list_ = list;

}

void CheckAckMessage::Execute()
{
  ofstream save("InitialPhase.txt", ios_base::app);
  save << network_->GetSystemTime() << " " << network_->GetInitialPhase() << endl;
  save.close();
    //Sprawdzenie czy wiadomosc ACK zosta³a dostarczona poprawnie (obs³uga b³êdu TER)
	if (!(network_->GetInfoAboutACKInReceivingStation(id_base_station_))) 
	{//Nie dotara wiadomosc ACK
    //cerr << id_base_station_ << endl;
	package_ = network_->GetPackageTer(id_base_station_);
		if (package_->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision()) // sprawdzanie czy pakiet przekroczy³ maksymaln¹ liczbê retransmisji
		{
      if (network_->GetTypeInfo() == 2)
      {
        if (network_->GetTypePrint() == 1)
        {
          cerr << "Packet sent for retransmission : " << id_base_station_ << endl;
        }
        else
        {
          ofstream save("logs.txt", ios_base::app);
          save << "Packet sent for retransmission : " << id_base_station_ << endl;
          save.close();
        }
      }
		package_->IncrementLR();
    //list_->DeleteCheckChannel(id_base_station_);
    int temp = 2 ^ package_->ReturnNumberCurrentRetransmission() - 1;
    int seed = network_->GetSeedForTimeTransmission(id_base_station_);
    double time = time_ + network_->UniformGeneratorRange(temp, 0, seed, id_base_station_);
    TimeEvent* event_ = new CheckingTheChannelBusy(network_, list_, package_->ReturnIdBaseStation(), time, false);
    list_->AddTimeEvent(event_);
		network_->SentPackageToRetransmission(package_); 
		}
		else // przekroczona iloœæ dostêpnych retransmisji - nale¿y usun¹æ pakiet
		{
        if (network_->GetTypeInfo() ==2)
        {
            if (network_->GetTypePrint() == 1)
            {
                cerr << "Packet with id: "<< package_->ReturnIdPackage() << " exceeded the allowable number of transmissions and was deleted from the system." << endl;
            }
            else
            {
                ofstream save("logs.txt", ios_base::app);
                save << "Packet with id: " << package_->ReturnIdPackage() << " exceeded the allowable number of transmissions and was deleted from the system." << endl;
                save.close();
            }
        }
        network_->AddErrorRate(package_->ReturnIdBaseStation());
        network_->DeleteBaseStationCheckingChannel(package_->ReturnIdBaseStation());
		delete package_;
		}
	}
	else//poprawnie dostarczona wiadomosc ACK
	{
    if (network_->GetTypeInfo() == 2)
    {
      if (network_->GetTypePrint() == 1)
      {
        cerr << "The ACK message was delivered correctly to the base station with id: "<< id_base_station_ << endl;

      }
      else
      {
        ofstream save("logs.txt", ios_base::app);
        save << "The ACK message was delivered correctly to the base station with id: " << id_base_station_ << endl;
        save.close();
      }
    }
    package_ = network_->GetPackageTer(id_base_station_);
    network_->IncrementAllPackage();
    network_->AddAverageRetransmission(package_->ReturnNumberCurrentRetransmission());
    network_->AddAverageBufforTime(package_->GetAvergeExitBuffor());
    network_->AddAverageFinishTime(package_->GetAverageReceiving());
	}
}

double CheckAckMessage::GetTime()
{
  return time_;
}

void CheckAckMessage::Print()
{
  if (network_->GetTypeInfo() <3)
  {
    if (network_->GetTypePrint() == 1)
    {
      cerr << "Checking if the message ACK correctly arrived at the base station with id: "<<id_base_station_<<" scheduled in time: " << time_ << endl;
    }
    else
    {
      ofstream save("logs.txt", ios_base::app);
      save << "Checking if the message ACK correctly arrived at the base station with id: " << id_base_station_ << " scheduled in time: " << time_ << endl;
      save.close();
    }
  }
}

int CheckAckMessage::ReturnId()
{
  return id_;
}

int CheckAckMessage::ReturnIdBaseStation()
{
  return -1;
}
