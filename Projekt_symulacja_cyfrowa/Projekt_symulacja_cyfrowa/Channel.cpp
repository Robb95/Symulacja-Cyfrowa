#include "Channel.h"

Channel::Channel()
{
	
}

Package* Channel::ReturnCurrentPackage()
{
	if(current_package_==nullptr)
	{ 
		cerr << "Error: amount of current package = 0!";
	}
	
	else return current_package_;
}

void Channel::DeleteCurrentPackage()
{
	current_package_ = nullptr;
}

bool Channel::GetCheckingTheChannelBusy()
{
	return channel_availability_;
}
