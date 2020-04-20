#pragma once

#include "BaseStation.h";
#include "Channel.h";
#include "ReceivingStation.h";

class WirelessNetwork
{
public:
    WirelessNetwork(); // constructor
    ~WirelessNetwork() = default; // default desctructor
    void GenerateSentPackage(Package* packet, int id_base_station);
    int ReturnkAmountOfRetransmision();
    Channel* ReturnChannel();
    void SentPackageToRetransmission(Package* get_package_to_retransmission);
    bool GetCheckingTheChannelBusy();
private:
    double system_time_; // variable describing the overall system time
    const int kNumberOfStations=20; // constant describing the number of base stations
    vector<BaseStation*> base_stations_; // vector that stores pointers to each base station
    Channel* channel_; // variable describing pointer on the channel
    vector<ReceivingStation*> receiving_station_; // vector that stores pointers to each receiving station
    const int kAmountOfRetransmission=5; // constant describing the number of retransmissions allowed
};

