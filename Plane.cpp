//
// Created by Kosio Lozanov on 24.06.26.
//

#include "Plane.h"
#include <vector>
#include <optional>
#include <memory>

#include "Engine.h"
#include "PassengerPlane.h"
#include "Ticket.h"
#include "Flight.h"



const unsigned Plane::getCapacity() const {
    return capacity;
}

const std::string & Plane::getId() const {
    return id;
}
