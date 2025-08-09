# Firmware

Two targets:
- **native**: builds a host executable for logic/scheduling tests.
- **nucleo_l073rz**: example embedded target (STM32L0). Edit `platformio.ini` for your board.

Key concepts:
- **Always‑on sentinel** keeps life‑support running.
- **Energy homeostasis** allows bursts only if supercap voltage > threshold.
- **Fail‑safe** brownout/WD protection to never kill the sentinel rail.
