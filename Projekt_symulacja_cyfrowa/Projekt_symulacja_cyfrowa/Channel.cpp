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
			
			current_package_.erase(current_package_.begin() + i);
			if (current_package_.empty())
			{
				channel_availability_ = true;	// do sprawdzenia w razie kolizji warunek dodaæ !!
			}
			return temp_;
		}
	}
	cerr << " ERROR on channel, there was no package with the specified id. " << endl;
}

void Channel::DeleteCurrentPackage(int id)
{
	//..for(unsigned)
	//current_package_ = nullptr;
}

bool Channel::GetCheckingTheChannelBusy()
{
	return channel_availability_;
}

void Channel::AddPackageToChannel(Package* current_package)
{
	current_package_.push_back(current_package);
	channel_availability_ = false;
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
