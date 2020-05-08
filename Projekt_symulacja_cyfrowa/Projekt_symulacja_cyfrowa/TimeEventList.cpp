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
		while (temp_->GetTime() < event->GetTime())
		{
			temp_ = temp_->next_;
			//if(temp_->GetTime() <= event->GetTime())
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

void TimeEventList::DeleteCheckACK()// to zdarzenie jest wywo³ywane tylko w momencie kiedy wyst¹pi³a kolizja
{

	temp_ = first_;
	condition_ = true;
	while (temp_!=last_)
	{
		if (temp_->ReturnId() == 1)
		{
			if (temp_ == first_)
			{
				first_ = temp_->next_;
				temp_->next_->previous_ = nullptr;
				temp_->next_ = nullptr;
				delete temp_;
				temp_ = first_;
				condition_ = false;
			}
			else
			{
				temp_->previous_->next_ = temp_->next_;
				temp_->next_->previous_ = temp_->previous_;
			}
		}
		else condition_ = true;
		if (condition_ ==true) {
			temp_ = temp_->next_;
		}
	}
	if (temp_->ReturnId() == 1)
	{
		last_ = temp_->previous_;
		temp_->previous_->next_ = nullptr;
		temp_->previous_ = nullptr;
		delete temp_;
		//temp_->next_->previous_ = temp_->previous_;
	}
}
