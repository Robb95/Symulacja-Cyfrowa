#ifndef RECEIVINGSTATION_H
#define RECEIVINGSTATION_H
#include "Package.h"
class ReceivingStation
{
public:
    ReceivingStation(int id); // constructor
    ~ReceivingStation() = default; // default desctructor
    void EndOfTransmitting(Package* receiving_package);
    int AddACK();
private:
    Package* receiving_package_;
    int id_receiving_station_; //variable describing id of the receiving station
    bool confirmation_ACK_; // variable determining whether ACK confirmation was issued

};
#endif;
