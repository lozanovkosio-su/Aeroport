//
// Created by Kosio Lozanov on 27.06.26.
//

#include "Dispatcher.h"
#include "Admin.h"


void Dispatcher::listAirspace() const {
    for (std::shared_ptr<Flight>& ptr : Engine::flights) {
        if (ptr->getStatus() == StatusFlight::Scheduled) {
            std::cout << ptr->getCode() << " | " << std::endl;
        }
    }
}

void Dispatcher::assignRunaway(const std::string &flightId, unsigned runawayId) {
    //Runaway runawayWork{};
    for (Runaway& runawayC : Engine::runaways) {
        if (runawayC.getId() == runawayId) {
            //runawayWork = runawayC;
            for (const std::shared_ptr<Flight>& flightC : Engine::flights) {
                if (flightC->getCode() == flightId) {
                    if (flightC->getPlane()->requiredLenght() > runawayC.getLenght()) {
                        std::cout << "Invalid!";
                        return;
                    }
                    runawayC.getPlane()->get() = *(flightC->getPlane());
                    flightC->setStatu(StatusFlight::Boarding);
                    runawayC.setStatus(Status::Occupied);
                    lastCommand = std::make_tuple("assign",runawayC.getId(),flightC->getCode());
                }
            }
        }
    }
}

void Dispatcher::delayFlight(const std::string &flightId) {
    for (const std::shared_ptr<Flight>& flightC : Engine::flights) {
        if (flightC->getCode() == flightId) {
            flightC->setStatu(StatusFlight::Delayed);
        }
    }
}

void Dispatcher::freeRunaway(unsigned id) {
    for (Runaway& runawayC : Engine::runaways) {
        if (runawayC.getId() == id) {
            //runawayWork = runawayC;
            for (const std::shared_ptr<Flight>& flightC : Engine::flights) {
                if (flightC->getCode() == runawayC.getPlane()->get().getId()) {
                    runawayC.getPlane() = std::nullopt;
                    flightC->setStatu(StatusFlight::Departed);
                    flightC->getPlane()->decreaseHealth();
                    double sum = 0;
                    for (std::shared_ptr<Ticket>& tick:flightC->getTickets()) {
                        sum += tick->getAmaount();
                    }
                    sum -= flightC->getPlane()->getTax();
                    Admin::getInstance().setBalance(flightC->getPlane()->getTax());
                    for (AvioCompany& comp : Engine::airlines) {
                        for (std::shared_ptr<Flight>& ptr : Engine::flights) {
                            if (comp.chechFlight(ptr)) {
                                comp.setBalance(sum);
                            }
                        }
                    }
                    lastCommand = std::make_tuple("free",runawayC.getId(),flightC->getCode());
                }
            }
        }
    }
}

void Dispatcher::undo() {
    int runawayId = std::get<1>(lastCommand);
    std::string flightId = std::get<2>(lastCommand);
    if (std::get<0>(lastCommand) == "free") {
        assignRunaway(flightId,runawayId);
        //
    }
}
