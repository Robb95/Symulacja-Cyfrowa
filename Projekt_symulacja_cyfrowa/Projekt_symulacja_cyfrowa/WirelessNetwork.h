#ifndef WIRELESSNETWORK_H
#define WIRELESSNETWORK_H
#include "BaseStation.h";
#include "Channel.h";
#include "ReceivingStation.h";
#include <iostream>
#include <fstream>
using namespace std;

class WirelessNetwork
{
public:
    WirelessNetwork(int type_info, int type_print); // constructor
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
    void PrintInfoAboutWirelessNetwork();
    int GetIdGeneratedPackage();
    int GetAmountNumberOfStations();
    double GetSystemTime();
    void SetSystemTime(double time);
    void AddBaseStationCheckingChannel(int id);
    bool ChechkBaseStationCheckingChannel(int id);
    void DeleteBaseStationCheckingChannel(int id);//Nie zapomnieæ u¿yæ przy tymm jak stacja wyœle pakiet!
    double GetCSCTime();
    void AddPackageToReceivingStation(int id,Package* packet);
    void SetInfoAboutACKInReceivingStation(int id);
    bool GetInfoAboutACKInReceivingStation(int id);
    Package* GetPackageTer(int id);
private:
    double system_time_; // variable describing the overall system time
    const int kNumberOfStations_=3; // constant describing the number of base stations
    vector<BaseStation*> base_stations_; // vector that stores pointers to each base station
    Channel* channel_; // variable describing pointer on the channel
    vector<ReceivingStation*> receiving_station_; // vector that stores pointers to each receiving station
    const int kAmountOfRetransmission=5; // constant describing the number of retransmissions allowed
    Package* tmp;
    vector<int> base_station_waiting_new_slot_;  //vector storing the id of base stations that are waiting for a free slot
    vector<int> ACK_confirm_;                    //vector storing ACK confirmations
    vector<int> base_station_checking_channel_busy_;
    int type_info_;
    int type_print_;
    int id_of_the_currently_generated_package_;
    const double CSC_time_=1;
};

#endif;

