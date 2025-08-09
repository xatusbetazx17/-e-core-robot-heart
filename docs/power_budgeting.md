# Power Budgeting

- Keep always‑on rail ≤10–100 µW.
- Let harvesters exceed that most days.
- Use supercaps to buffer short high‑power jobs.

Example math:
- Indoor PV ~ 1000 lux over 0.05 m² → ~100–300 mW typical (panel/geometry dependent).
- Always‑on 80 µW → ~0.00008 W; PV surplus charges caps quickly.
- A 10 J supercap burst can deliver 5 V × 1 A × 2 s = 10 J, then recover.

See `software/tools/energy_sim.py` to test scenarios.
