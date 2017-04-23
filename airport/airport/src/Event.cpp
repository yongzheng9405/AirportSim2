/*
 * Event->cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: lihan
 */
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <string>
#include <ctime>
#include <time.h>
#include <vector>
#include "Airplane.h"
#include "Airport.h"
#include "Event.h"


using namespace std;


Event::Event(){
   m_eventId = m_nextId++;

}


Event::Event(double delay, Airport* handler, int eventType, Airport* destination) {
	 //Event();
	 m_time = delay;
     m_eventId = m_nextId++;
	 m_handler = handler;
	 m_eventType = eventType;
     m_destination = destination;             // set information about the destination airport

}


int Event::getId() {
    //return m_nextId;
    return m_eventId;
}

double Event::getTime() {
    return m_time;
}

void Event::setTime(double time) {
    m_time = time;
}

Airport* Event::getHandler() {
    return m_handler;
}

int Event::getType() { return m_eventType; }

void Event::setHandler(Airport* handler) {
    m_handler = handler;
}

void Event::setPlaneInformation(Airplane* Airplane1) {
             m_Airplane = Airplane1;
         }  // pass in the information of which Airplane* has the event

Airplane* Event::getPlaneInformation() {
             return m_Airplane;
         } // get the information of the plane having this event

void Event::setPlaneDestination(Airport* airport) {
             m_destination = airport;
         } // set destination for the event

Airport* Event::getPlaneDestination() {
             return m_destination;  // get the information of the destination airport
         }





int Event::m_nextId = 0;
int Event::PLANE_ARRIVES = 0;
int Event::PLANE_LANDED = 1;
int Event::PLANE_TAKEOFF = 2;
int Event::PLANE_DEPARTS = 3;


