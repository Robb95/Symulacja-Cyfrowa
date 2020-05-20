#include "CheckingTheSlotBusy.h"
// Zdarzenie czasowe rozpocz�cie nowej szczeliny czasowej w tym zdarzeniu nale�y:
//sprawdzi� czy jaka� stacja bazowa oczekuje nowej szczeliny czasowej aby rozpocz�� transmisje z prawdopodobie�stwem PT = 0,4
CheckingTheSlotBusy::CheckingTheSlotBusy(WirelessNetwork* network, double time, TimeEventList* list)
{
	network_ = network;
	time_ = time;
	list_ = list;
}

void CheckingTheSlotBusy::Execute()
{
	event_ = new CheckingTheSlotBusy(network_, time_ + network_->GetCSCTime(), list_);
	list_->AddTimeEvent(event_);
	if (network_->GetTypeInfo() == 2)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "New time slot. " << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "New time slot" << endl;
			save.close();
		}
	}
		if (network_->GetCheckingTheChannelBusy())// ponowne sprawdzenie statusu kana�u w nowej szczelinie czasowej
		{
			if (network_->GetSizeOfVector() != 0)
			{// Warunek ze je�li wektor stacji oczekuj�cych na kolejna szczeline czasowa jest pusty to ma si� nic nie dzia�
				
				for (unsigned i = 0; i < network_->GetSizeOfVector(); i++)
				{
					id_actual_element_ = network_->GetBaseStationWaitingNewSlot(i);
					PT_ = rand() % 10 + 1;
					if (PT_ <= 4) //wysylamy 
					{
						if (network_->GetTypeInfo() == 2)
						{
							if (network_->GetTypePrint() == 1)
							{
								cerr << "The packet should be sent (PT<0.4) by the base station with id: " << id_actual_element_ << endl;
							}
							else
							{
								ofstream save("logs.txt", ios_base::app);
								save << "The packet should be sent (PT<0.4) by the base station with id: " << id_actual_element_ << endl;
								save.close();
							}
						}
						network_->SentPackageBaseStationToRecivingStation(id_actual_element_,time_);
						int seed = network_->GetSeedForTimeTransmission(id_actual_element_);
						time_temp_ = network_->UniformGeneratorRange(10, 1, seed, id_actual_element_);
						event_ = new EndOfPackageTransmission(network_, list_, time_temp_ + time_);
						list_->AddTimeEvent(event_);
						event_ = new CheckAckMessage(network_,list_, time_temp_ + time_ + 1, id_actual_element_);
						list_->AddTimeEvent(event_);
						temp_vector_for_delete_elemnts_.push_back(i);
					}
					else  //nie wysy�amy pakietu 
					{
						if (network_->GetTypeInfo() == 2)
						{
							if (network_->GetTypePrint() == 1)
							{
								cerr << "the package should not be sent" << id_actual_element_ << endl;
							}
							else
							{
								ofstream save("logs.txt", ios_base::app);
								save << "the package should not be sent" << id_actual_element_ << endl;
								save.close();
							}
						}
					}
				}
				for (unsigned i = 0; i <temp_vector_for_delete_elemnts_.size(); i++)
				{
					sort(temp_vector_for_delete_elemnts_.begin(), temp_vector_for_delete_elemnts_.end());
					network_->DeleteBaseStationWaitingNewSlot(temp_vector_for_delete_elemnts_[temp_vector_for_delete_elemnts_.size()-i-1]);
				}
				temp_vector_for_delete_elemnts_.clear();
				}
			else// brak czekajacych stacji do nadania
			{
				if (network_->GetTypeInfo() == 2)
				{
					if (network_->GetTypePrint() == 1)
					{
						cerr << "No base station was waiting for a new slot" << endl;
					}
					else
					{
						ofstream save("logs.txt", ios_base::app);
						save << "No base station was waiting for a new slot" << endl;
						save.close();
					}
				}
			}
		

	}
	else // Kana� w nowej szczeinie czasowej by� zaj�ty nale�y wi�c usun�� z wektora stacje czekaj�ce na kolejn� szczeline czasow� i doda� zdrzenie czasowe nas�uchiwania kana�u
	{
		
		if (network_->GetSizeOfVector() != 0) {
			for (unsigned i = 0; i < network_->GetSizeOfVector(); i++)
			{
				// kana� sta� sie zajety i powinny sie pojawic zdarzenia nas�uchiwania kana�u
				id_actual_element_ = network_->GetBaseStationWaitingNewSlot(i);
				TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_actual_element_, time_ + 1, true);
				list_->AddTimeEvent(new_time_event);
				
			}
		}
		network_->ClearVector();
	}
}

double CheckingTheSlotBusy::GetTime()
{
	return time_;
}

void CheckingTheSlotBusy::Print()
{
	if (network_->GetTypeInfo() < 3)
	{
		if (network_->GetTypePrint() == 1)
		{
			cerr << "New time slot, time: "<<time_ << endl;
		}
		else
		{
			ofstream save("logs.txt", ios_base::app);
			save << "New time slot, time: "<<time_ << endl;
			save.close();
		}
	}
}

int CheckingTheSlotBusy::ReturnId()
{
	return id_;
}

int CheckingTheSlotBusy::ReturnIdBaseStation()
{
  return -1;
}
