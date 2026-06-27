#ifndef UNTITLED2_PASSENGER_H
#define UNTITLED2_PASSENGER_H
#include <iostream>
#include <string>
#include "User.h"
#include "Ticket.h"
#include <vector>
#include <memory>



class Passenger : public User {
    double balance;
public:
    Passenger(const std::string& name_, const std::string& password_, const Role& role_,
        double balance_=0.00);

    void addFunds(double amaount);
    void listFlights(const std::string& destination);
    void filterFlights(unsigned maxPrice) const;
    void bookTicket(const std::string& flightID, const std::string& ticketType);
    void cancelTicket(const std::string& flightId);
    void upgradeTicket(const std::string& flightId, const std::string& ticketType);
    void addBagggage(const std::string& flightId, unsigned weight);
    void myTickets() const;
    void setBalance(unsigned amaount);
};


#endif //UNTITLED2_PASSENGER_H