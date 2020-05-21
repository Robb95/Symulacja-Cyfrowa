#include "GeneratePackage.h"

GeneratePackage::GeneratePackage(WirelessNetwork* network, double time,int id_base_station, TimeEventList* event)
{
	network_ = network;
	time_ = time;
	id_base_station_ = id_base_station;
	event_ = event;
	
}

void GeneratePackage::Execute()
{
	if (network_->GetTypeInfo() == 2)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "Generating a packet at the station with id: " << id_base_station_ << " time: " << time_ << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "Generating a packet at the station with id: " << id_base_station_ << " time: " << time_ << endl;
			save.close();
		}
	}

	Package* packet = new Package(id_base_station_,network_->GetIdGeneratedPackage());
	packet->SaveGeneratedTime(time_);
	network_->GenerateSentPackage(packet,id_base_station_);
	int seed = network_->GetSeedForGenerationPackage(id_base_station_);
	double time_for_generate_package = network_->ExponentialGenerator(0.1, seed, id_base_station_);
	TimeEvent* genarte_new_package = new GeneratePackage(network_, time_+5, id_base_station_, event_);
	event_->AddTimeEvent(genarte_new_package);
	//zaplanowaæ zdarzenie czasowe sprawdzenia zajêtoœci kana³u. Przy wygenerwoaniu pakietu sprawdzenie kana³u odbywa siê natychmiastowo
	if (!(network_->ChechkBaseStationCheckingChannel(id_base_station_)))// funkcja sprawdzaj¹ca czy dana stacja bazowa ju¿ sprawdza kana³
	{
		network_->AddBaseStationCheckingChannel(id_base_station_);
		genarte_new_package = new CheckingTheChannelBusy(network_, event_, id_base_station_, time_, false);
		event_->AddTimeEvent(genarte_new_package);
	}

}

double GeneratePackage::GetTime()
{
	return time_;
}

void GeneratePackage::Print()
{
	if (network_->GetTypeInfo() < 3)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "Generate package: " << time_ << " ID base station: " << id_base_station_ << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "Generate package time: " << time_ << " ID base station: " << id_base_station_ << endl;
			save.close();
		}
	}
}

int GeneratePackage::ReturnId()
{
	return id_;
}

int GeneratePackage::ReturnIdBaseStation()
{
  return -1;
}
