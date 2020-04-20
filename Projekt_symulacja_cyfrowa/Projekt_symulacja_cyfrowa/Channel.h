#pragma once

#include "Package.h";
#include <iostream>
using namespace std;
class Channel
{
public:
	Channel(); // constructor
	~Channel() = default; // default desctructor
	Package* ReturnCurrentPackage();
	void DeleteCurrentPackage();
private:
	bool channel_availability_; // variable determines if a channel is free
	bool collision_checking_; // variable determines whether a collision has occurred
	double transmission_time_; // variable describing the transmission time
	Package* current_package_; // pointer to the currently transmitted package

};

