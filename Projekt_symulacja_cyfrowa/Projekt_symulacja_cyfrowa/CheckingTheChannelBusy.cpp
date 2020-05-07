#include "CheckingTheChannelBusy.h"


CheckingTheChannelBusy::CheckingTheChannelBusy(WirelessNetwork* network, TimeEventList* list, int id_base_station,double time, bool first_check) 
{
	network_ = network;
	id_base_station_ = id_base_station;
	time_ = time;
	list_ = list;
	first_check_ = first_check;
}

void CheckingTheChannelBusy::Execute()
{
	cerr << "Kana³ jest odpytywane przez stacje nadawcza o id: " << id_base_station_ << endl;
	if (network_->GetCheckingTheChannelBusy())   //KANAL WOLNY sprawdzay obecn¹ szczeline czasow¹ czy stacja ma wys³aæ pakiet 
	{
		PT_ = rand()%10+1;
		if (PT_ <= 4) //wysylamy
		{
			cerr << " Pakiet powienien zostaæ przes³any pt mniejsze badz rowne 0.4 " << endl;
			network_->SentPackageBaseStationToRecivingStation(id_base_station_);
			time_temp_ = (rand() % 10) + 1;
			event_ = new EndOfPackageTransmission(network_, list_, time_temp_);
			list_->AddTimeEvent(event_);
			event_ = new CheckAckMessage(network_, time_temp_+1, id_base_station_);
			list_->AddTimeEvent(event_);
			network_->DeleteBaseStationCheckingChannel(id_base_station_);
			// Dodaæ warunek ze je¿eli nie jest pusty bufor to odrazu wygenerwaæ zdarzenie ( do przemyslenia jeszcze xD)
		}
		else //nie wysylamy, planujemy kolejn¹ próbê przes³ania pakietu na kolejn¹ woln¹ szczeline
		{
			cerr << " Pakiet NIE powienien zostaæ przes³any - czzekamy na nastêpn¹ szczeline czasow¹. " << endl;
			network_->AddToBaseStationWaitingNewSlot(id_base_station_);
		}
	}
	else // zaplanuj kolejne zdarzenie czasowe (sprawdzenie zajetosci kanalu) KANAL ZAJETY 
	{
		if (first_check_ == false)//stacja bazowa sprawdza kana³ pierwszy raz i odrazu jest zajêty - kolejne sprawdzenie po 0.5 ms
		{
			cerr << "zapalnowanie kolejnego zdarzenia sprawdzania kana³u (pierwszy raz)" << "id base station: "<<id_base_station_<< endl;
			TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_base_station_, time_ + 0.5, false);
			list_->AddTimeEvent(new_time_event);
		}
		else// stacja bazowa sprawdza³a kana³ i sta³ siê zajêty w kolejnej szczelinie czasowej - kolejne sprawdzanie po 1 ms
		{
			cerr << "zapalnowanie kolejnego zdarzenia sprawdzania kana³u (kana³ sta³ siê zajêty po czasie)" << "id base station: " << id_base_station_ << endl;
			TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_base_station_, time_ + 1, true);
			list_->AddTimeEvent(new_time_event);
		}
	}
}

double CheckingTheChannelBusy::GetTime()
{
	return time_;
}

void CheckingTheChannelBusy::Print()
{
	cerr << " Checking the channel busy: " << time_ << "id stacji bazowej: " << id_base_station_ << endl;
}
