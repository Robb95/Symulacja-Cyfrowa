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
    cerr << "3. Nothing" << endl;
    cerr << "Choose a number: "; 
    cin >> type_info;
    while (!((type_info < 4) && (type_info > 0)))
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
    int number_of_symulation_=0;
    int condition;
    int seed_chart = 1209371;
    int tab1[10] = { 0 };
    int tab[10] = { 0 };
    int tab2[100] = { 0 };
    double temp_chart;
    bool chart;
    vector<int> seeds;
    int seed = 5;
    bool condition1 = true;
    int counter = 0;
    int counter_seed = 0;
    int number_of_simulations;
    cerr << "Enter the number of simulations to generate the right amount of seeds" << endl;
    cin >> number_of_simulations;
    double time_initial_phase;
    double time_for_generate_package;
    bool condition_initial_phase = true;
    int end_simulation_condition;
    double condition_of_finish_time;
    int condition_of_finish_packages;
    bool first = true;
    for (int i = 0; i < number_of_simulations; i++)
    {
      WirelessNetwork* wireless_network = new WirelessNetwork(type_info, type_print);
      if (first == true) {
        cerr << "Do you want to save data to charts (1-yes, 0-no)" << endl;

        cin >> chart;
        if (chart == 1) {

          for (int i = 0; i < 20000000; i++)
          {
            temp_chart = wireless_network->UniformGenerator2(seed_chart);// *10 i rzutowanie na int
            tab1[int(temp_chart * 10)]++;
          }
          for (int i = 0; i < 10; i++)
          {
            ofstream save("uniform0-1.txt", ios_base::app);
            save << tab1[i] << endl;
            save.close();
          }
          for (int i = 0; i < 20000000; i++)
          {
            temp_chart = wireless_network->UniformGeneratorRange2(10, 1, seed_chart);
            tab[int(temp_chart - 1)]++;

          }
          for (int i = 0; i < 10; i++)
          {
            ofstream save("uniform1-10.txt", ios_base::app);
            save << tab[i] << endl;
            save.close();
          }
          for (int i = 0; i < 200000; i++)
          {
            temp_chart = wireless_network->ExponentialGenerator2(1, seed_chart);//wynik razy 10 rozmiar talblicy do 100
            tab2[int(temp_chart * 10)]++;
          }
          for (int i = 0; i < 100; i++)
          {
            ofstream save("exp.txt", ios_base::app);
            save << i << " " << tab2[i] << endl;
            save.close();
          }
        }

        condition = (number_of_simulations * 5 * 2) + number_of_simulations;
        // cerr << condition << endl;
        while (condition1)
        {
          wireless_network->UniformGenerator(seed, -1, false);
          //cerr << seed << endl;
          counter++;
          if (counter >= 100000)
          {
            ofstream save("SEEDS.txt", ios_base::app);
            save << seed << endl;
            save.close();

            seeds.push_back(seed);
            counter_seed++;
            counter = 0;
            if (counter_seed >= condition)
            {
              condition1 = false;
            }
          }

        }
      }
      for (int i = 0; i < wireless_network->GetAmountNumberOfStations(); i++)
      {
        wireless_network->AddSeedForTimeTransmision(seeds[0]);
        seeds.erase(seeds.begin());
        wireless_network->AddSeedForPacketGeneration(seeds[0]);
        seeds.erase(seeds.begin());
      }
      wireless_network->AddSeedForChannel(seeds[0]);
      seeds.erase(seeds.begin());

      TimeEventList* time_event_list = new TimeEventList();
      TimeEvent* time_event;
      if (type_info < 3)
      {
        if (type_print == 1)
        {
          cerr << "System initialization: " << endl;
          cerr << "Creating time events for generating the package and a new time slot" << endl;
        }
        else
        {
          ofstream save("logs.txt", ios_base::app);
          save << "System initialization: " << endl;
          save << "Creating time events for generating the package and a new time slot" << endl;
          save.close();
        }
      }
     // wireless_network->PrintSeedsForGenerationPackage();

      for (int i = 0; i < wireless_network->GetAmountNumberOfStations(); i++)
      {
        seed = wireless_network->GetSeedForGenerationPackage(i);
        time_for_generate_package = wireless_network->ExponentialGenerator(0.3, seed, i);
        time_event = new GeneratePackage(wireless_network, time_for_generate_package, i, time_event_list);
        time_event_list->AddTimeEvent(time_event);

      }
      time_event = new CheckingTheSlotBusy(wireless_network, 0, time_event_list); // pierwsza szczelina czasowa jest generowana z czasem zero
      time_event_list->AddTimeEvent(time_event);
      if (first == true)
      {
        cerr << "Enter the time of the initial phase after which the statistics should be reset" << endl;
        cin >> time_initial_phase;


        cerr << "Select the end simulation condition" << endl;
        cerr << "1. Time " << endl;
        cerr << "2. Number of correctly delivered packages" << endl;
        cerr << "Choose a number: "; cin >> end_simulation_condition;
        while (!((end_simulation_condition < 3) && (end_simulation_condition > 0)))
        {
          cerr << "Wrong value selected!! Choose a number(1-2): "; cin >> end_simulation_condition;
        }
        if (end_simulation_condition == 1)
        {
          cerr << "Enter the end time of the simulation: "; cin >> condition_of_finish_time;
          condition_of_finish_packages = INT_MAX;
        }
        else
        {
          cerr << "Enter the number of packets sent correctly when the simulation is to end : "; cin >> condition_of_finish_packages;
          condition_of_finish_time = INT_MAX;
        }
      }
      while (wireless_network->GetSystemTime() < condition_of_finish_time && wireless_network->GetPackageCondition() < condition_of_finish_packages)
      {
        if (time_initial_phase < wireless_network->GetSystemTime() && condition_initial_phase == true)
        {

          condition_initial_phase = false;
          wireless_network->ResetStatistic();
        }
        time_event = time_event_list->GetFirst();
        wireless_network->SetSystemTime(time_event->GetTime());
        time_event->Execute();
        delete time_event;
        if (type_info < 3)
        {
          if (type_print == 1)
          {
            cerr << "System time: " << wireless_network->GetSystemTime() << endl;
            cerr << "List of scheduled time events: " << endl;
            cerr << "---------------------------------------------------" << endl;
          }
          else
          {
            ofstream save("logs.txt", ios_base::app);
            save << "System time: " << wireless_network->GetSystemTime() << endl;
            save << "List of scheduled time events: " << endl;
            save << "---------------------------------------------------" << endl;
            save.close();
          }
        }

        if (type_info < 3)
        {
          if (type_print == 1)
          {
            cerr << "---------------------------------------------------" << endl;
            time_event_list->PrintTimeEventList();
            cerr << "---------------------------------------------------" << endl;
          }
          else
          {
            ofstream save("logs.txt", ios_base::app);
            save << "---------------------------------------------------" << endl;
            time_event_list->PrintTimeEventList();
            save << "---------------------------------------------------" << endl;
            save.close();
          }
        }
        if (step == 1)
        {
          cin.get();
        }
      }
      first = false;
      number_of_symulation_++;
      cerr << "Simulation: "<<number_of_symulation_ << endl;
      wireless_network->PrintStatistic();
      delete wireless_network;
      delete time_event_list;
      cerr << endl;
      // }
    }
    return 0;
}


