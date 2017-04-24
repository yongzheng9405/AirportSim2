/*
* Airport.h
*
*  Created on: Mar 24, 2017
*      Author: lihan
*/

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include <iostream>
#include <stdlib.h>
#include <queue>
#include <string>
#include <ctime>
#include <time.h>
#include <functional>
#include <vector>
#include "Airplane.h"
#include "Event.h"

class Event;
class Airport {

	int m_inTheAir;
	int m_onTheGround;
	int m_airport_index;
	int m_passengerArrive;
	int m_passengerDepart;
	double m_circlingTime;


	bool m_freeToLand;
	int free_runway;
	int num_runway;

	std::string m_airportName;


public:
	int m_numberOfPlanes;
	double m_flightTime;
	double m_runwayTimeToLand;
	double m_requiredTimeOnGround;
	double m_takeoffTime;
	std::priority_queue<Event*, std::vector<Event*>, CompareTime> ArrivingQueue;
	std::priority_queue<Event*, std::vector<Event*>, CompareTime> TakingoffQueue;
	std::priority_queue<Event*, std::vector<Event*>, CompareTime> EmergencyQueue;


	Airport();


	Airport(std::string name, double runwayTimeToLand, double requiredTimeOnGround, double takeoffTime, double flightTime, int airport_index, int num_of_runway);

	std::string getName();

	int getIndex();

	double getCirclingTime();

	void setCirclingTime(double Increment);

	void setFlightTime(double flighttime);

	double getM_flightTime();

	int getArrivePassenger();

	void setArrivePassenger(int number);

	int getDepartPassenger();

	void setDepartPassenger(int number);

	int getAirplaneNumber();

	int setDestinationIndex();

	bool getFree();

	void freeRunway();

	void occupyRunway();

	bool checkFree();

};




#endif /* AIRPORT_H_ */
