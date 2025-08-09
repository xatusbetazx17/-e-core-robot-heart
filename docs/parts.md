# Parts (initial, vendor-agnostic)

| Group | Example Part | Notes |
|------:|--------------|------|
| PV (outdoor) | Mono-Si mini tiles | High efficiency, UV-stable cover |
| PV (indoor) | a‑Si / DSSC / GaInP tile | Better spectral match at low lux |
| Harvester PMIC | TI BQ25570 / e‑peas AEM10941 | MPPT, cold‑start, supercap/batt mgmt |
| TEG | Bi₂Te₃ thin module | Needs thermal path; small ΔT → mW |
| Motion | PVDF piezo beam / micro‑EM shaker | mW while moving |
| RF | PCB rectenna + Schottky | µW–tens µW near strong sources |
| Storage | 1–10 F supercap (2.7 V) | Derate voltage for lifetime |
| Backup | Li‑SOCl₂ primary cell | Do **not** recharge; ideal diode ORing |
| MCU | STM32U / EFM32 / nRF52 | Idle µA, wake on events |
| Memory | FRAM | Practically no wear |
| Power | Buck/boost, ideal diode | Low IQ, high efficiency |
