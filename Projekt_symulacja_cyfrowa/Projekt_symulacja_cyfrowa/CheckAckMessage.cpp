#include "CheckAckMessage.h"

CheckAckMessage::CheckAckMessage(WirelessNetwork* network, double time,int id_base_station)
{
  network_ = network;
  id_base_station_ = id_base_station;
  time_ = time;

}

void CheckAckMessage::Execute()
{
    //Sprawdzenie czy wiadomosc ACK zosta³a dostarczona poprawnie (obs³uga b³êdu TER)
	if (!(network_->GetInfoAboutACKInReceivingStation(id_base_station_))) 
	{//Nie
	package_ = network_->GetPackageTer(id_base_station_);
		if (package_->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision()) // sprawdzanie czy pakiet przekroczy³ maksymaln¹ liczbê retransmisji
		{
		package_->IncrementLR();
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
		cerr << "The ACK message was delivered correctly. " << endl;
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
