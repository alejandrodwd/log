All consumer cameras work like this: 
- The sensor spits out a stream 0s and 1s
- In the processor, an EXAGGERATED amount of computationally-expensive algorithms (eg. demosaic, TNR, ...) transform those 0s and 1s into a real, tangible image with its own proprietary 'look' and color profile.
- All these algorithms _have_ to run before you even see the preview on the screen; let alone the jpeg or mp4 that gets stored on the SD card.

**log** is fundementally different, writing the RAW 0s and 1s directly to the SD card.* 
No onboard processing. 
The heavy task of image signal processing is offloaded to the far more powerful laptop or phone that the images are eventually exported to.
This design draws a nice paralell to film, where:
- images will take some time to be 'revealed' on the device.
- and, until revealed, the images are in a fragile 'limbo' of existance in the black box that is the camera. They exist technically, but much like exposed, undeveloped film, they dont. 

*some **lossless** compression is used on the RAW sensor data to reduce system bandwith
