#include "CheckingChannelStatusAfterRetransmission.h"

double CheckingChannelStatusAfterRetransmission::GetTime()
{
	return time_;
}

void CheckingChannelStatusAfterRetransmission::Print()
{
	cerr << " Checking channel status after retransmission: " << time_ << endl;
}
