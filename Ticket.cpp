//
// Created by Kosio Lozanov on 24.06.26.
//

#include "Ticket.h"

Ticket::Ticket(const std::string &name_, const std::string &flightID_, const TicketType &type_, unsigned paidAmaount_):
name(name_), flightId(flightID_), ticketType(type_), paidAmaount(paidAmaount_)
{
}

const std::string & Ticket::getFlightId() const {
    return flightId;
}

const unsigned Ticket::getAmaount() const {
    return paidAmaount;
}

void Ticket::setAmaount(double amaount) {
    paidAmaount += amaount;
}

void Ticket::setLuggage(unsigned weight) {
    luggageWeight += weight;
}

const std::string & Ticket::getName() const {
    return name;
}
