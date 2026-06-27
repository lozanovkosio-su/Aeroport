//
// Created by Kosio Lozanov on 26.06.26.
//

#ifndef UNTITLED2_IWEATHEROBSERVER_H
#define UNTITLED2_IWEATHEROBSERVER_H

enum class Weather { SUNNY, STORM };

class IWeatherObserver {
public:

    virtual ~IWeatherObserver() = default;
    virtual void onWeatherChanged(Weather newWeather, bool airportHasIls) = 0;
};


#endif //UNTITLED2_IWEATHEROBSERVER_H