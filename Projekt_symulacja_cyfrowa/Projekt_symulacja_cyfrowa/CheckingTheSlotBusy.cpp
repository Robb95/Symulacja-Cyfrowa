#include "CheckingTheSlotBusy.h"

void CheckingTheSlotBusy::Ececute()
{
	if (network_->GetCheckingTheChannelBusy())
	{
		unsigned size_of_vector = network_->GetSizeOfVector();
		int id_actual_element;
		for (unsigned i = 0; i < size_of_vector; i++)
		{
			id_actual_element = network_->GetBaseStationWaitingNewSlot(i);
			PT_ = rand() % 10 + 1;
			if (PT_ <= 4) //wysylamy 
			{
				if (network_->GetCheckingTheChannelBusy())
				{
					network_->SentPackageBaseStationToRecivingStation(id_actual_element);
					network_->DeleteBaseStationWaitingNewSlot(i); //zaplanuj wystapienie kolejnej szczeliny czasowej
					break;
				}
				else  //wystapienie zdarzenia warunkowego, kolizja
				{
					Channel* tmp = network_->ReturnChannel();
					Package* tmp2 = tmp->ReturnCurrentPackage();
					tmp->DeleteCurrentPackage();
					if (tmp2->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision())
					{
						tmp2->IncrementLR();
						network_->SentPackageToRetransmission(tmp2); //zaplanuj kolejne zdarzenie czasowe, wygenerowanie CRP
						
					}
					else
					{
						delete tmp2;
						cerr << "The package deleted [Package retransmission limit exceeded]" << endl;
					}

					tmp2 = network_->GetPackageFromBaseStation(id_actual_element);

					if (tmp2->ReturnNumberCurrentRetransmission() < network_->ReturnkAmountOfRetransmision())
					{
						tmp2->IncrementLR();
						network_->SentPackageToRetransmission(tmp2); //zaplanuj kolejne zdarzenie czasowe, wygenerowanie CRP

					}
					else
					{
						delete tmp2;
						cerr << "The package deleted [Package retransmission limit exceeded]" << endl;
					}
				}
				
				
			}

			else //zaplanuj wystapienie kolejnej szczeliny czasowej
			{

			}

		}

	}
	else //zaplanuj wystapienie kolejnej szczeliny czasowej
	{

	}
}

void CheckingTheSlotBusy::Print()
{
	cerr << " Checking the slot busy: " << time_ << endl;
}
