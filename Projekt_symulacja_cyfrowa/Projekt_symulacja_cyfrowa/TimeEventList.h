#ifndef TIMEEVENTLIST_H
#define TIMEEVENTLIST_H
#include "TimeEvent.h";
#include "WirelessNetwork.h";
class TimeEventList
{
public:
	void AddTimeEvent(TimeEvent* event);        //add a new element on the TimeEventList
	TimeEvent* GetFirst();			            //get first element from TimeEventList
	void PrintTimeEventList();	//print elements from TimeEventList
private:
	TimeEvent* first_;
	TimeEvent* last_;
	TimeEvent* temp_;
};
#endif
