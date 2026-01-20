OFF - Nothing is on   
ON - Lives in deep sleep, only e-ink display is on    
Wakes from deep sleep on any button press
       
On shutter press (no half press)
- MCU Wake ~2ms
- Trigger IR ~5ms
- Trigger light meter (parallel)
- MCU processes ~5ms
- Move focus ~10ms  (to x, y, z, ∞)
- Move aperature (parallel)
- Shutter capture ?ms
- Write to SD card ~200ms
- Back to sleep
       - If in fixed focus mode:
       - Same, without IR or focus move

Optional half press button on back??? 
- In AUTO: Hold focus and exposure to recompose and garauntee it fires
- In fixed modes, hold exposure and give chance to recompose
- Green led lock indication

Photo protocol:
- Avoid moving aperature unless necessary
- Play with ISO and shutter speed before changing aperature (power draw)

Video protocol:
- Also avoid changing aperature
- ISO and shutter ideally, aperature if necessary
- IR and refocus every second
- Meter light every 0.5s but only adjust ISO, shutter or aperature if scene lighting actually changes
- Try to minimize exposure adjustment in stable lighting conditions (2-3s between adjustments)
- For example:
       - ISO change if light changes > 0.3 EV
       - Shutter change if light changes > 0.6 EV
       - Aperture change if light changes > 1.2 EV
     
On record press
- MCU Wake ~2ms
- Focus + Aperature ~20ms~
- Start recording ASAP, enter video protocol (MCU doesnt really sleep)
- Ignore any press except end record OR focus mode
- Light meter + exposure adjust every 0.5s
- IR + focus adjust every 1s
- End recording 
- Finish SD write
- Back to sleep
       - If in fixed focus mode:
       - Same, without IR or focus adjust

On focus mode press while recording
- Move focus unit
- Continue polling and adjusting aperature 

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
     
On focus mode button (cycles between focus modes)
- MCU Wake ~2ms
- MCU refreshes e-ink display to show next focus mode ~200ms
- MCU sets focusMode state ~1ms
- Move lens to appropriate spot (∞ by default for AUTO) ~10ms 
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
- Single port for transfer and charging
- When plugged in, weather in data transfer or charging, usb powers system and any leftover goes to the battery.
- Button in app triggers usb mode on the camera so it doesnt auto-activate when connected to any usb-capable device - we might just want to charge
- By default charge only
     
------------------------------------------------------------------------------------------------------------
     
Indicator LED Notes
- On ending photo/video write - green flicker to show finished SD writing, saved correctly
- During long shutters (>1/10s) - red rapid flashes
- During long SD writes - multicolor write blips?
- On recording video - slow blinking red
- While sleeping - nothing, only e-ink stays on
- On trying to fire flash but flash not recharged - rapid double yellow flash
- Engage ND! Overexposed! - yellow static
- Charging in progress - slow blinking yellow
- Charging complete - static green
- Detecting / setting up USB data - quick green flashes
- Data transfer - hyper fast blips in sync with writes and reads (multicolor)
- On battery dying - rapid blinking red
- On power on - 1s green
- On power off - 1s + 2 fast blips red
     
E ink display Notes
- Shows BATTERY percentage, SD percentage, focus mode, flash icon, timer icon
- Only indicator of if camera is off or in deep sleep / standby
- Charging - Nothing changes, battery percentage goes up
- Shows if ND is engaged and if it should be
     
Haptic notes
- On photo capture - iPhone like cli-click
- On video start - low thuck
- On video end - single click
- On no focus grab - zzzt
- On flash not ready - short vibrate?
- On plugged in - thu-thuck

------------------------------------------------------------------------------------------------------------

Focus UI
- No half press
- AUTO fires if IR confidence is over x%, otherwise nothing
- Fallback fixed modes ALWAYS fire
- For video, can toggle focus modes, but AUTO refocuses every second or two
- Focus modes = x, y, z, ∞, AUTO (xyz depend on final optics)
- Focus measurement from center of frame only
- If wanting to "recompose" a shot switch to a fixed mode
- Can use the 3x zoom etched line as rough focus square

VF UI
- Small LCD in bottom left displays current zoom level (e.g. 1.7x)
- Small end of fiber optic cable shows indicator led in bottom right
- LCD triggered by any zoom level >1x, off rest of time
- Discrete etched EDGE LINES (no corners) for 2x and 3x zoom.
- Tune VF optics for typical focus distance (no way around focus breathing)
- VF near sensor ideally

Timer UI (simple, traditional)
- Press shutter
- Bright red pulses every 1s x9
- Rapid puleses in last 1s
- Fire

Timelapse UI - requires external module
- Ignores a flash press, timer press and mode press
- Has to be done in a fixed focus mode (no refocusing)
- Recalculates exposure before shooting each time
- This add on will come far after the first camera protoype

