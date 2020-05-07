#include "CheckingTheSlotBusy.h"
// Zdarzenie czasowe rozpoczêcie nowej szczeliny czasowej w tym zdarzeniu nale¿y:
//sprawdziæ czy jakaœ stacja bazowa oczekuje nowej szczeliny czasowej aby rozpocz¹æ transmisje z prawdopodobieñstwem Pt = 0,4
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
	if (network_->GetCheckingTheChannelBusy())// ponowne sprawdzenie statusu kana³u w nowej szczelinie czasowej
	{
		unsigned size_of_vector = network_->GetSizeOfVector();
		if (size_of_vector != 0) {// warunek ze jeœli vektor staci czekaj¹cych na kolejna szczeline czasowa jest pusty to ma siê nic nie dziaæ
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
				else  //nie wysy³amy pakietu
				{

				}

			}
		}
		else
		{
			cerr << "zadna stacja bazowa nie chce wys³aæ pakietu wiêc w tej szczelinie nic siê nie dzieje kana³ by³ wolny!" << endl;
		}
	}
	else // Kana³ w nowej szczeinie czasowej by³ zajêty nale¿y wiêc usun¹æ z wektora stacje czekaj¹ce na kolejn¹ szczeline czasow¹ i dodaæ zdrzenie czasowe nas³uchiwania kana³u
	{
		size_of_vector_ = network_->GetSizeOfVector();
		if (size_of_vector_ != 0) {
			for (unsigned i = 0; i < size_of_vector_; i++)
			{
				id_actual_element_ = network_->GetBaseStationWaitingNewSlot(i);
				cerr << "zapalnowanie kolejnego zdarzenia sprawdzania kana³u (kana³ sta³ siê zajêty po czasie)" << "id base station: " << id_actual_element_ << endl;
				TimeEvent* new_time_event = new CheckingTheChannelBusy(network_, list_, id_actual_element_, time_ + 1, true);
				list_->AddTimeEvent(new_time_event);
				network_->DeleteBaseStationWaitingNewSlot(i);
			}
			///dodac wszystkie stacje nadawacze ¿eby czeka³y na wolny kanal i odpuytywaly co 1 ms
		}
		else
		{
			cerr << "zadna stacja bazowa nie chce wys³aæ pakietu wiêc w tej szczelinie nic siê nie dzieje kana³ by³ zajêty!" << endl;
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
