#pragma once

// Energy thresholds (tune to your hardware)
static constexpr float SUPERCAP_OK_V = 2.2f;     // burst allowed above
static constexpr float SUPERCAP_MIN_V = 1.9f;    // protect below
static constexpr float SUPERCAP_MAX_V = 2.5f;    // derated max

// Scheduling
static constexpr unsigned TELEMETRY_PERIOD_S = 30;
static constexpr unsigned SENSE_PERIOD_S = 5;

// Mocked values for native build (sim hooks)
extern float mock_supercap_v;
extern float mock_harvest_mW;
extern float mock_load_uW;
