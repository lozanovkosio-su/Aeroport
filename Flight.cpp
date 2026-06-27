//
// Created by Kosio Lozanov on 24.06.26.
//

#include "Flight.h"
#include "User.h"
#include "Engine.h"
#include "Passenger.h"


const std::string & Flight::getDest() const {
    return destination;
}

const StatusFlight & Flight::getStatus() const {
    return status;
}

const std::string & Flight::getCode() const {
    return uniqueCode;
}

const double Flight::getPrice() const {
    return baseTicketPrice;
}

std::vector<std::shared_ptr<Ticket>> & Flight::getTickets(){
    return soldTickets;
}

const std::unique_ptr<Plane> & Flight::getPlane() const {
    return plane;
}

void Flight::setStatu(const StatusFlight &status_) {
    status = status_;
}
void Flight::onWeatherChanged(Weather newWeather, bool airportHasIls)  {
    if (newWeather == Weather::STORM && status == StatusFlight::Scheduled) {
        if (!airportHasIls) {
            status = StatusFlight::Cancelled;
        }
    }
    for (std::shared_ptr<Ticket>& ptr : soldTickets) {
        for (std::shared_ptr<User>& userC : Engine::users) {
            for (const std::shared_ptr<Ticket>& ticketC : userC->getTickets()) {
                if (ticketC->getName() == ptr->getName()) {
                    std::shared_ptr<Passenger> psg = std::static_pointer_cast<Passenger>(userC);
                    psg->setBalance(ticketC->getAmaount());
                }
            }
        }
    }
}

#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Flight& f) {
    os << std::quoted(f.uniqueCode) << ' '
       << std::quoted(f.destination) << ' '
       << f.baseTicketPrice << ' '
       << static_cast<int>(f.status);
    return os;
}

std::istream& operator>>(std::istream& is, Flight& f) {
    std::string tCode, tDest;
    double tPrice;
    int tStatus;

    if (is >> std::quoted(tCode) >> std::quoted(tDest) >> tPrice >> tStatus) {
        f.uniqueCode = tCode;
        f.destination = tDest;
        f.baseTicketPrice = tPrice;
        f.status = static_cast<StatusFlight>(tStatus);
    }
    return is;
}

Flight::Flight(const Flight& other)
    : IWeatherObserver(other), // Копираме базовия клас
      uniqueCode(other.uniqueCode),
      listCodes(other.listCodes),
      destination(other.destination),
      baseTicketPrice(other.baseTicketPrice),
      status(other.status),
      soldTickets(other.soldTickets) // Виж важната бележка по-долу!
{
    // Дълбоко копиране на самолета:
    if (other.plane != nullptr) {
        plane = other.plane->clone();
    }
}