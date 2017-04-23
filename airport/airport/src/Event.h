/*
 * Event.h
 *
 *  Created on: Mar 24, 2017
 *      Author: lihan
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <stdlib.h>
#include <queue>
#include <string>
#include <ctime>
#include <time.h>
#include <vector>
#include "Airplane.h"
#include "Airport.h"

class Airport;
class Airplane;
class Event {

	 double m_time;
	 int m_eventId;
	 int m_eventType;

	 Airplane* m_Airplane;
	 Airport* m_handler;
     Airport* m_destination;
     int m_plane_index;
     int m_source_index;
     int m_target_index;
     double m_arrivalTime;


public:
     static int m_nextId;
     static int PLANE_ARRIVES;
     static int PLANE_LANDED;
     static int PLANE_TAKEOFF;
     static int PLANE_DEPARTS;


     Event();

     Event(double delay, Airport* handler, int eventType, Airport* destination);


     int getId();

     double getTime();

     void setTime(double time);

     Airport* getHandler();

     int getType();

     void setHandler(Airport* handler);

     void setPlaneInformation(Airplane* Airplane1);

     Airplane* getPlaneInformation();

     void setPlaneDestination(Airport* airport);

     Airport* getPlaneDestination();



};


// Compare the timestamp of two events. Arrange them according to their timestamp in the priority queue
struct CompareTime {
    bool operator()(Event *p1, Event *p2) {
        // return "true" if "p1" is ordered before "p2", for example:
    	if (p1->getTime() > p2->getTime()) {
    		return true;
    	}
    	else if (p1->getTime() == p2->getTime()){
    		return p1->getId() > p2->getId();
    	}
    	else
    		return false;
    }
};




#endif /* EVENT_H_ */
