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