#ifndef UNTITLED2_TICKET_H
#define UNTITLED2_TICKET_H
#include <iostream>
#include <string>
#include <memory>


enum class TicketType {
    Standard,
    LastMinute,
    VIP
};

class Ticket {
protected:
    std::string name;
    std::string flightId;
    TicketType ticketType;
    unsigned paidAmaount;
    unsigned luggageWeight = 0;
    //vip -> 20 luggage
    //cargo

public:
    static std::unique_ptr<Ticket> createT(const std::string& type);//1
    Ticket(const std::string& name_, const std::string& flightID_, const TicketType& type_,
        unsigned paidAmaount_);
    const std::string& getFlightId() const;
    const unsigned getAmaount() const;
    void setAmaount(double amaount);
    void setLuggage(unsigned weight);
    const std::string& getName() const;

};


#endif //UNTITLED2_TICKET_H