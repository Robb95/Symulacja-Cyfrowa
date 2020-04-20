#pragma once
class ReceivingStation
{
public:
    ReceivingStation(); // constructor
    ~ReceivingStation() = default; // default desctructor
private:
    int id_receiving_station_; //variable describing id of the receiving station
    bool confirmation_ACK_; // variable determining whether ACK confirmation was issued

};

