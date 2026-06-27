//
// Created by Kosio Lozanov on 25.06.26.
//

#ifndef UNTITLED2_LASTMINUTE_H
#define UNTITLED2_LASTMINUTE_H
#include <iostream>
#include <string>
#include "User.h"
#include "Ticket.h"


class LastMinute : public Ticket {
public:
    LastMinute(const std::string& name_, const std::string& flightID_, const TicketType& type_,
        unsigned paidAmaount_);
};


#endif //UNTITLED2_LASTMINUTE_H