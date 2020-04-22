#ifndef WIRELESSNETWORK_H
#define WIRELESSNETWORK_H
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
    void SentPackageBaseStationToRecivingStation(int id_base_station);
    void AddToBaseStationWaitingNewSlot(int id);
    void DeleteBaseStationWaitingNewSlot(int id);
    int GetBaseStationWaitingNewSlot(int id);
    unsigned GetSizeOfVector();
    int SentPackageToReceivingStation(Package* current_package);
    Package* GetPackageFromBaseStation(int id_base_station);
    void AddACKFromReceivingStation(int id);
    bool ACKConfirmBaseStation(int id);
private:
    double system_time_; // variable describing the overall system time
    const int kNumberOfStations=20; // constant describing the number of base stations
    vector<BaseStation*> base_stations_; // vector that stores pointers to each base station
    Channel* channel_; // variable describing pointer on the channel
    vector<ReceivingStation*> receiving_station_; // vector that stores pointers to each receiving station
    const int kAmountOfRetransmission=5; // constant describing the number of retransmissions allowed
    Package* tmp;
    vector<int> base_station_waiting_new_slot_;  //wektor przechowuj¹cy id stacji bazowych,ktore czekaja na wolna szczeline
    vector<int> ACK_confirm_;                      //wektor przechowujacy potwierdzenia ACK
};

#endif;

