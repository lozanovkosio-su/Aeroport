//
// Created by Kosio Lozanov on 17.06.26.
//

#include "Admin.h"
#include <optional>
#include <functional>
#include "Engine.h"
#include "Flight.h"
#include "Plane.h"
#include "Runaway.h"




Admin::Admin(const std::string &name_, const std::string &password_, const Role &role_):
User(name_,password_,role_) {
}

Admin & Admin::getInstance() {
    static Admin a{"admin", "admin", Role::admin};
    return a;
}

Runaway Admin::buildRunaway(int id, unsigned length,
                            const std::optional<optionalExtentions> &firstOptional, const std::optional<optionalExtentions> &secondOptional,
                            const std::optional<optionalExtentions> &thirdOptional) {
    std::vector<optionalExtentions> extens;
    if (firstOptional!=std::nullopt) {
        extens.push_back(*firstOptional);
    }
    if (secondOptional!=std::nullopt) {
        extens.push_back(*secondOptional);
    }
    if (thirdOptional!=std::nullopt) {
        extens.push_back(*thirdOptional);
    }
    Runaway runawayC(id,length,Status::Free,std::nullopt,extens);
    Engine::runaways.push_back(runawayC);
    return runawayC;

}

Hangar Admin::buildHangar(const std::string id, unsigned capacity, double repairFee) {
    Hangar h{id,capacity,repairFee};
    Engine::hangars.push_back(h);
    return h;
}

void Admin::closeRunway(const std::string &runawayId) {
    int idRunaway = std::stoi(runawayId);
    for (Runaway& cRunaway : Engine::runaways) {
        if (cRunaway.getId() == idRunaway) {
            cRunaway.setStatus(Status::Maintenance);
            if (cRunaway.getPlane().has_value()) {
                for (std::shared_ptr<Flight>& ptr : Engine::flights) {
                    if (ptr->getPlane()->getId() == cRunaway.getPlane()->get().getId()) {
                        ptr->setStatu(StatusFlight::Scheduled);
                    }
                }
            }
        }
    }
}

void Admin::setTime(const std::string &type) {
    if (type == "SUNNY") return;
    bool flag = false;
    for (const Runaway object : Engine::runaways) {
        if (object.checkIfItHasILS(object)) {
            flag = true;
            break;
        }
    }
    for (const std::shared_ptr<Flight>& ptr : Engine::flights) {
        ptr->onWeatherChanged(Weather::STORM,flag);
    }
}

void Admin::registerAirline(const std::string &name, double capital) {
    if (capital < 0) {
        throw std::invalid_argument("Invalid Arg");
    }
    AvioCompany a(name,capital);
    Engine::airlines.emplace_back(a);
}

void Admin::setBalance(double newB) {
    balance += newB;
}
