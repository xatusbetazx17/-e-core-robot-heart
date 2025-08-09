#pragma once
#include <cstdint>

struct PowerBus {
    float supercap_V;     // measured cap voltage
    float harvest_mW;     // current harvested power
    float load_uW;        // current micro-watt life-support draw

    PowerBus(): supercap_V(2.1f), harvest_mW(0.0f), load_uW(80.0f) {}
};
