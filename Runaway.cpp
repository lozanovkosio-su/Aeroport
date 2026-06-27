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

std::ostream& operator<<(std::ostream& os, const Runaway& r) {
    os << r.id << ' '
       << r.lenght << ' '
       << static_cast<int>(r.status) << ' '
       << r.optionals.size();

    for (optionalExtentions opt : r.optionals) {
        os << ' ' << static_cast<int>(opt);
    }
    return os;
}

std::istream& operator>>(std::istream& is, Runaway& r) {
    int tId, tStatus;
    unsigned tLen;
    size_t optSize;

    if (is >> tId >> tLen >> tStatus >> optSize) {
        r.id = tId;
        r.lenght = tLen;
        r.status = static_cast<Status>(tStatus);

        r.optionals.clear();
        for (size_t i = 0; i < optSize; ++i) {
            int optVal;
            is >> optVal;
            r.optionals.push_back(static_cast<optionalExtentions>(optVal));
        }
        r.plane = std::nullopt; // Референции към самолети не се зареждат от текст директно
    }
    return is;
}
