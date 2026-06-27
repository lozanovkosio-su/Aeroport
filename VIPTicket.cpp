//
// Created by Kosio Lozanov on 25.06.26.
//

#include "VIPTicket.h"
VIPTicket::VIPTicket(const std::string &name_, const std::string &flightID_, const TicketType &type_,
unsigned paidAmaount_) : Ticket(name_,flightID_,type_,paidAmaount_)
{
    luggageWeight = 20;
}