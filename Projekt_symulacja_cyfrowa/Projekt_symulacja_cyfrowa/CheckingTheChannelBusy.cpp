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
	if (network_->GetTypeInfo() ==2 )
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "Checking channel status by base station with id: " << id_base_station_ << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "Checking channel status by base station with id: " << id_base_station_ << endl;
			save.close();
		}
	}
	if (network_->GetCheckingTheChannelBusy())   //KANAL WOLNY sprawdzay obecn¹ szczeline czasow¹ czy stacja ma wys³aæ pakiet 
	{
		PT_ = rand()%10+1;
		if (PT_ <= 4) //wysylamy
		{
			if (network_->GetTypeInfo() == 2)
			{
				if (network_->GetTypePrint() == 1)
				{
					cerr << "The packet should be sent (PT<0.4) by the base station with id: " << id_base_station_ << endl;
				}
				else
				{
					ofstream save("logs.txt", ios_base::app);
					save << "The packet should be sent (PT<0.4) by the base station with id: " << id_base_station_ << endl;
					save.close();
				}
			}
			network_->AddToBaseStationWaitingNewSlot(id_base_station_);
			/*
			network_->SentPackageBaseStationToRecivingStation(id_base_station_,time_);
			int seed = network_->GetSeedForTimeTransmission(id_base_station_);
			time_temp_ = network_->UniformGeneratorRange(10,1,seed,id_base_station_);
			event_ = new EndOfPackageTransmission(network_, list_, time_temp_+time_);
			list_->AddTimeEvent(event_);
			event_ = new CheckAckMessage(network_, list_,(time_temp_+1+time_), id_base_station_);
			list_->AddTimeEvent(event_);
			*/
		}
		else //nie wysylamy, planujemy kolejn¹ próbê przes³ania pakietu na kolejn¹ woln¹ szczeline
		{
			if (network_->GetTypeInfo() == 2)
			{
				if (network_->GetTypePrint() == 1)
				{
					cerr << "The packet should NOT be sent (PT<0.4) by the base station with id: " << id_base_station_ << endl;
				}
				else
				{
					ofstream save("logs.txt", ios_base::app);
					save << "The packet should NOT be sent (PT<0.4) by the base station with id: " << id_base_station_ << endl;
					save.close();
				}
			}			
			network_->AddToBaseStationWaitingNewSlot(id_base_station_);
		}
	}
	else // zaplanuj kolejne zdarzenie czasowe (sprawdzenie zajetosci kanalu), KANAL ZAJETY 
	{
		if (network_->GetTypeInfo() == 2)
		{
			if (network_->GetTypePrint() == 1)
			{
				cerr << "Chanel was busy. " << id_base_station_ << endl;
			}
			else
			{
				ofstream save("logs.txt", ios_base::app);
				save << "Chanel was busy. "  << id_base_station_ << endl;
				save.close();
			}
		}
		if (first_check_ == false)//stacja bazowa sprawdza kana³ pierwszy raz i odrazu jest zajêty - kolejne sprawdzenie po 0.5 ms
		{
			TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_base_station_, time_ + 0.5, false);
			list_->AddTimeEvent(new_time_event);
		}
		else// stacja bazowa sprawdza³a kana³ i sta³ siê zajêty w kolejnej szczelinie czasowej - kolejne sprawdzanie po 1 ms
		{
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
	if (network_->GetTypeInfo() < 3)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "Channel check by base station with id: " << id_base_station_ << " time: " << time_ << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "Channel check by base station with id: " << id_base_station_ << " time: " << time_ << endl;
			save.close();
		}
	}
}

int CheckingTheChannelBusy::ReturnId()
{
	return id_;
}

int CheckingTheChannelBusy::ReturnIdBaseStation()
{
	return id_base_station_;
}
