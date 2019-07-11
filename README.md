__placeholder__

# Sample Rate
If we run the system on the 8MHz internal clock and use 8-bit resolution PWM for the audio, we'll
have a sample rate of 8000000/256=31250 Hz. I used Audacity to prepare the audio files - project
rate of 31250, split into mono and delete one channel, then export the audio to unsigned 8 bit raw.

# FAT Driver
FatFS driver - see http://elm-chan.org/fsw/ff/00index_e.html (may take a while to load)

# KiCAD
Required libraries (may not be an all-inclusive list...):
 * custom library, bundled in this repo
 * Device
 * Connector
 * MCU_Microchip_ATmega
 * Amplifier_Audio
 * Regulator_Linear
