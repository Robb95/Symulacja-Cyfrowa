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
    ~WirelessNetwork(); // default desctructor
    void GenerateSentPackage(Package* packet, int id_base_station);
    int ReturnkAmountOfRetransmision();
    Channel* ReturnChannel();
    void SentPackageToRetransmission(Package* get_package_to_retransmission);
    bool GetCheckingTheChannelBusy();
    void SentPackageBaseStationToRecivingStation(int id_base_station,double time);
    void AddToBaseStationWaitingNewSlot(int id);
    void DeleteBaseStationWaitingNewSlot(int id);
    int GetBaseStationWaitingNewSlot(int id);
    unsigned GetSizeOfVector();
    int SentPackageToReceivingStation(Package* current_package);

    void AddACKFromReceivingStation(int id);
    bool ACKConfirmBaseStation(int id);
    void PrintInfoAboutWirelessNetwork();
    int GetIdGeneratedPackage();
    int GetAmountNumberOfStations();
    double GetSystemTime();
    void SetSystemTime(double time);
    void AddBaseStationCheckingChannel(int id);
    bool ChechkBaseStationCheckingChannel(int id);
    void DeleteBaseStationCheckingChannel(int id);  //Nie zapomnieæ u¿yæ przy tymm jak stacja wyœle pakiet!
    double GetCSCTime();
    void AddPackageToReceivingStation(int id,Package* packet);
    void SetInfoAboutACKInReceivingStation(int id);
    bool GetInfoAboutACKInReceivingStation(int id);
    Package* GetPackageTer(int id);
    int GetTypeInfo();
    int GetTypePrint();
    bool IsTheBuforInBaseStationIsEmpty(int id);
    void ClearVector();
    double UniformGenerator(int& seed, int id, bool condition); // generowanie wartoœci z przedzia³u od 0-1 (u¿ywamy go do generowania wartoœci dla innych generatorów)
    double UniformGeneratorRange(int maks, int min, int& seed, int id);// generowanie wartoœci z przedzia³u min-max (u¿ywany do wyznaczania czasu transmisji pakietu)
    double ExponentialGenerator(double lambda, int& seed, int id); // generwoanie wartoœci wyk³adniczych w zale¿nosci od parametru lambda (u¿ywany do wyznaczania czasu po którym ma siê wygenerowaæ pakiet)
    int ZeroOneGenerator(double p, int& seed, int id);
    double UniformGenerator2(int& seed); // generowanie wartoœci z przedzia³u od 0-1 (u¿ywamy go do generowania wartoœci dla innych generatorów)
    double UniformGeneratorRange2(int maks, int min, int& seed);// generowanie wartoœci z przedzia³u min-max (u¿ywany do wyznaczania czasu transmisji pakietu)
    double ExponentialGenerator2(double lambda, int& seed); // generwoanie wartoœci wyk³adniczych w zale¿nosci od parametru lambda (u¿ywany do wyznaczania czasu po którym ma siê wygenerowaæ pakiet)
    void AddSeedForTimeTransmision(int seed);
    void AddSeedForPacketGeneration(int seed);
    void AddSeedForChannel(int seed);
    void PrintSeedsForGenerationPackage();
    int GetSeedForTimeTransmission(int id);
    int GetSeedForGenerationPackage(int id);
    int GetSeedForChannel();
    void ResetStatistic();
    void PrintStatistic();
    void AddErrorRate(int id);
    void AddAllRate(int id);
    void AddAverageRetransmission(int number);
    void IncrementAllPackage();
    void AddAverageBufforTime(double time);
    void AddAverageFinishTime(double time);
    int GetPackageCondition();
private:
    double system_time_; // variable describing the overall system time
    const int kNumberOfStations_=4; // constant describing the number of base stations
    vector<BaseStation*> base_stations_; // vector that stores pointers to each base station
    Channel* channel_; // variable describing pointer on the channel
    vector<ReceivingStation*> receiving_station_; // vector that stores pointers to each receiving station
    const int kAmountOfRetransmission=10; // constant describing the number of retransmissions allowed
    Package* tmp;
    vector<int> base_station_waiting_new_slot_;  //vector storing the id of base stations that are waiting for a free slot
    vector<int> ACK_confirm_;                    //vector storing ACK confirmations
    vector<int> base_station_checking_channel_busy_;
    int type_info_;
    int type_print_;
    int id_of_the_currently_generated_package_;
    const double CSC_time_=1;
    const double kM = 2147483647.0;
    static const int kA = 16807;
    static const int kQ = 127773;
    static const int kR = 2836;
    int channel_seed_;
    double average_retransmission_=0;
    int all_package_=0;
    double average_packet_buffor_ = 0;
    double average_packet_finish_ = 0;
    int correctly_received_packet_ = 0;
    vector<int> seeds_for_time_transmission_;
    vector<int> seeds_for_packet_generation_;



};
#endif;

