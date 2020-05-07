#ifndef PACKAGE_H
#define PACKAGE_H

class Package
{
public:
	Package(int id_base_station, int id_package);	// constructor
	~Package() = default; // default desctructor
	int ReturnNumberCurrentRetransmission();
	int ReturnIdBaseStation();
	void IncrementLR();
	int ReturnIdPackage();
private:
	int id_package_;  //variable that specifies the id package
	int number_current_retransmission_; // variable specifies the number of the current retransmission
	int id_source_transmiter_; // variable describing the id of the base station from which the package was sent
	double average_waiting_time_; // variable storing the average package wait time
	int id_base_station_; // zmienna przechowuj¹ca informacje z której stacji bazowej zosta³ wys³any pakiet
};
#endif

