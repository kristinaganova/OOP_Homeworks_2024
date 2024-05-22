#include "time.h"
#include <iostream>
#include <fstream>
#include <iomanip>

Time::Time() : secondsFromMidnight(0) {}

Time::Time(unsigned hours, unsigned mins, unsigned seconds) 
{
    setHours(hours);
    setMins(mins);
    setSeconds(seconds);
}

unsigned Time::getSecondsFromMidnight() const
{
    return this->secondsFromMidnight;
}

bool Time::validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier) 
{
    if (newValue >= lowerBound && newValue <= upperBound)
    {
        (secondsFromMidnight -= (oldValue * multiplier)) += (newValue * multiplier);
        return true;
    }
    else
        return false;
}

unsigned Time::getHours() const {
    return secondsFromMidnight / SECONDS_IN_HOURS;
}

unsigned Time::getMins() const 
{
    return (secondsFromMidnight / 60) % 60;
}

unsigned Time::getSeconds() const
{
    return secondsFromMidnight % 60;
}

bool Time::setHours(unsigned hours) 
{
    return validateAndSet(0, 23, hours, getHours(), SECONDS_IN_HOURS);
}

bool Time::setMins(unsigned mins) 
{
    return validateAndSet(0, 59, mins, getMins(), SECONDS_IN_MINUTE);
}

bool Time::setSeconds(unsigned seconds)
{
    return validateAndSet(0, 59, seconds, getSeconds(), 1);
}

void Time::tick() 
{
    ++secondsFromMidnight %= DAY_SECONDS;
}

void Time::serialize(std::ostream& os) const
{
    os << std::setw(2) << std::setfill('0') << getHours() << ":"
        << std::setw(2) << std::setfill('0') << getMins() << ":"
        << std::setw(2) << std::setfill('0') << getSeconds() << std::endl;
}
