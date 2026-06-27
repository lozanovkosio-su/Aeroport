//
// Created by Kosio Lozanov on 25.06.26.
//

#ifndef UNTITLED2_STANDARTTICKET_H
#define UNTITLED2_STANDARTTICKET_H
#include <iostream>
#include <string>
#include "User.h"
#include "Ticket.h"



class StandartTicket : public Ticket{
public:
    StandartTicket(const std::string& name_, const std::string& flightID_, const TicketType& type_,
        unsigned paidAmaount_);
};


#endif //UNTITLED2_STANDARTTICKET_H