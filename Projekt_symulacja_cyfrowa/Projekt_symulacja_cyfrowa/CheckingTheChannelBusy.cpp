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
	cerr << "Kana� jest odpytywane przez stacje nadawcza o id: " << id_base_station_ << endl;
	if (network_->GetCheckingTheChannelBusy())   //KANAL WOLNY sprawdzay obecn� szczeline czasow� czy stacja ma wys�a� pakiet 
	{
		PT_ = rand()%10+1;
		if (PT_ <= 4) //wysylamy
		{
			cerr << " Pakiet powienien zosta� przes�any pt mniejsze badz rowne 0.4 " << endl;
			network_->SentPackageBaseStationToRecivingStation(id_base_station_);
			time_temp_ = (rand() % 10) + 1;
			event_ = new EndOfPackageTransmission(network_, list_, time_temp_);
			list_->AddTimeEvent(event_);
			event_ = new CheckAckMessage(network_, time_temp_+1, id_base_station_);
			list_->AddTimeEvent(event_);
			network_->DeleteBaseStationCheckingChannel(id_base_station_);
			// Doda� warunek ze je�eli nie jest pusty bufor to odrazu wygenerwa� zdarzenie ( do przemyslenia jeszcze xD)
		}
		else //nie wysylamy, planujemy kolejn� pr�b� przes�ania pakietu na kolejn� woln� szczeline
		{
			cerr << " Pakiet NIE powienien zosta� przes�any - czzekamy na nast�pn� szczeline czasow�. " << endl;
			network_->AddToBaseStationWaitingNewSlot(id_base_station_);
		}
	}
	else // zaplanuj kolejne zdarzenie czasowe (sprawdzenie zajetosci kanalu) KANAL ZAJETY 
	{
		if (first_check_ == false)//stacja bazowa sprawdza kana� pierwszy raz i odrazu jest zaj�ty - kolejne sprawdzenie po 0.5 ms
		{
			cerr << "zapalnowanie kolejnego zdarzenia sprawdzania kana�u (pierwszy raz)" << "id base station: "<<id_base_station_<< endl;
			TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_base_station_, time_ + 0.5, false);
			list_->AddTimeEvent(new_time_event);
		}
		else// stacja bazowa sprawdza�a kana� i sta� si� zaj�ty w kolejnej szczelinie czasowej - kolejne sprawdzanie po 1 ms
		{
			cerr << "zapalnowanie kolejnego zdarzenia sprawdzania kana�u (kana� sta� si� zaj�ty po czasie)" << "id base station: " << id_base_station_ << endl;
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
