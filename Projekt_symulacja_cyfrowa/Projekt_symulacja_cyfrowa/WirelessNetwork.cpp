#include "WirelessNetwork.h"

WirelessNetwork::WirelessNetwork(int type_info, int type_print)
{
	id_of_the_currently_generated_package_ = 0;
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

WirelessNetwork::~WirelessNetwork()
{
	receiving_station_.clear();
	base_stations_.clear();
	delete channel_;
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

void WirelessNetwork::SentPackageBaseStationToRecivingStation(int id_base_station,double time)
{
	tmp=base_stations_[id_base_station]->SentPackageBaseStationToReceivingStation(time);
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
		
			return true;
		}
		
	}
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

int WirelessNetwork::GetIdGeneratedPackage()
{
	if(id_of_the_currently_generated_package_!=0)
	{ 
	return id_of_the_currently_generated_package_;
	}
	else
	{
		id_of_the_currently_generated_package_++;
		return 0;
	}
}

int WirelessNetwork::GetAmountNumberOfStations()
{
	return kNumberOfStations_;
}

double WirelessNetwork::GetSystemTime()
{
	return system_time_;
}

void WirelessNetwork::SetSystemTime(double time)
{
	system_time_ = time;
}

void WirelessNetwork::AddBaseStationCheckingChannel(int id)
{
	base_station_checking_channel_busy_.push_back(id);
}

bool WirelessNetwork::ChechkBaseStationCheckingChannel(int id)
{
	for (unsigned i = 0; i < base_station_checking_channel_busy_.size(); i++)
	{
		if (base_station_checking_channel_busy_[i] == id)
		{
			return true;
		}
	}
	return false;
}

void WirelessNetwork::DeleteBaseStationCheckingChannel(int id)
{
	for (unsigned i = 0; i < base_station_checking_channel_busy_.size(); i++)
	{
		if (base_station_checking_channel_busy_[i] == id)
		{
			base_station_checking_channel_busy_.erase(base_station_checking_channel_busy_.begin() + i);
		}
	}
}

double WirelessNetwork::GetCSCTime()
{
  return CSC_time_;
}

void WirelessNetwork::AddPackageToReceivingStation(int id,Package* packet)
{
	receiving_station_[id]->EndOfTransmitting(packet);
}

void WirelessNetwork::SetInfoAboutACKInReceivingStation(int id)
{
	base_stations_[id]->SetAckMessage();
}

bool WirelessNetwork::GetInfoAboutACKInReceivingStation(int id)
{
	return base_stations_[id]->GetAckMessage();
}

Package* WirelessNetwork::GetPackageTer(int id)
{
	return receiving_station_[id]->SendToRetransmission();
}

int WirelessNetwork::GetTypeInfo()
{
	return type_info_;
}

int WirelessNetwork::GetTypePrint()
{
	return type_print_;
}

bool WirelessNetwork::IsTheBuforInBaseStationIsEmpty(int id)
{
	return base_stations_[id]->TheBuforIsEmpty();
}

void WirelessNetwork::ClearVector()
{
	base_station_waiting_new_slot_.clear();
}

double WirelessNetwork::UniformGenerator(int& seed, int id, bool condition)
{
	int h = seed / kQ;
	seed = kA * (seed - kQ * h) - kR * h;
	if (condition == false)
	{
		if (id >= 0)seeds_for_time_transmission_[id] = seed;
		else channel_seed_=seed;
	}
	else
	{
		seeds_for_packet_generation_[id] = seed;
	}
	if (seed < 0)seed = seed + static_cast<int>(kM);


	return seed / kM;
}

double WirelessNetwork::UniformGeneratorRange(int maks, int min, int& seed,int id)
{
	return UniformGenerator(seed,id,false) * (maks - min) + min;
}

double WirelessNetwork::ExponentialGenerator(double lambda, int& seed, int id)
{
	return -(1.0 / lambda) * log(UniformGenerator(seed, id,true));
}

int WirelessNetwork::ZeroOneGenerator(double p, int& seed, int id)
{

	if (UniformGenerator(seed, -1, false) < p)return 1;
	else return 0;
}

double WirelessNetwork::UniformGenerator2(int& seed)
{
	int h = seed / kQ;
	seed = kA * (seed - kQ * h) - kR * h;
	if (seed < 0)seed = seed + static_cast<int>(kM);

	return seed / kM;
}

double WirelessNetwork::UniformGeneratorRange2(int maks, int min, int& seed)
{
	return UniformGenerator2(seed) * (maks - min) + min;
}

double WirelessNetwork::ExponentialGenerator2(double lambda, int& seed)
{
	return -(1.0 / lambda) * log(UniformGenerator2(seed));
}

void WirelessNetwork::AddSeedForTimeTransmision(int seed)
{
	seeds_for_time_transmission_.push_back(seed);
}

void WirelessNetwork::AddSeedForPacketGeneration(int seed)
{
	seeds_for_packet_generation_.push_back(seed);
}

void WirelessNetwork::AddSeedForChannel(int seed)
{
	channel_seed_ = seed;
}

void WirelessNetwork::PrintSeedsForGenerationPackage()
{
	for (int i = 0; i < seeds_for_packet_generation_.size(); i++)
	{
		cerr << i << " " << seeds_for_packet_generation_[i] << endl;
	}
}

int WirelessNetwork::GetSeedForTimeTransmission(int id)
{
	return seeds_for_time_transmission_[id];
}

int WirelessNetwork::GetSeedForGenerationPackage(int id)
{
	return seeds_for_packet_generation_[id];
}

int WirelessNetwork::GetSeedForChannel()
{
	return channel_seed_;
}

void WirelessNetwork::ResetStatistic()
{
	for (int i = 0; i < base_stations_.size(); i++)
	{
		base_stations_[i]->ResetStatistic();
	}
	
	average_retransmission_ = 0;
	all_package_ = 0;
	average_packet_buffor_ = 0;
	average_packet_finish_ = 0;
}

void WirelessNetwork::PrintStatistic()
{
	double sum=0;
	double max=0;
	for (int i = 0; i < base_stations_.size(); i++)
	{
		sum += base_stations_[i]->GetAverageErrorRate();
		if (max < base_stations_[i]->GetAverageErrorRate())
		{
			max = base_stations_[i]->GetAverageErrorRate();
		}
	}
	
	cerr << "Srednia pakietowa stopa bledow: " << sum / base_stations_.size() << endl;
	cerr << "Maksymalna pakietowa stopa bledow: " << max << endl;
	cerr << "Srednia liczba retransmisji pakietow: " << average_retransmission_ / all_package_ << endl;
	cerr << "Przeplywnosc systemu: " << all_package_ / (system_time_/1000) << endl;
	cerr << "Srednie opoznienie pakietu pojawienie sie w buforze - opuszczenie: " << average_packet_buffor_ / all_package_ << endl;
	cerr << "Sredni czas oczekiwania pojawienia sie w buforze - opuszczenie: " << average_packet_finish_ / all_package_ << endl;
}

void WirelessNetwork::AddErrorRate(int id)
{
	base_stations_[id]->AddErorRate();
}

void WirelessNetwork::AddAllRate(int id)
{
	base_stations_[id]->AddAllRate();
}

void WirelessNetwork::AddAverageRetransmission(int number)
{
	average_retransmission_ += number;
}

void WirelessNetwork::IncrementAllPackage()
{
	all_package_++;
	correctly_received_packet_++;
}

void WirelessNetwork::AddAverageBufforTime(double time)
{
	average_packet_buffor_ += time;
}

void WirelessNetwork::AddAverageFinishTime(double time)
{
	average_packet_finish_ += time;
}

int WirelessNetwork::GetPackageCondition()
{
	return correctly_received_packet_;
}

double WirelessNetwork::GetInitialPhase()
{
	double sum = 0;
	for (int i = 0; i < base_stations_.size(); i++)
	{
		sum += base_stations_[i]->GetAverageErrorRate();
	}
	return sum/kNumberOfStations_;
}









