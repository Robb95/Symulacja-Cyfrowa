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
	// TUTAJ DODAÆ MECHANIZM ODPOWIEDNIEGO WYSWIETALANA
	cerr << "Generowanie pakietu w staci o id: " << id_base_station_ << " czas: " << time_ << endl;
	Package* packet = new Package(id_base_station_,network_->GetIdGeneratedPackage());
	network_->GenerateSentPackage(packet,id_base_station_);
	TimeEvent* genarte_new_package = new GeneratePackage(network_, time_+5, id_base_station_, event_);
	event_->AddTimeEvent(genarte_new_package);
	//zaplanowaæ zdarenie czasowe sprawdzenia zajêtoœci kana³u. Przy wygenerwoaniu pakietu sprawdzenie kana³u odbywa siê natychmiastowo
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
	cerr << " Generate package: "<< time_ << "Id base station: "<< id_base_station_ << endl;
}
