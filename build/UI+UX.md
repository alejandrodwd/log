OFF - Nothing is on   
ON - Lives in deep sleep, only e-ink display is on    
Wakes from deep sleep on any button press
       
On shutter press (no half press)
- MCU Wake ~2ms
- Trigger IR ~5ms
- MCU processes ~5ms
- Move lens ~10ms  (to 0.5, 1, ∞)
- Decide exposure ~2ms
- Shutter capture ?ms
- Write to SD card ~200ms
- Back to sleep
     
On record press
- MCU Wake ~2ms
- Start recording ASAP, enter video protocol (MCU doesnt really sleep)
- Ignore any press except end record OR focus mode, respect focus mode as normal
- End recording 
- Finish SD write
- Back to sleep
     
On flash button
- MCU Wake ~2ms
- MCU refreshes e-ink display to show flash icon ~200ms
- MCU sets flashOn flag ~1ms
- Back to sleep
     
On timer button
- MCU Wake ~2ms
- MCU refreshes e-ink display to show timer icon ~200ms
- MCU sets timerOn flag ~1ms
- Back to sleep
     
On focus mode button (cycles between auto, 1m and 0.5m)
- MCU Wake ~2ms
- MCU refreshes e-ink display to show next focus mode ~200ms
- MCU sets focusMode state ~1ms
- Move lens to appropriate spot (0.5, 1, or ∞ by default for AUTO) ~10ms 
- Back to sleep

Camera LIVES in deep sleep. No such thing as it being "awake" apart from when its recording.
     
------------------------------------------------------------------------------------------------------------
     
Battery dying protocol
- Detect V below certain threshold
- Stop current video/photo capture
- Finish writing everything in RAM and seal
- E ink off
- Rapid blinking red
- Everything off
     
Plugged in from dead protocol
- Wake MCU
- Red static LED
- Wait till some battery charge
- Turn on E ink
- Change LED to static yellow

USB C protocol
- single port for transfer and charging
- when plugged in, weather in data transfer or charging, usb powers system and any leftover goes to the battery.
- button in app triggers usb mode on the camera so it doesnt auto-activate when connected to any usb-capable device - we might just want to charge
- by default charge only
     
------------------------------------------------------------------------------------------------------------
     
Indicator LED Notes
- On ending photo/video capture - green flicker to show finished SD writing, saved correctly
- On recording video - blinking red
- While sleeping - nothing, only e-ink stays on
- On trying to fire flash but flash not recharged - rapid double yellow flash
- Charging in progress - static yellow
- Charging complete - static green
- Detecting / setting up USB data - quick green flashes
- Data transfer - hyper fast blips in sync with writes and reads
- On battery dying - rapid blinking red
- On power on - 1.5s green
- On power off - 1s + 2 fast blips red
     
E ink display Notes
- Shows BATTERY percentage, SD percentage, focus mode, flash icon, timer icon
- Only indicator of if camera is off or in deep sleep / standby
- Charging - Nothing changes, battery percentage goes up
     
Haptic notes
- On photo capture - iPhone like cli-click
- On video start - low thuck
- On video end - single click
- On no focus grab - nothing
- On flash not ready - short vibrate?
- On plugged in - thu-thuck
