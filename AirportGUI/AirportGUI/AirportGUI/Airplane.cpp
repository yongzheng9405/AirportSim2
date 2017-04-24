/*
* main.cpp
*
*  Created on: Mar 23, 2017
*      Author: lihan
*/
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <string>
#include "Airplane.h"
#include "Airport.h"
#include "Event.h"
using namespace std;




Airplane::Airplane(string name, int plane_index, int source_index, int target_index, double arrivaltime, double speed, int max_passenger) {

	m_name = name;
	m_source_index = source_index;
	m_target_index = target_index;
	m_plane_index = plane_index;
	m_arrivalTime = arrivaltime;
	m_speed = speed;
	m_maxPassengers = max_passenger;

	generatePassengerNumber();   // initialize random number of passenger on the plane

}

string Airplane::getName() {
	return m_name;
}

// generate a random number between 200 and maximum each time when a plane departs
void Airplane::generatePassengerNumber() {
	m_numberPassengers = 200 + (rand() % (int)(m_maxPassengers - 200 + 1));
}

double Airplane::getSpeed() {
	return m_speed;
}

int Airplane::getPassengerNumber() { return m_numberPassengers; }


int Airplane::getTarget() { return m_target_index; }

// get the arrival time for the plane for future use of circling time calculation
double Airplane::getArrivalTime() { return m_arrivalTime; }

void Airplane::setArrivalTime(double arrivaltime) {
	m_arrivalTime = arrivaltime;
}







