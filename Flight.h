#ifndef UNTITLED2_FLIGHT_H
#define UNTITLED2_FLIGHT_H
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <memory>
#include "Plane.h"
#include "Ticket.h"
#include "IWeatherObserver.h"

enum class StatusFlight {
    Scheduled,
    Boarding,
    Delayed,
    Departed,
    Cancelled
};
//kogas mogat bileti

class Flight : public IWeatherObserver {
    std::string uniqueCode;
    std::vector<std::string> listCodes;
    std::unique_ptr<Plane> plane;
    std::string destination;
    double baseTicketPrice;
    std::vector<std::shared_ptr<Ticket>> soldTickets;
    StatusFlight status;

public:
    const std::string& getDestination() const;
    const std::string& getDest() const;
    const StatusFlight& getStatus() const;
    const std::string& getCode() const;
    const double getPrice() const;
    std::vector<std::shared_ptr<Ticket>>& getTickets();
    const std::unique_ptr<Plane>& getPlane() const;
    void setStatu(const StatusFlight& status_);
    void onWeatherChanged(Weather newWeather, bool airportHasIls) override;
     ~Flight() override = default;
};


#endif //UNTITLED2_FLIGHT_H