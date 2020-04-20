#pragma once
#include <queue>
#include "Package.h"

using namespace std;
class BaseStation
{
public:
    BaseStation();  // constructor
    ~BaseStation() = default; // default desctructor
    void AddToBaseStation(Package* packet);
private:
    int id_base_station_; // variable describing the number of the base station
    const int kCTIZ_time_=5; // constant describing ACK pickup time
    double CGPK_rand_; // random variable describing the package generation time
    queue<Package*> package_; // queue that stores ready packages to be sent
    bool start_transmiting_; // variable specifying the start of transmission by the base station

};

