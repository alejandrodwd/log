on shutter press it does
	- polls ir 5ms
	- thinks 5ms
	- moves lens 10ms
	- opens shutter ?ms
	- writes to sd card
	- back to sleep
no half press just all in one motion and barely any power used


on record button press it wakes everything, starts recording and then enters its video protocol where it gets to sleep some time between writes and compresses but not THAT much it kinda has to be 
awake no way around it. once the video is done recording and writing to sd, back to deep sleep.


on flash button
- wake
- cpu refreshes the e ink display to now show the flash icon
- sets the flashOn flag
- back to sleep

on timer button
- wake
- cpu refreshes the e ink display to now show the timer icon
- sets the timerhOn flag
- back to sleep

on focus mode button - (focus mode cycles between auto, 1m and 0.5m)
- wake
- cpu refreshes the e ink display to show next focus mode
- sets the focusmode state in the cpu
- moves lens to appropriate spot (0.5, 1, or infinity by default for auto)
- back to sleep


so the camera literally LIVES in deep sleep theres no such thing as it being "awake" apart from when its recording and even then it gets to sleep a tiiiny bit sometimes.



LED notes.-only need red and green for this- im thinking after ending video capture and photo capture a little green flicker of the led to show that it finished writing to sd. while recording a blinking red, and then while sleeping nothing obviously, only the e ink display. and when the camera is OFF off well the display turns off and that's the simple ui.

double yellow flash when trying to take a flash photo and flash hasn't finished recharging

for charging static yellow and then static green when full 

for data transfer some sort of very rapid blips in sync with writes.

2s rapid green flashes as usb data is being set up / detected

1.5s green on power up

1.5s + a couple blips of red on power down



HAPTIC notes

on photo capture - iphone esque cli-click
on video start - low thuck
on video end - normal click

on no focus grab - nothing
on flash not ready - 

on charging - thu-thuck
on usb data plugged in - 

