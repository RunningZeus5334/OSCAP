# OSCAP
OSCAP: Open-Source Customizable Ambilight Project


# OSCAP Roadmap & Todo List

## v0.1 — Proof of Concept (Completed)
- [x] Set up GitHub repository with dual-license (`LICENSE-SOFTWARE` + `LICENSE-HARDWARE`) and AI disclaimer[cite: 1, 4]
- [x] Binary USB serial data protocol (`0xAA 0x55`) with support for 3 independent buses[cite: 1]
- [x] Working end-to-end test on Raspberry Pi Pico W with Windows DXGI (`BetterCam`) and `NeoPixelBus`[cite: 1]

## v0.5 — Sampling Engine & HDR Optimization
- [ ] **Zone Mapper:** Link the left, top, right, and bottom of the screen to specific LED ranges and/or buses[cite: 1]
- [ ] **Response Settings:** Adjustable sampling depth (`sample_depth`), smoothing speed (EMA filter), and color calculation (average vs. dominant)[cite: 1]
- [ ] **HDR Tone Mapping:** Saturation and gamma correction for vivid colors in Windows HDR mode[cite: 1, 2]
- [ ] **Color Orders:** Support for `RGB`, `GRB`, `RGBW`, and `RGBWW` on the PC side[cite: 1, 2]

## v0.8 — Foolproof Hardware & 3D Enclosure (`/hardware`)
- [ ] **PCB Design** The PCB should be able to handle a total of 10 Amps. And 4 Amps per bus
- [ ] **Galvanic Isolation & Level Shifting:** Schematic based on the **TI ISO6440DWR** (4-channel digital isolator, 3.3V to 5V, up to 150 Mbps) to keep the PC 100% isolated from the LED power circuit
- [ ] **Universal 5V–24V Pass-Through Power Supply:** Parallel input with both a **5.5×2.1mm DC barrel jack** (plug-and-play without cutting the adapter) and a 2-pin screw terminal, connected to a small internal buck converter for the isolator
- [ ] **Hardware Protection:** Overvoltage protection (P-MOSFET), TVS diode against voltage spikes, and 3x resettable PTC polyfuses on the strip outputs[cite: 1]
- [ ] **Enclosure:** 3D-printed housing with strain relief and 3 standard 3-pin outputs (`V+`, `Data`, `GND`)[cite: 2]

## v1.0 — Plug & Play Release & 2D Room Visualizer
- [ ] **2D Room Visualizer GUI:** Visual editor to place your screen and LED strips in your room/setup and assign address ranges[cite: 1, 2]
- [ ] **Auto-Discovery:** Automatic USB port detection via OSCAP handshake (no more manual COM port selection needed)[cite: 1]
- [ ] **Background Service:** System tray application with an option to start automatically with Windows[cite: 1]

## v1.1 — Wireless & Smart Home Ecosystem
- [ ] **WiFi / UDP Streaming:** Wireless control of ESP32 / Pico W controllers via a lightweight UDP protocol (e.g., DDP or WLED realtime)[cite: 1, 2]
- [ ] **Home Assistant Integration:** Software integration to let wireless smart lamps and LED strips in the room match the screen colors

## License

OSCAP is dual-licensed depending on the type of files:

* **Software (`/pc-app`, `/firmware`):** Licensed under the **GNU General Public License v3.0 (GPLv3)**. You are free to use, modify, and distribute the code, provided that any derivative work is also released under GPLv3 with attribution. See [LICENSE-SOFWARE](LICENSE-SOFTWARE) for details.
* **Hardware, 3D Models & Documentation (`/hardware`, `/docs`):** Licensed under the **Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)**. You may share and adapt the 3D models and schematics with proper attribution, strictly for non-commercial purposes. See [LICENSE-HARDWARE](LICENSE-HARDWARE) for details.

## AI Disclosure & Code Quality

Parts of the codebase, documentation, and architectural brainstorming for OSCAP were developed with the assistance of AI tools. However, **no code is blindly merged**: every line of generated code is thoroughly reviewed, refactored, and tested on real hardware before being committed to this repository to ensure reliability, performance, and safety.
