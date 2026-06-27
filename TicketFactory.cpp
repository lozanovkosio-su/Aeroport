//
// Created by Kosio Lozanov on 26.06.26.
//

#include "TicketFactory.h"
#include <iostream>
#include <string>
#include <memory>
#include "StandartTicket.h"
#include "LastMinute.h"
#include "VIPTicket.h"


std::shared_ptr<Ticket> TicketFactory::createT(const std::string &type,
    const std::string& name,
    const std::string& flightId, unsigned paidAmaount){
    if (type == "Standard") {
        return std::make_shared<StandartTicket>(name, flightId,TicketType::Standard,
            paidAmaount);
    }
    else if (type == "LastMinute") {
        return std::make_shared<LastMinute>(name, flightId,TicketType::LastMinute,
            paidAmaount);
    }else if (type == "VIP") {
        return std::make_shared<VIPTicket>(name, flightId,TicketType::VIP,
            paidAmaount);
    }else {
        std::cout << "Such type ticket doesnt exist!" << std::endl;
        return nullptr;
    }
}