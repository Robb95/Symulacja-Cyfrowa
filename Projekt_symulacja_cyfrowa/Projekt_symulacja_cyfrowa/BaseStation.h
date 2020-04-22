#ifndef BASESTATION_H
#define BASESTATION_H
#include <queue>
#include "Package.h"

using namespace std;
class BaseStation
{
public:
    BaseStation(int id);  // constructor
    ~BaseStation() = default; // default desctructor
    void AddToBaseStation(Package* packet);
    void SetPackageToRetransmission(Package* get_package_to_retransmission);
    Package* SentPackageBaseStationToReceivingStation();
   
    
private:
    int id_base_station_; // variable describing the number of the base station
    const int kCTIZ_time_=5; // constant describing ACK pickup time
    double CGPK_rand_; // random variable describing the package generation time
    queue<Package*> package_; // queue that stores ready packages to be sent
    bool start_transmiting_; // variable specifying the start of transmission by the base station
    Package* get_package_to_retransmission_; // pointer one the package ready to rertansmission
    Package* tmp;
};
#endif

