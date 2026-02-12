**log** - **Ultra-Low-Power ISP-Less Dispo Camera — System Overview**

**Sensor & Data Capture:**
Sony IMX678, 2-lane MIPI CSI-2 → directly streams RAW Bayer to FireBeetle 2 ESP32-P4 (no ISP). MCU performs lightweight compression (delta + zigzag + RLE) and writes to 256 GB SD. All high-speed differential lanes include proper GND references; low-speed lines (I²C, RESET, PWDN, XCLK, power) handled via GPIO and external regulators.

**Power Management:**
4000 mAh battery; system resides in deep sleep by default. Shutter/record input triggers wake, capture, SD write, then return to deep sleep. No display or additional electronics.

**Optics & Mechanics:**
6 mm fixed lens; dual aperture f/2.0 / f/9 via sliding brass plate (<20 ms actuation). Motorized stepper autofocus with 4 discrete positions, f/9 mode requires single focus covering 0.3 m → ∞ (5 positions total). Mechanically sliding ND filter for bright-light conditions.

**Design Philosophy:**
Minimalist, point-and-shoot disposable form factor. Pipeline optimized for RAW capture with zero onboard ISP, maximal battery efficiency, and minimal latency between capture and sleep. Storage and power capacity decoupled from system operation.

**Key Notes:**

* MIPI CSI-2 fully leveraged for 2-lane RAW capture.
* Compression minimizes write bandwidth while preserving pixel fidelity.
* Optical/mechanical stack optimized for rapid aperture/focus/filter transitions.
* MCU serves strictly as data path and control; sensor timing, wake, and sleep entirely firmware-managed.


**log** is fundamentally different. It writes the RAW 0s and 1s directly to the SD card.* 
No onboard processing. 
The heavy task of image signal processing is offloaded to the far more powerful laptop or phone that the images are eventually exported to.

This makes **log** less of a camera, and more of a **sensor data logging device**, hence the name.

This design draws a clear parallel to film:
- Images take time to be 'revealed' on the device.
- Until revealed, the images are in a fragile limbo, trapped inside a black box. They exist technically - but much like exposed, undeveloped film, they don't truly exist as images.

Design: (if you know cameras) its a digital **Yashica T4** / **Olympus mju I**

***lossless** compression is used on the RAW sensor data to reduce system bandwidth
