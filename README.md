**log is stil in early design, prototype coming soon!**

All consumer cameras work like this: 
- The sensor spits out a stream of 0s and 1s
- In the processor, an **exaggerated** amount of computationally-expensive algorithms (e.g. demosaic, TNR, ...) transform those 0s and 1s into a real, viewable image with its own proprietary 'look' and color profile.
- All of these algorithms have to run _before_ you even see a live preview on the screen; let alone the JPEG or MP4 that gets stored on the SD card.

**log** is fundamentally different. It writes the RAW 0s and 1s directly to the SD card.* 
No onboard processing. 
The heavy task of image signal processing is offloaded to the far more powerful laptop or phone that the images are eventually exported to.

This makes **log** less of a camera, and more of a **sensor data logging device**, hence the name.

**Goal**: A durable, reliable, and affordable point and shoot memory capturer. _Feeling_ over resolution and analog-style shooting that stays fully out of your way.

**Design Principles**: Quality materials, robust parts, efficient computing, extreme battery life, simplicity and comfort when in doubt.

This design draws a clear parallel to film:
- Images take time to be 'revealed' on the device.
- Until revealed, the images are in a fragile limbo, trapped inside a black box. They exist technically - but much like exposed, undeveloped film, they don't truly exist as images.


*some **lossless** compression is used on the RAW sensor data to reduce system bandwidth
