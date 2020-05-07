#include "BaseStation.h"
#include "Channel.h"
#include "Package.h"
#include "GeneratePackage.h"
#include "ReceivingStation.h"
#include "WirelessNetwork.h"
#include "TimeEvent.h"
#include "TimeEventList.h"
#include "CheckingTheSlotBusy.h"
#include <iostream>
using namespace std;

int main()
{
    int type_info;
    cerr << "Choose type information to display: " << endl;
    cerr << "1. Standard" << endl;
    cerr << "2. Debug" << endl;
    cerr << "Choose a number: "; 
    cin >> type_info;
    while (!((type_info < 3) && (type_info > 0)))
    {
        cerr << "Wrong value! Choose a number(1-2): "; 
        cin >> type_info;
    }

    int type_print;
    cerr << "Select a display method : " << endl;
    cerr << "1. Console" << endl;
    cerr << "2. Txt file" << endl;
    cerr << "Choose a number: "; cin >> type_print;
    while (!((type_print < 3) && (type_print > 0)))
    {
        cerr << "Wrong value! Choose a number(1-2): "; 
        cin >> type_print;
    }
    bool step = false;
    cerr << "Do you want to choose a step mode? (0=no, 1=yes)" << endl;
    cin >> step;
    while (!((step <= 1) && (step >= 0)))
    {
      cerr << "Wrong value! Choose a number(1-2): ";
      cin >> step;
    }

    //inicjalizacja systemu
    WirelessNetwork* wireless_network = new WirelessNetwork( type_info, type_print);
    TimeEventList* time_event_list = new TimeEventList();
    //zaplanowanie pierwszych zdarzeń czasowych
    TimeEvent* time_event;
    for (int i = 0; i < wireless_network->GetAmountNumberOfStations(); i++)
    {
      time_event = new GeneratePackage(wireless_network, i+1, i, time_event_list);
      time_event_list->AddTimeEvent(time_event);
    }
    //time_event_list->PrintTimeEventList();
    time_event = new CheckingTheSlotBusy(wireless_network, 0, time_event_list); // pierwsza szczelina czasowa jest generowana z czasem zero
    time_event_list->AddTimeEvent(time_event);
    while(wireless_network->GetSystemTime() < 2000)
    {
      cin.get();
     time_event = time_event_list->GetFirst();
     wireless_network->SetSystemTime(time_event->GetTime());
     time_event->Execute();
     cerr << "Czas systemowy: " << wireless_network->GetSystemTime() << endl;
     cerr << "Zaplanowane zdarznia czasowe: " << endl;
     time_event_list->PrintTimeEventList();

     cerr << "-----------------------------------------" << endl;
     if (step == 1)
     {
       cin.get();
     }
    }
    return 0;
}


