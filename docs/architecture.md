# Architecture

```
+----------------------------- Robot Skin -----------------------------+
|  PV tiles  |  PV (indoor)  |  Piezo/Micro-EM  |  RF Rectenna        |
+------------+---------------+------------------+----------------------+
        \           \                \                   \
         \           \                \                   \
          +-----------+----------------+-------------------+
                          Harvester PMICs (MPPT, ORing)
                               |
                        +------+-------+
                        |   Supercaps  |  <-- high cycle life burst tank
                        +------+-------+
                               |
                     +---------+---------+
                     |  3.3V Life-Support |--> MCU + Sensors + FRAM (≤10–100 µW)
                     |  (buck/LDO)       |
                     +---------+---------+
                               |
                        +------+-------+
                        |  5–12V Burst |--> short 1–2 A pulses (actuators/radio)
                        |   (boost)    |
                        +------+-------+
                               |
                     +---------+---------+
                     |  Li‑SOCl₂ backup |--> ideal diode, emergencies only
                     +------------------+
```
- **Always‑on**: tiny sentinel firmware (timers, event detection, safety).
- **Burst tasks**: only when supercap > threshold (energy homeostasis).
- **Decay‑proof**: derated voltages, sealed enclosure, UV‑stable covers.
