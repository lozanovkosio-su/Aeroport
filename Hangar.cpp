//
// Created by Kosio Lozanov on 24.06.26.
//

#include "Hangar.h"
#include <algorithm>
#include <stdexcept>

std::vector<std::string> Hangar::listIds = {};

Hangar::Hangar(const std::string& id,
               unsigned capacity,
               double sum)
    : id(id),
      capacity(capacity),
      sum(sum)
{
    // check uniqueness
    if (std::find(listIds.begin(), listIds.end(), id) != listIds.end()) {
        throw std::runtime_error("Hangar ID already exists: " + id);
    }

    listIds.push_back(id);
}
#include <iomanip> // Задължително за std::quoted

std::ostream& operator<<(std::ostream& os, const Hangar& h) {
    os << std::quoted(h.id) << ' ' << h.capacity << ' ' << h.sum;
    return os;
}

std::istream& operator>>(std::istream& is, Hangar& h) {
    std::string tempId;
    unsigned tempCap;
    double tempSum;

    if (is >> std::quoted(tempId) >> tempCap >> tempSum) {
        h.id = tempId;
        h.capacity = tempCap;
        h.sum = tempSum;

        // ВАЖНО: Регистрираме ID-то в статичния вектор, ако го няма
        if (std::find(Hangar::listIds.begin(), Hangar::listIds.end(), h.id) == Hangar::listIds.end()) {
            Hangar::listIds.push_back(h.id);
        }
    }
    return is;
}