#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  //NP 12Apr2021
  int arrivalTime = currentTime;
  if (travelDir == EAST_DIRECTION)
  {
    arrivalTime = getPositiveNormal(eastArrivalMean, eastArrivalStdDev)
                  + currentTime;
    EventClass arrivalEvent(arrivalTime, EVENT_ARRIVE_EAST);
    eventList.insertValue(arrivalEvent);
    cout << "Time: " << currentTime << " ";
    cout << "Scheduled " << arrivalEvent << endl;
  }
  if (travelDir == WEST_DIRECTION)
  {
    arrivalTime = getPositiveNormal(westArrivalMean, westArrivalStdDev)
                  + currentTime;
    EventClass arrivalEvent(arrivalTime, EVENT_ARRIVE_WEST);
    eventList.insertValue(arrivalEvent);
    cout << "Time: " << currentTime << " ";
    cout << "Scheduled " << arrivalEvent << endl;
  }
  if (travelDir == NORTH_DIRECTION)
  {
    arrivalTime = getPositiveNormal(northArrivalMean, northArrivalStdDev)
                  + currentTime;
    EventClass arrivalEvent(arrivalTime, EVENT_ARRIVE_NORTH);
    eventList.insertValue(arrivalEvent);
    cout << "Time: " << currentTime << " ";
    cout << "Scheduled " << arrivalEvent << endl;
  }
  if (travelDir == SOUTH_DIRECTION)
  {
    arrivalTime = getPositiveNormal(southArrivalMean, southArrivalStdDev)
                  + currentTime;
    EventClass arrivalEvent(arrivalTime, EVENT_ARRIVE_SOUTH);
    eventList.insertValue(arrivalEvent);
    cout << "Time: " << currentTime << " ";
    cout << "Scheduled " << arrivalEvent << endl;
  }
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
  //NP 12Apr2021
  cout << "Time: " << currentTime << " ";
  if (currentLight == LIGHT_GREEN_EW)
  {
    int lightChangeTime = currentTime + eastWestGreenTime;
    EventClass nextLight(lightChangeTime, EVENT_CHANGE_YELLOW_EW);
    eventList.insertValue(nextLight);
    currentLight = LIGHT_YELLOW_EW;
    cout << "Scheduled " << nextLight << endl;
  }
  else if (currentLight == LIGHT_YELLOW_EW)
  {
    int lightChangeTime = currentTime + eastWestYellowTime;
    EventClass nextLight(lightChangeTime, EVENT_CHANGE_GREEN_NS);
    eventList.insertValue(nextLight);
    cout << "Scheduled " << nextLight << endl;
    currentLight = LIGHT_GREEN_NS;
  }
  else if (currentLight == LIGHT_GREEN_NS)
  {
    int lightChangeTime = currentTime + northSouthGreenTime;
    EventClass nextLight(lightChangeTime, EVENT_CHANGE_YELLOW_NS);
    eventList.insertValue(nextLight);
    cout << "Scheduled " << nextLight << endl;
    currentLight = LIGHT_YELLOW_NS;
  }
  else if (currentLight == LIGHT_YELLOW_NS)
  {
    int lightChangeTime = currentTime + northSouthYellowTime;
    EventClass nextLight(lightChangeTime, EVENT_CHANGE_GREEN_EW);
    eventList.insertValue(nextLight);
    cout << "Scheduled " << nextLight << endl;
    currentLight = LIGHT_GREEN_EW;
  }
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  //NP 13Apr2021
  EventClass nextEvent;
  CarClass carAtLight;
  eventList.removeFront(nextEvent);
  currentTime = nextEvent.getTimeOccurs();
  int eventType = nextEvent.getType();
  int continueSim;
  if (currentTime > timeToStopSim)
  {
    int eastQueueLength = eastQueue.getNumElems();
    int westQueueLength = westQueue.getNumElems();
    maxEastQueueLength = max(eastQueueLength, maxEastQueueLength);
    maxWestQueueLength = max(westQueueLength, maxWestQueueLength);
    int northQueueLength = northQueue.getNumElems();
    int southQueueLength = southQueue.getNumElems();
    maxNorthQueueLength = max(northQueueLength, maxNorthQueueLength);
    maxSouthQueueLength = max(southQueueLength, maxSouthQueueLength);
    cout << endl << "Next event occurs AFTER the simulation end time (" 
         << nextEvent << ")!" << endl;
    continueSim = false;
  }
  else
  {
    cout << endl << "Handling " << nextEvent << endl;
    if (eventType == EVENT_ARRIVE_EAST)
    {
      CarClass incomingCar(EAST_DIRECTION, currentTime);
      eastQueue.enqueue(incomingCar);
      cout << "Time: " << currentTime << " ";
      cout << "Car #" << incomingCar.getId() << " arrives east-bound - ";
      cout << "queue length: " << eastQueue.getNumElems() << endl; 
      scheduleArrival(EAST_DIRECTION);
    }
    else if (eventType == EVENT_ARRIVE_WEST)
    {
      CarClass incomingCar(WEST_DIRECTION, currentTime);
      westQueue.enqueue(incomingCar);
      cout << "Time: " << currentTime << " ";
      cout << "Car #" << incomingCar.getId() << " arrives west-bound - ";
      cout << "queue length: " << westQueue.getNumElems() << endl; 
      scheduleArrival(WEST_DIRECTION);
    }
    else if (eventType == EVENT_ARRIVE_NORTH)
    {
      CarClass incomingCar(NORTH_DIRECTION, currentTime);
      northQueue.enqueue(incomingCar);
      cout << "Time: " << currentTime << " ";
      cout << "Car #" << incomingCar.getId() << " arrives north-bound - ";
      cout << "queue length: " << northQueue.getNumElems() << endl; 
      scheduleArrival(NORTH_DIRECTION);
    }
    else if (eventType == EVENT_ARRIVE_SOUTH)
    {
      CarClass incomingCar(SOUTH_DIRECTION, currentTime);
      southQueue.enqueue(incomingCar);
      cout << "Time: " << currentTime << " ";
      cout << "Car #" << incomingCar.getId() << " arrives south-bound - ";
      cout << "queue length: " << southQueue.getNumElems() << endl; 
      scheduleArrival(SOUTH_DIRECTION);
    }
    else if (eventType == EVENT_CHANGE_YELLOW_EW)
    {
      cout << "Advancing cars on east-west green" << endl;
      int eastQueueLength = eastQueue.getNumElems();
      int westQueueLength = westQueue.getNumElems();
      maxEastQueueLength = max(eastQueueLength, maxEastQueueLength);
      maxWestQueueLength = max(westQueueLength, maxWestQueueLength);
      currentLight = LIGHT_YELLOW_EW;
      int eastCarLightCount = 0;
      int westCarLightCount = 0;
      for (int i = 0; i < eastWestGreenTime; i++)
      {
        bool advanceEast = eastQueue.dequeue(carAtLight);
        if (advanceEast)
        {
          cout << "  Car #" << carAtLight.getId() << " advances east-bound" << endl;
          numTotalAdvancedEast++;
          eastCarLightCount++;
        }
        else
        {
          break;
        }
      }
      for (int i = 0; i < eastWestGreenTime; i++)
      {
        bool advanceWest = westQueue.dequeue(carAtLight);
        if (advanceWest)
        {
          cout << "  Car #" << carAtLight.getId() << " advances west-bound" << endl;
          numTotalAdvancedWest++;
          westCarLightCount++;
        }
        else
        {
          break;
        }
      }
      cout << "East-bound cars advanced on green: " << eastCarLightCount;
      cout << " Remaining queue: " << eastQueue.getNumElems() << endl;
      cout << "West-bound cars advanced on green: " << westCarLightCount;
      cout << " Remaining queue: " << westQueue.getNumElems() << endl;
      scheduleLightChange();    
    }
    else if (eventType == EVENT_CHANGE_GREEN_EW)
    {
      cout << "Advancing cars on north-south yellow" << endl;
      if (northQueue.getNumElems() == 0)
      {
        cout << "  No north-bound cars waiting to advance on yellow" << endl;
      }
      else
      {
        cout << "  Next north-bound car will NOT advance on yellow" << endl;
      } 
      if (southQueue.getNumElems() == 0)
      {
        cout << "  No south-bound cars waiting to advance on yellow" << endl;
      }
      else
      {
        cout << "  Next south-bound car will NOT advance on yellow" << endl;
      } 
      bool advanceOnYellowWest = true;
      bool advanceOnYellowEast = true;
      int carNorthCounter = 0;
      int carSouthCounter = 0;
      for (int i = 0; i < northSouthYellowTime; i++)
      {
        bool advanceNorth = getUniform(0,100) < percentCarsAdvanceOnYellow;;
        if (advanceNorth && northQueue.dequeue(carAtLight))
        {
          numTotalAdvancedNorth++;
          carNorthCounter++;
        }
        else
        {
          break;
        }
      }
      for (int i = 0; i < northSouthYellowTime; i++)
      {
        bool advanceSouth = getUniform(0,100) < percentCarsAdvanceOnYellow;;
        if (advanceSouth && southQueue.dequeue(carAtLight))
        {
          numTotalAdvancedSouth++;
          carNorthCounter++;
        }
        else
        {
          break;
        }
      }
      currentLight = LIGHT_GREEN_EW;
      cout << "North-bound cars advanced on yellow: " << carNorthCounter 
           << " Remaining queue: " << northQueue.getNumElems() << endl;
      cout << "South-bound cars advanced on yellow: " << carSouthCounter 
           << " Remaining queue: " << southQueue.getNumElems() << endl;
      scheduleLightChange();
    }
    else if (eventType == EVENT_CHANGE_YELLOW_NS)
    {
      cout << "Advancing cars on north-south green" << endl;
      int northQueueLength = northQueue.getNumElems();
      int southQueueLength = southQueue.getNumElems();
      int carNorthCounter = 0;
      int carSouthCounter = 0;
      maxNorthQueueLength = max(northQueueLength, maxNorthQueueLength);
      maxSouthQueueLength = max(southQueueLength, maxSouthQueueLength);
      currentLight = LIGHT_YELLOW_NS;
      for (int i = 0; i < northSouthGreenTime; i++)
      {
        bool advanceNorth = northQueue.dequeue(carAtLight);
        if (advanceNorth)
        {
          cout << "  Car #" << carAtLight.getId() << " advances north-bound" << endl;
          numTotalAdvancedNorth++;
          carNorthCounter++;
        }
        else
        {
          break;
        }
      }
      for (int i = 0; i < northSouthGreenTime; i++)
      {
        bool advanceSouth = southQueue.dequeue(carAtLight);
        if (advanceSouth)
        {
          cout << "  Car #" << carAtLight.getId() << " advances south-bound" << endl;
          numTotalAdvancedSouth++;
          carSouthCounter++;
        }
        else
        {
          break;
        }
      }
      cout << "North-bound cars advanced on green: " << carNorthCounter 
           << " Remaining queue: " << northQueue.getNumElems() << endl;
      cout << "South-bound cars advanced on green: " << carSouthCounter 
           << " Remaining queue: " << southQueue.getNumElems() << endl;
      scheduleLightChange();
    }
    else if (eventType == EVENT_CHANGE_GREEN_NS)
    {
      cout << "Advancing cars on east-west yellow" << endl;
      if (eastQueue.getNumElems() == 0)
      {
        cout << "  No east-bound cars waiting to advance on yellow" << endl;
      }
      else
      {
        cout << "  Next east-bound car will NOT advance on yellow" << endl;
      } 
      if (westQueue.getNumElems() == 0)
      {
        cout << "  No west-bound cars waiting to advance on yellow" << endl;
      }
      else
      {
        cout << "  Next west-bound car will NOT advance on yellow" << endl;
      } 
      bool advanceOnYellowNorth = true;
      bool advanceOnYellowSouth = true;
      int carEastCounter = 0;
      int carWestCounter = 0;
      for (int i = 0; i < eastWestYellowTime; i++)
      {
        bool advanceWest = getUniform(0,100) < percentCarsAdvanceOnYellow;
        if (advanceWest && westQueue.dequeue(carAtLight))
        {
          numTotalAdvancedWest++;
          carWestCounter++;
        }
        else
        {
          break;
        }
      }
      for (int i = 0; i < eastWestYellowTime; i++)
      {
        bool advanceEast = getUniform(0,100) < percentCarsAdvanceOnYellow;
        if (advanceEast && eastQueue.dequeue(carAtLight))
        {
          numTotalAdvancedEast++;
          carEastCounter++;
        }
        else
        {
          break;
        }
      }
      cout << "East-bound cars advanced on yellow: " << carEastCounter 
           << " Remaining queue: " << eastQueue.getNumElems() << endl;
      cout << "West-bound cars advanced on yellow: " << carWestCounter 
           << " Remaining queue: " << westQueue.getNumElems() << endl;
      currentLight = LIGHT_GREEN_NS;
      scheduleLightChange();
    }
    continueSim = true;
  }
  return continueSim;
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
