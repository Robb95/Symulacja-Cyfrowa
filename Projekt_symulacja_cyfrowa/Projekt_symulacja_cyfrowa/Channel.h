#ifndef CHANNEL_H
#define CHANNEL_H

#include "Package.h";
#include <iostream>
#include <vector>
using namespace std;
class Channel
{
public:
	Channel(); // constructor
	~Channel() = default; // default desctructor
	Package* ReturnCurrentPackage(int id);
	void DeleteCurrentPackage(int id);
	bool GetCheckingTheChannelBusy();
	void AddPackageToChannel(Package* current_package);
	unsigned GetVectorSize();
	int GetIdPackageFromVector(int i);
	void SendAckMessage();
	void FinishAckMessage();
	void ClearVector();
	
private:
	bool channel_availability_; // variable determines if a channel is free
	bool message_sending_ACK_;
	bool collision_checking_; // variable determines whether a collision has occurred
	double transmission_time_; // variable describing the transmission time
	vector<Package*> current_package_; // pointer to the currently transmitted package
	Package* temp_;

};
#endif

