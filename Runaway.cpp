//
// Created by Kosio Lozanov on 24.06.26.
//

#include "Runaway.h"

Runaway::Runaway(int id_,unsigned length,
                 Status status,
                 const std::optional<std::reference_wrapper<Plane>>& plane,
                 const std::vector<optionalExtentions>& optionals)
    :
      lenght(length),
      status(status),
      plane(plane),
      optionals(optionals),id(id_)
{
    for (int idC : ids) {
        if (idC == id) {
            throw std::invalid_argument("Runaway with this id exist");
        }
    }
}

int Runaway::getId() const {
    return id;
}

void Runaway::setStatus(const Status &newS) {
    status = newS;
}

std::optional<std::reference_wrapper<Plane>> & Runaway::getPlane() {
    return plane;
}

bool Runaway::checkIfItHasILS(const Runaway &r1) const{
    for (optionalExtentions opt: optionals) {
        if (opt == optionalExtentions::ils) {
            return true;
        }
    }
    return false;
}

unsigned Runaway::getLenght() const {
    return lenght;
}
