//
// Created by Kosio Lozanov on 26.06.26.
//

#ifndef UNTITLED2_TICKETFACTORY_H
#define UNTITLED2_TICKETFACTORY_H
#include <iostream>
#include <string>
#include "Ticket.h"
#include <memory>


class TicketFactory {
public:
    static std::shared_ptr<Ticket> createT(const std::string& type,
    const std::string& name,
const std::string& flightId, unsigned paidAmaount);
};



#endif //UNTITLED2_TICKETFACTORY_H
