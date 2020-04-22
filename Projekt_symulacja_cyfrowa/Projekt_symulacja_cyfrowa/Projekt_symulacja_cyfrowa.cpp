#include "BaseStation.h"
#include "Channel.h"
#include "Package.h"
#include "GeneratePackage.h"
#include "ReceivingStation.h"
#include "WirelessNetwork.h"
#include "TimeEvent.h"
#include "TimeEventList.h"
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
    cerr << "Choose space to display: " << endl;
    cerr << "1. Console" << endl;
    cerr << "2. Txt file" << endl;
    cerr << "Choose a number: "; cin >> type_print;
    while (!((type_print < 3) && (type_print > 0)))
    {
        cerr << "Wrong value! Choose a number(1-2): "; 
        cin >> type_print;
    }


    WirelessNetwork* wirelessnetwork = new WirelessNetwork( type_info, type_print);
    TimeEventList* timeeventlist = new TimeEventList();
    TimeEvent* timeevent = new GeneratePackage(wirelessnetwork,0,0,timeeventlist);
    timeeventlist->AddTimeEvent(timeevent);
    timeeventlist->PrintTimeEventList();
    return 0;
}


