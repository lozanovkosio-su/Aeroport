//
// Created by Kosio Lozanov on 25.06.26.
//

#ifndef UNTITLED2_VIPTICKET_H
#define UNTITLED2_VIPTICKET_H
#include <iostream>
#include <string>
#include "Ticket.h"


class VIPTicket : public Ticket{
public:
    VIPTicket(const std::string& name_, const std::string& flightID_, const TicketType& type_,
            unsigned paidAmaount_);
};


#endif //UNTITLED2_VIPTICKET_H