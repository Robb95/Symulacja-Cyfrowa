#include "Channel.h"

Channel::Channel()
{
	channel_availability_ = true;
	message_sending_ACK_ = false;
}

Package* Channel::ReturnCurrentPackage(int id)
{
	for(unsigned i=0; i<current_package_.size();i++)
	{ 
		if (current_package_[i]->ReturnIdPackage() == id)
		{
			temp_ = current_package_[i];
			channel_availability_ = true;// do sprawdzenia w razie kolizji warunek dodaæ !!
			current_package_.erase(current_package_.begin() + i);
			return temp_;
		}
	}
	cerr << " B£¥D w kanae nie by³o pakietu o okreœlonym id " << endl;
}

void Channel::DeleteCurrentPackage(int id)
{
	//..for(unsigned)
	//current_package_ = nullptr;
}

bool Channel::GetCheckingTheChannelBusy()
{
	cerr << "Sprawdzanie zajêtoœci kana³u 1-true " << channel_availability_;
	return channel_availability_;
}

void Channel::AddPackageToChannel(Package* current_package)
{
	cerr << "dodano pakiet do kana³u id pakeitu " << current_package->ReturnIdPackage() << endl;
	current_package_.push_back(current_package);
	channel_availability_ = false;
	cerr << " POWINNA NASTP¥PIC ZMIANA KANA£U " << channel_availability_ << endl;
}

unsigned Channel::GetVectorSize()
{
	return current_package_.size();
}

int Channel::GetIdPackageFromVector(int i)
{
	return current_package_[i]->ReturnIdPackage();
}

void Channel::SendAckMessage()
{
	channel_availability_ = false;
	message_sending_ACK_ = true;
}

void Channel::FinishAckMessage()
{
	channel_availability_ = true;
	message_sending_ACK_ = false;
}

void Channel::ClearVector()
{
	current_package_.clear();
}
