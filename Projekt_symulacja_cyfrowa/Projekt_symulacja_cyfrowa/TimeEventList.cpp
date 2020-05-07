#include "TimeEventList.h"

void TimeEventList::AddTimeEvent(TimeEvent* event)
{
	if (first_ == nullptr)
	{
		first_ = last_= event;
		return;
	}
	else if (first_->GetTime() >= event->GetTime())
	{
		event->next_ = first_;
		first_->previous_ = event;
		first_ = event;

	}
	else if (last_->GetTime() <= event->GetTime())
	{
		last_->next_ = event;
		event->previous_ = last_;
		last_ = event;
		return;
	}

	else {
		temp_ = first_;
		while (temp_->GetTime() <= event->GetTime())
		{
			temp_ = temp_->next_;
		}
		event->next_ = temp_;
		event->previous_ = temp_->previous_;
		temp_->previous_->next_ = event;
		temp_->previous_ = event;
	}
}

TimeEvent* TimeEventList::GetFirst()
{
	if (first_ != nullptr)
	{
		temp_ = first_;
		first_= first_->next_;
		return temp_;
	}
}

void TimeEventList::PrintTimeEventList()
{
	temp_ = first_;
	while (temp_ !=last_)
	{
		temp_->Print();
		temp_ = temp_->next_;
	}
	temp_ -> Print();
	
}