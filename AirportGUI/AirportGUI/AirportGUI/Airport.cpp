/*
* Airport.cpp
*
*  Created on: Mar 24, 2017
*      Author: lihan
*/
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <string>
#include <ctime>
#include <vector>
#include <time.h>
#include "Airplane.h"
#include "Airport.h"
#include "Event.h"
using namespace std;

const int NumberAirports = 100;

Airport::Airport(){

}


Airport::Airport(std::string name, double runwayTimeToLand, double requiredTimeOnGround, double takeoffTime, double flightTime, int airport_index, int num_of_runway) {
	m_airportName = name;
	m_inTheAir = 0;
	m_onTheGround = 0;
	m_passengerArrive = 0;
	m_passengerDepart = 0;
	m_circlingTime = 0.0;
	m_freeToLand = true;
	m_runwayTimeToLand = runwayTimeToLand;
	m_requiredTimeOnGround = requiredTimeOnGround;
	m_takeoffTime = takeoffTime;
	m_flightTime = flightTime;
	m_airport_index = airport_index;
	m_numberOfPlanes = 0;
	m_freeToLand = true;
	free_runway = num_of_runway;
	num_runway = num_of_runway;
}

std::string Airport::getName() {
	return m_airportName;
}

int Airport::getIndex() { return m_airport_index; }

double Airport::getCirclingTime() { return m_circlingTime; }

void Airport::setCirclingTime(double Increment) {
	m_circlingTime = m_circlingTime + Increment;
}


void Airport::setFlightTime(double flighttime) {
	m_flightTime = flighttime;
}

double Airport::getM_flightTime() {
	return m_flightTime;
}

int Airport::getArrivePassenger() { return m_passengerArrive; }

void Airport::setArrivePassenger(int number){
	m_passengerArrive = m_passengerArrive + number;
}

int Airport::getDepartPassenger() { return m_passengerDepart; }

void Airport::setDepartPassenger(int number){
	m_passengerDepart = m_passengerDepart + number;
}

int Airport::getAirplaneNumber() { return m_numberOfPlanes; }


// Randomly set another airport as its next destination
int Airport::setDestinationIndex() {

	int randomNumber = (int)(rand() % NumberAirports);
	while (randomNumber == m_airport_index) {
		randomNumber = (int)(rand() % NumberAirports);
	}
	return randomNumber;
}


bool Airport::getFree() {
	return m_freeToLand;
}


void Airport::freeRunway(){
	free_runway++;
}

void Airport::occupyRunway(){
	free_runway--;
}

// Check whether there is still a free runway
bool Airport::checkFree(){
	return free_runway > 0;
}


