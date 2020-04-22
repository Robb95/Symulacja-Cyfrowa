#include "WirelessNetwork.h"

WirelessNetwork::WirelessNetwork(int type_info, int type_print)
{
	for (int i = 0; i < kNumberOfStations_; i++)
	{
		BaseStation* base_station_tmp = new BaseStation(i);
		base_stations_.push_back(base_station_tmp);
	}

	for (int i = 0; i < kNumberOfStations_; i++)
	{
		ReceivingStation* receiving_station_tmp = new ReceivingStation(i);
		receiving_station_.push_back(receiving_station_tmp);
	}

	channel_ = new Channel();
	system_time_ = 0;


	type_info_ = type_info;
	type_print_ = type_print;

	this->PrintInfoAboutWirelessNetwork();

}



void WirelessNetwork::GenerateSentPackage(Package* packet, int id_base_station)
{
	base_stations_[id_base_station]->AddToBaseStation(packet);
}

int WirelessNetwork::ReturnkAmountOfRetransmision()
{
	return kAmountOfRetransmission;
}

Channel* WirelessNetwork::ReturnChannel()
{
	return channel_;
}

void WirelessNetwork::SentPackageToRetransmission(Package* get_package_to_retransmission)
{
	base_stations_[get_package_to_retransmission->ReturnIdBaseStation()]->SetPackageToRetransmission(get_package_to_retransmission);
}

bool WirelessNetwork::GetCheckingTheChannelBusy()
{
	return channel_->GetCheckingTheChannelBusy();
}

void WirelessNetwork::SentPackageBaseStationToRecivingStation(int id_base_station)
{
	tmp=base_stations_[id_base_station]->SentPackageBaseStationToReceivingStation();
	channel_->AddPackageToChannel(tmp);
}

void WirelessNetwork::AddToBaseStationWaitingNewSlot(int id)
{
	base_station_waiting_new_slot_.push_back(id);
}

void WirelessNetwork::DeleteBaseStationWaitingNewSlot(int id)
{
	base_station_waiting_new_slot_.erase(base_station_waiting_new_slot_.begin()+id);
}

int WirelessNetwork::GetBaseStationWaitingNewSlot(int id)
{
	return base_station_waiting_new_slot_[id];
}

unsigned WirelessNetwork::GetSizeOfVector()
{
	return base_station_waiting_new_slot_.size();
}

int WirelessNetwork::SentPackageToReceivingStation(Package* current_package)
{
	int tmp = current_package->ReturnIdBaseStation();
	receiving_station_[tmp]->EndOfTransmitting(current_package);
	return tmp;
}

Package* WirelessNetwork::GetPackageFromBaseStation(int id_base_station)
{
	return base_stations_[id_base_station]->SentPackageBaseStationToReceivingStation();
}

void WirelessNetwork::AddACKFromReceivingStation(int id)
{
	ACK_confirm_.push_back(id);
}

bool WirelessNetwork::ACKConfirmBaseStation(int id)
{
	for (unsigned i=0; i < ACK_confirm_.size(); i++)
	{
		if (ACK_confirm_[i] == id)
		{
			ACK_confirm_.erase(ACK_confirm_.begin() + i);
			cerr << "Pakiet zostal poprawnie dostarczony" << endl;
			return true;
		}
		
	}
	cerr << "Pakiet nie zostal poprawnie dostarczony" << endl;
	return false;
}

void WirelessNetwork::PrintInfoAboutWirelessNetwork()
{
	if (type_info_ == 1)
	{
		if (type_print_ == 1)
		{
			cerr << "System initialization: " << endl;
			cerr << "Number of base stations and receiving station: " << kNumberOfStations_ << endl;
		}
		else
		{
			ofstream save("debug.txt", ios_base::app);

			save << "System initialization: " << endl;
			save << "Number of base stations and receiving station: " << kNumberOfStations_ << endl;
			save.close();
		}
	}
	else if (type_info_ == 2)
	{
		if (type_print_ == 1)
		{
			cerr << "System initialization: " << endl;
			cerr << "Number of base stations and receiving station: " << kNumberOfStations_ << endl;
		}
		else
		{
			ofstream save("debug.txt", ios_base::app);

			save << "System initialization: " << endl;
			save << "Number of base stations and receiving station: " << kNumberOfStations_ << endl;
			save.close();
		}
	}
}









