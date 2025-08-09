#pragma once
#include <cstdint>

class Harvester {
public:
    // Return available harvested power in milliwatts (mW) for this tick
    virtual float harvest_mW() = 0;
    virtual ~Harvester() = default;
};
