#!/usr/bin/env python3
import argparse, math, random

def simulate(hours=24, area_m2=0.05, lux_indoor=800, sun_hours=4.0,
             avg_load_uW=80.0, burst_power_W=5.0, burst_seconds=1.0, burst_every_min=30):
    """
    Extremely simple energy budget simulator.
    - day: 'sun_hours' at outdoor peak, remainder indoor lux
    - PV model is coarse; for real design, replace with measured curves
    """
    # Coarse PV model:
    # Indoor: ~ (lux * area_m2) * k_in (W/lux/m2)
    # Outdoor: cap at ~200 W/m2 * area_m2 * panel_eff
    panel_eff = 0.20
    k_in = 3e-7   # rough W per lux per m^2
    outdoor_W_per_m2 = 200.0  # conservative average in usable hours

    dt_s = 1.0
    steps = int(hours*3600/dt_s)
    vcap = 2.1
    vmin, vok, vmax = 1.9, 2.2, 2.5
    load_W = avg_load_uW * 1e-6
    burst_interval_s = burst_every_min*60
    next_burst_t = burst_interval_s
    joules = 0.0

    def pv_power_W(t):
        hour = (t/3600.0) % 24.0
        if hour < sun_hours:  # outdoor window
            return outdoor_W_per_m2 * panel_eff * area_m2
        else:
            return lux_indoor * area_m2 * k_in
    results = []
    for t in range(steps):
        harv = pv_power_W(t)
        # net energy this step
        e_in = harv * dt_s
        e_out = load_W * dt_s
        joules += (e_in - e_out)

        # very crude mapping of joules to cap voltage
        vcap = max(vmin, min(vmax, 2.1 + 0.00005*joules))

        fired = False
        if t >= next_burst_t and vcap >= vok:
            # consume burst energy
            e_burst = burst_power_W * burst_seconds
            joules -= e_burst
            vcap = max(vmin, 2.1 + 0.00005*joules)
            next_burst_t += burst_interval_s
            fired = True

        if (t % 600) == 0:
            results.append((t, vcap, joules, harv, fired))
    return results

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--hours", type=float, default=24)
    ap.add_argument("--area_m2", type=float, default=0.05)
    ap.add_argument("--lux_indoor", type=float, default=800)
    ap.add_argument("--sun_hours", type=float, default=4.0)
    ap.add_argument("--avg_load_uW", type=float, default=80.0)
    ap.add_argument("--burst_power_W", type=float, default=5.0)
    ap.add_argument("--burst_seconds", type=float, default=1.0)
    ap.add_argument("--burst_every_min", type=float, default=30)
    args = ap.parse_args()

    res = simulate(**vars(args))
    print("t[s], Vcap[V], Joules[J], PV_in[W], burst_fired")
    for t, v, j, p, fired in res:
        print(f"{t},{v:.3f},{j:.2f},{p:.3f},{int(fired)}")
