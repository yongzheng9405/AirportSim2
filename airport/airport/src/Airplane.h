/*
 * Airplane.h
 *
 *  Created on: Mar 23, 2017
 *      Author: lihan
 */

#ifndef AIRPLANE_H_
#define AIRPLANE_H_

#include <iostream>
#include <stdlib.h>
#include <queue>
#include <string>


class Airplane {

     std::string m_name;
     int m_numberPassengers;
     int m_plane_index;
     int m_source_index;
     int m_target_index;
     double m_arrivalTime;


public:
     double m_speed;    // the speed is about 15.0 miles per minute
     int m_maxPassengers;

     Airplane(std::string name, int plane_index, int source_index, int target_index, double arrivaltime, double speed, int max_passenger);

     std::string getName();

    // generate a random number between 300 and 700 each time when a plane departs
     void generatePassengerNumber();

     double getSpeed();

     int getPassengerNumber();

     int getTarget();

    // get the arrival time for the plane for future use of circling time calculation
     double getArrivalTime();

     void setArrivalTime(double arrivaltime);
};



#endif /* AIRPLANE_H_ */
