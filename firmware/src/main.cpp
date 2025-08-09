#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "include/config.h"
#include "lib/power/PowerBus.h"

float mock_supercap_v = 2.1f;
float mock_harvest_mW = 2.5f;
float mock_load_uW = 80.0f;

static PowerBus bus;

static bool burst_allowed() {
    return bus.supercap_V >= SUPERCAP_OK_V;
}

static void tick_life_support() {
    // Simulate supercap voltage drift: harvest charges, load discharges
    // Very simplified; real firmware would read ADCs and use coulomb counting
    float net_mW = bus.harvest_mW - (bus.load_uW / 1000.0f);
    // 1 tick ~ 1 second, super basic voltage step model
    bus.supercap_V += net_mW * 0.0001f;
    if (bus.supercap_V > SUPERCAP_MAX_V) bus.supercap_V = SUPERCAP_MAX_V;
    if (bus.supercap_V < 0.0f) bus.supercap_V = 0.0f;
}

static void do_burst_job() {
    // Example: 5V @ 1A for ~0.5s (simulated)
    printf("[BURST] Firing actuator pulse...\n");
    // Drop supercap voltage to reflect energy usage
    bus.supercap_V -= 0.05f;
    if (bus.supercap_V < SUPERCAP_MIN_V) bus.supercap_V = SUPERCAP_MIN_V;
}

int main() {
    printf("E-Core sentinel starting...\n");
    unsigned t = 0;
    while (t < 120) { // simulate 2 minutes
        // Sense
        bus.harvest_mW = mock_harvest_mW;
        bus.load_uW = mock_load_uW;

        // Protect: never dip below minimum
        if (bus.supercap_V < SUPERCAP_MIN_V) {
            // reduce background load or turn off noncritical sensors
            mock_load_uW = 50.0f;
        }

        // Burst if allowed every 30s
        if (t % 30 == 0 && burst_allowed()) {
            do_burst_job();
        }

        tick_life_support();

        if (t % 10 == 0) {
            printf("[t=%us] Vcap=%.3fV, harvest=%.2fmW, load=%.2fuW\n",
                   t, bus.supercap_V, bus.harvest_mW, bus.load_uW);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++t;
    }
    printf("E-Core simulation complete.\n");
    return 0;
}
