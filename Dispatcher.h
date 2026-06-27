//
// Created by Kosio Lozanov on 27.06.26.
//

#ifndef UNTITLED2_DISPATCHER_H
#define UNTITLED2_DISPATCHER_H
#include <iostream>
#include <string>
#include <tuple>
#include "Hangar.h"
#include "Runaway.h"
#include "User.h"
#include "Flight.h"
#include "Engine.h"



class Dispatcher:public User {
    std::tuple<std::string,int,std::string> lastCommand;
public:
    void listAirspace() const;
    void assignRunaway(const std::string& flightId, unsigned runawayId);
    void delayFlight(const std::string& flightId);
    void freeRunaway(unsigned id);
    void undo();
};


#endif //UNTITLED2_DISPATCHER_H
