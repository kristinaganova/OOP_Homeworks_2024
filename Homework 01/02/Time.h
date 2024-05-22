#pragma once
#include <iostream>
//using the class implement in lecture
constexpr unsigned SECONDS_IN_HOURS = 3600;
constexpr unsigned SECONDS_IN_MINUTE = 60;
constexpr unsigned DAY_SECONDS = 24 * 3600;

class Time {
private:
    unsigned secondsFromMidnight;

    bool validateAndSet(unsigned lowerBound, unsigned upperBound, unsigned newValue, unsigned oldValue, unsigned multiplier);

public:
    Time();
    Time(unsigned hours, unsigned mins, unsigned seconds);
    unsigned getSecondsFromMidnight() const;
    unsigned getHours() const;
    unsigned getMins() const;
    unsigned getSeconds() const;
    bool setHours(unsigned hours);
    bool setMins(unsigned mins);
    bool setSeconds(unsigned seconds);
    void tick();
    void serialize(std::ostream& os) const;
};


