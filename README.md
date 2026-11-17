# OSCAP: Open-Source Customizable Ambilight Project

I had an addressable RGB strip lying around in my room and wanted to sync it to my PC as an ambient backlight. Unfortunately, most off-the-shelf Ambilight kits are either overpriced or rely on an HDMI passthrough box. In almost all cases, those boxes are capped at **HDMI 2.0 (18 Gbit/s)**—which means sacrificing image quality, refresh rate, or HDR on a modern monitor. My own **2K HDR 165Hz** setup requires roughly **20 Gbit/s** of throughput (and 4K high-refresh monitors demand even more), so an HDMI bottleneck simply wasn't an option.

That's why I started **OSCAP**: a modular, zero-bottleneck Ambilight system designed to work with almost any PC setup.

### How It Works
The concept is straightforward: instead of intercepting a video cable, a lightweight PC application reads the screen edges directly from GPU memory, processes and averages the colors, and streams the data to a microcontroller—either **wired via USB** or **wirelessly over Wi-Fi**. Down the road, I also plan to integrate **Home Assistant** so other smart lights in the room can join the sync.

### The OSCAP-Box (Hardware Highlights)
* **Flexible Power Input:** Equipped with two different barrel jack sizes alongside a screw terminal input, supporting anything from **5V up to 24V** without forcing you to cut up your power supply cables.
* **Multi Microcontroller Support** The system uses [platformIO](https://platformio.org/) so that it can run on almost any microcontroller. 
* **High Power Handling:** Rated for up to **10A total**—giving you up to **240W of LED power at 24V** (plenty for full-room or large-screen setups).
* **4 Independent Outputs:** Features **4 controllable data buses**, allowing you to easily split and manage multiple LED strips across your desk or room.

### 100% Open-Source & DIY Friendly
OSCAP is built for makers, gamers, and tinkerers. Everything you need to build, modify, or expand your own unit will be made publicly available in this repository:
* **Source Code:** The full PC capture/visualizer software and microcontroller firmware.
* **Electronics & PCB Files:** Complete electrical schematics, Bill of Materials (BOM), and production-ready **Gerber files** so you can order the custom PCB yourself.
* **3D Printable Enclosure:** Ready-to-print STL/3D CAD files for the OSCAP-Box housing.

Whether you want to build it on a breadboard or order custom PCBs and 3D-print the case, anyone who wants to make their own OSCAP is free to do so.

*(Reference: [HDMI Bandwidth Specifications](https://en.wikipedia.org/wiki/HDMI))*


## Roadmap

* **v0.1 — Proof of Concept (Completed)**
  Initial hardware setup tested with a lightweight script to capture screen colors and drive addressable LEDs via USB.
* **v0.3 — Full Documentation & Bill of Materials**
  Publication of the initial electrical schematics, Bill of Materials (BOM), and hardware documentation for OSCAP.
* **v0.5 — Sampling Engine & HDR Optimization** *(Optional Alpha Release)*
  Release of the screen-capture and color-sampling engine, including system requirement benchmarks. *(Depending on community interest, an early Alpha release may be published at this stage).*
* **v0.6 — Linux Support**
  Porting the capture engine to Linux (target display server architecture—X11/Wayland—to be determined).
* **v0.8 — Foolproof Hardware & 3D Enclosure (`/hardware`)**
  Publication of the complete custom PCB design (Gerber files) and 3D-printable enclosure models.
* **v1.0 — Plug & Play Release & 2D Room Visualizer**
  Introduction of the 2D Room Visualizer GUI to visually map LED strips and address ranges, alongside background service / system-tray support.
* **v1.1 — Wireless & Smart Home Ecosystem**
  Addition of wireless Wi-Fi streaming mode and Home Assistant integration so external smart lights can sync with the setup.

## License

OSCAP is dual-licensed depending on the type of files:

* **Software (`/pc-app`, `/firmware`):** Licensed under the **GNU General Public License v3.0 (GPLv3)**. You are free to use, modify, and distribute the code, provided that any derivative work is also released under GPLv3 with attribution. See [LICENSE-SOFWARE](LICENSE-SOFTWARE) for details.
* **Hardware, 3D Models & Documentation (`/hardware`, `/docs`):** Licensed under the **Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0)**. You may share and adapt the 3D models and schematics with proper attribution, strictly for non-commercial purposes. See [LICENSE-HARDWARE](LICENSE-HARDWARE) for details.

## AI Disclosure & Code Quality

Parts of the codebase, documentation, and architectural brainstorming for OSCAP were developed with the assistance of AI tools. However, **no code is blindly merged**: every line of generated code is thoroughly reviewed, refactored, and tested on real hardware before being committed to this repository to ensure reliability, performance, and safety.
