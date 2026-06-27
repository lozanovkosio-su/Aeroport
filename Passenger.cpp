//
// Created by Kosio Lozanov on 17.06.26.
//

#include "Passenger.h"
#include <memory>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Plane.h"
#include "Engine.h"
#include <print>
#include "TicketFactory.h"
#include "Ticket.h"




Passenger::Passenger(const std::string &name_,const std::string &password_, const Role &role_, double balance_) :
User(name_, password_, role_)
{
    if (balance_ < 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    balance = balance_;
}

void Passenger::addFunds(double amaount) {
    if (amaount < 0) {
        throw std::invalid_argument("Invalid Argument!");
    }
    balance += amaount;
}

void Passenger::listFlights(const std::string &destination) {
    int numFlights = 1;
    bool isFirstFound = false;
    for (std::shared_ptr<Flight>& ptr: Engine::flights) {
        if (ptr->getDest() == destination) {
            isFirstFound = true;
            if (numFlights == 1) {
                std::print("Available flights to{}:\n", destination);
            }
            if (ptr->getStatus() == StatusFlight::Scheduled) {
                std::print("{}. {} | Status:Scheduled | Base Price: {} EUR,\n",
                    numFlights, ptr->getCode(),ptr->getPrice());
                numFlights++;
            }else if (ptr->getStatus() == StatusFlight::Delayed) {
                std::print("{}. {} | Status:Delayed | Base Price: {} EUR,\n",
                    numFlights, ptr->getCode(),ptr->getPrice());
                numFlights++;
            }
        }
    }
    if (!isFirstFound) {
        std::print("No available flights to {}\n", destination);
    }
}

void Passenger::filterFlights(unsigned maxPrice) const {
    int numFlights = 1;
    bool isFirstFound = false;
    for (std::shared_ptr<Flight>& ptr: Engine::flights) {
        if (ptr->getPrice() < maxPrice) {
            isFirstFound = true;
            if (numFlights == 1) {
                std::print("Filtered flights (Price < {} EUR):\n", maxPrice);
            }
            if (ptr->getStatus() == StatusFlight::Scheduled) {
                std::print("{}. {} ({}) - {} EUR,\n",
                    numFlights, ptr->getCode(),ptr->getDest(),ptr->getPrice());
                numFlights++;
            }
        }
    }
    if (!isFirstFound) {
        std::print("No flights with price < {} were found!\n", maxPrice);
    }
}

void Passenger::bookTicket(const std::string &flightID, const std::string &ticketType) {
    TicketType type;
    double paid = 0;
    bool flag = false;
    if (ticketType == "Standard") {
        type = TicketType::Standard;
        paid = 1;
    }else if (ticketType == "LastMinute") {
        type = TicketType::LastMinute;
        paid = 0.5;
    }else if (ticketType == "VIP") {
        type = TicketType::VIP;
        paid = 2;
    }
    for (std::shared_ptr<Flight>& ptr: Engine::flights) {
        if (ptr->getCode() == flightID) {
            if (paid*(ptr->getPrice()) <= balance) {flag = true; break;
            }
            if (ptr->getTickets().size() < (ptr->getPlane())->getCapacity()) {
                std::shared_ptr<Ticket> pTicket =
                    TicketFactory::createT(ticketType,name, flightID,paid*(ptr->getPrice()));

                tickets.emplace_back(pTicket);
                ptr->getTickets().push_back(pTicket);
                balance -= paid*(ptr->getPrice());
                flag = true;
                break;
            }
        }
    }
    if (!flag) {
        std::cout << "No such Flight exist! or not enough balance";
    }else {
        std::print("Ticket for flight: {} is booked", flightID);
    }
}

void Passenger::cancelTicket(const std::string &flightId) {
    bool flag = false;
    bool isTicketInMyTickets = false;
    std::shared_ptr<Ticket> currTicket = nullptr;
    //for (std::unique_ptr<Flight>& ptr: Engine::flights) {
    for (int i = 0; i < Engine::flights.size(); i++){
        std::shared_ptr<Flight>& ptr = Engine::flights[i];
        if (ptr->getCode() == flightId) {
            for (std::shared_ptr<Ticket> tick : tickets) {
                if (tick->getFlightId() == flightId) {
                    isTicketInMyTickets = true;
                    currTicket = tick;
                    break;
                }
            }
            if (!isTicketInMyTickets) {break;}
            tickets.erase(tickets.begin() + i);
            balance += currTicket->getAmaount();
            flag = true;
        }
    }
    if (!flag) {
        std::cout << "No such Flight or you dont own this ticket!";
    }else {
        std::print("Ticket for flight: {} refunded", flightId);
    }
}

void Passenger::upgradeTicket(const std::string &flightId, const std::string &ticketType) {
    cancelTicket(flightId);
    bookTicket(flightId,ticketType);
}

void Passenger::addBagggage(const std::string &flightId, unsigned weight) {
    bool flag = false;
    for (std::shared_ptr<Ticket> tick : tickets) {
        if (tick->getFlightId() == flightId) {
            double toPay = 5*weight;
            if (balance >= toPay) {
                balance -= toPay;
                tick->setLuggage(weight);
                flag = true;
            }
        }
    }
    if (flag) {
        std::cout << "Successful adding of luggage";
    }else {
        std::cout << "You dont have enough money or you dont have such ticket!";
    }
}

void Passenger::myTickets() const {
    int num = 0;
    for (std::shared_ptr<Ticket> tick : tickets) {
        std::string type;
        for (std::shared_ptr<Flight>& ptr: Engine::flights) {
            //if (ptr->getStatus() == )
        }
    }
}

void Passenger::setBalance(unsigned amaount) {
    balance += amaount;
}
