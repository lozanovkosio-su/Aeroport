//
// Created by Kosio Lozanov on 25.06.26.
//

#include "StandartTicket.h"

StandartTicket::StandartTicket(const std::string &name_, const std::string &flightID_, const TicketType &type_,
unsigned paidAmaount_) : Ticket(name_,flightID_,type_,paidAmaount_)
{
}
