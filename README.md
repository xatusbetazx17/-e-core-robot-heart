# E‑Core: Robot Heart (Decades)

**Always‑awake, self‑harvesting power core** for small robots and wearables, inspired by real energy‑harvesting tech and the spirit of Mega Man’s “E‑Tank.”  
Goal: run **for decades** without human recharging by sipping power from **light, heat, motion, and a little RF**, storing it in **supercapacitors**, and falling back to a **long‑life primary cell** only when absolutely necessary.

> ⚠️ **Reality clause:** This is not perpetual motion and not a weapon design. The core is engineered to keep low‑power “life‑support” electronics running 24/7 and to accumulate energy for **short bursts** (actuators, radio). For continuous high‑power work, use sunlight/wind exposure, larger surface area, or a stationary base.

---

## Features
- **Multi‑source harvesting:** PV (indoor+outdoor), TEG (small temp gradients), motion (piezo/EM), RF (rectenna).
- **Decades‑ready storage:** supercaps for bursts + **Li‑SOCl₂** backup (never recharged; ultra‑low self‑discharge).
- **Energy‑aware firmware:** always‑on sentinel at **≤10–100 µW**, burst tasks only when charge is available.
- **Contactless top‑ups (optional):** Qi/inductive coil or short‑range optical pad.
- **Robustness:** derated voltages, FRAM (no wear), watchdogs, brownout protection, sealed enclosure.

---

## Quick Start
### 1) Simulate an energy budget (no hardware)
```bash
python3 software/tools/energy_sim.py --hours 48 --area_m2 0.05 --lux_indoor 800 --sun_hours 4   --avg_load_uW 80 --burst_power_W 5 --burst_seconds 1 --burst_every_min 30
```

### 2) Build firmware (PlatformIO)
- Install [PlatformIO](https://platformio.org/install).  
- Compile a native test or an embedded target:
```bash
# Native (host) build for quick logic tests
pio run -e native

# Example embedded target (STM32L0 Nucleo) — edit platformio.ini to your board
pio run -e nucleo_l073rz
```

### 3) Directory layout
```
e-core-robot-heart/
├─ README.md
├─ LICENSE
├─ CONTRIBUTING.md
├─ CODE_OF_CONDUCT.md
├─ SECURITY.md
├─ .gitignore
├─ docs/
│  ├─ architecture.md
│  ├─ power_budgeting.md
│  ├─ parts.md
│  ├─ safety.md
├─ hardware/
│  ├─ bom.csv
│  └─ README.md
├─ firmware/
│  ├─ platformio.ini
│  ├─ README.md
│  ├─ include/config.h
│  ├─ src/main.cpp
│  └─ lib/
│     ├─ harvester/Harvester.h
│     ├─ harvester/Harvester.cpp
│     └─ power/PowerBus.h
├─ software/
│  ├─ tools/energy_sim.py
│  └─ examples/default_power_profile.yaml
└─ examples/
   └─ energy_profiles.md
```

---

## Build Philosophy
- **Harvest > Load (most days):** keep the always‑on rail tiny (10–100 µW).
- **Burst, don’t stream:** short high‑power actions from supercaps; then recover.
- **Derate everything:** voltage/current/temperature margins extend life massively.
- **Fail soft:** if one harvester fails, others keep you alive.

See **docs/** for diagrams, math, and safety.

---

## License
MIT © 2025 xatusbetazx17

---

## Credits
Designed by the community; initial repository scaffolding by **xatusbetazx17**.
Mega Man inspiration acknowledged as cultural flavor only; no IP from the games is included.
