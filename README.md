**log** - Ultra-Low-Power ISP-Less Dispo Camera — System Overview

**Sensor & Data Capture:**
Sony IMX678, 2-lane MIPI CSI-2 → directly streams RAW Bayer to FireBeetle 2 ESP32-P4 (no ISP). MCU performs lightweight compression (delta + zigzag + RLE) and writes to 256 GB SD. All high-speed differential lanes include proper GND references; low-speed lines (I²C, RESET, PWDN, XCLK, power) handled via GPIO and external regulators.

**Software:**
ISP (demosaic, noise reduction, white balance...) is done post capture and offloaded to the far more powerful laptop or phone processor. The camera feeds the device repackaged and compressed RAW10 over a high speed USBC connection. A light app/script recieves the RAW10 and runs my custom ISP to sequentially "reveal" the images on the device.

**Power Management:**
4000 mAh battery; system resides in deep sleep by default. Shutter/record input triggers wake, capture, SD write, then return to deep sleep. No display or additional electronics.

**Optics & Mechanics:**
6 mm fixed lens; dual aperture f/2.0 / f/9 via sliding brass plate (<20 ms actuation). Motorized stepper autofocus with 4 discrete positions, f/9 mode requires single focus covering 0.3 m → ∞ (5 positions total). Mechanically sliding ND filter for bright-light conditions. Phototransistors used for exposure and a TOF IR module for autofocus.

**Design Philosophy:**
Minimalist, point-and-shoot form factor inspired by the **Yashica T4** / **Olympus mju I**. Pipeline optimized for RAW capture with zero onboard ISP, maximal battery efficiency, and minimal latency between capture and sleep. Storage and power capacity practically decoupled from system operation.

**Key Notes:**

* Optical/mechanical stack optimized for rapid aperture/focus transitions.
* UI design much like a point and shoot film camera.


Offloading the burden of image signal processing to the recieving device makes **log** fundamentally different than other consumer cameras. 
This design makes **log** less of a camera, and more of a **sensor data logging device**, hence the name.

This design draws a clear parallel to film:
- Images take time to be 'revealed' on the device.
- Until revealed, the images are in a fragile limbo, trapped inside a black box. They exist technically - but much like exposed, undeveloped film, they don't truly exist as images.


