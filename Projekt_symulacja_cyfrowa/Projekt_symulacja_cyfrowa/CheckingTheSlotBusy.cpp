#include "CheckingTheSlotBusy.h"
// Zdarzenie czasowe rozpocz�cie nowej szczeliny czasowej w tym zdarzeniu nale�y:
//sprawdzi� czy jaka� stacja bazowa oczekuje nowej szczeliny czasowej aby rozpocz�� transmisje z prawdopodobie�stwem Pt = 0,4
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
	cerr << " NOWA SZCZELINA CZASOWA!" << endl;
	if (network_->GetCheckingTheChannelBusy())// ponowne sprawdzenie statusu kana�u w nowej szczelinie czasowej
	{
		unsigned size_of_vector = network_->GetSizeOfVector();
		if (size_of_vector != 0) {// warunek ze je�li vektor staci czekaj�cych na kolejna szczeline czasowa jest pusty to ma si� nic nie dzia�
			int id_actual_element;
			for (unsigned i = 0; i < size_of_vector; i++)
			{
				id_actual_element = network_->GetBaseStationWaitingNewSlot(i);
				PT_ = rand() % 10 + 1;
				if (PT_ <= 4) //wysylamy 
				{
					network_->SentPackageBaseStationToRecivingStation(id_actual_element);
					time_temp_ = (rand() % 10) + 1;
					event_ = new EndOfPackageTransmission(network_, list_, time_temp_);
					list_->AddTimeEvent(event_);
					event_ = new CheckAckMessage(network_, time_temp_+1, id_actual_element);
					list_->AddTimeEvent(event_);
					network_->DeleteBaseStationWaitingNewSlot(i); //zaplanuj wystapienie kolejnej szczeliny czasowej
					//break;
				}
				else  //nie wysy�amy pakietu
				{

				}

			}
		}
		else
		{
			cerr << "zadna stacja bazowa nie chce wys�a� pakietu wi�c w tej szczelinie nic si� nie dzieje kana� by� wolny!" << endl;
		}
	}
	else // Kana� w nowej szczeinie czasowej by� zaj�ty nale�y wi�c usun�� z wektora stacje czekaj�ce na kolejn� szczeline czasow� i doda� zdrzenie czasowe nas�uchiwania kana�u
	{
		size_of_vector_ = network_->GetSizeOfVector();
		if (size_of_vector_ != 0) {
			for (unsigned i = 0; i < size_of_vector_; i++)
			{
				id_actual_element_ = network_->GetBaseStationWaitingNewSlot(i);
				cerr << "zapalnowanie kolejnego zdarzenia sprawdzania kana�u (kana� sta� si� zaj�ty po czasie)" << "id base station: " << id_actual_element_ << endl;
				TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_actual_element_, time_ + 1, true);
				list_->AddTimeEvent(new_time_event);
				network_->DeleteBaseStationWaitingNewSlot(i);
			}
			///dodac wszystkie stacje nadawacze �eby czeka�y na wolny kanal i odpuytywaly co 1 ms
		}
		else
		{
			cerr << "zadna stacja bazowa nie chce wys�a� pakietu wi�c w tej szczelinie nic si� nie dzieje kana� by� zaj�ty!" << endl;
		}
	}
}

double CheckingTheSlotBusy::GetTime()
{
	return time_;
}

void CheckingTheSlotBusy::Print()
{
	cerr << " Checking the slot busy: " << time_ << endl;
}
