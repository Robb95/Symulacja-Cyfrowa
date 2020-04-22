#include "TimeEventList.h"

void TimeEventList::AddTimeEvent(TimeEvent* event)
{
	if (first_ == nullptr)
	{
		first_ = last_= event;
		return;
	}
	else if (last_->GetTime() < event->GetTime())
	{
		last_->next = event;
		event->previous = last_;
		last_ = event;
		return;
	}

	temp = first_;
	while (temp->next-> GetTime() < event->GetTime())
	{
		temp = temp->next;
	}
	temp->next->previous = event;
	event->next = temp->next;
	event->previous = temp;
	temp->next = event;
}

TimeEvent* TimeEventList::GetFirst()
{
	if (first_ != nullptr)
	{
		temp = first_;
		first_= first_->next;
		return temp;
	}
}

void TimeEventList::PrintTimeEventList()
{
	temp = first_;
	while (temp !=last_)
	{
		temp->Print();
		temp = temp->next;
	}
	temp -> Print();
	
}