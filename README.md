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

# Random Number Generator
This project needs some way to decide which sound to play. The easy way out is
to just play one sound over and over, but I wanted more variety. I could rotate
over a list of sounds sequentially, but then I'd have to store which sound
played previously in the EEPROM and worry about wear leveling and all sorts of
mess, so I decided to just choose a random sound every time the chip starts up.
This also has the added bonus of not getting locked into a monotonous loop if
you want to play a few sounds in a row.

On the advice of a few threads over at AVRFreaks, I played around with using ADC
noise as an entropy source for a random number generator. I tried using the
internal temp sensor, but it ended up working much better to use ADC5, the pin
furthest from the GND pin. It probably didn't matter which pin I used (not that
I tested pin vs. pin performance), but it seemed like that was a free way to get
a little bit more noise on the line. That's a weird sentence to type, but noise
is desirable in this case!

The random number generator itself is dead simple - I read the two LSBs of the
ADC four times to fill an 8 bit unsigned int then just modulo that number with
the number of entries in my sound file array. That number is just an index into
that array and bam - random sound. See `code/main_code/sound_files.c` for the
implementation.

To test the randomness I cycled the chip 100 times and recorded the output of
the RNG. The histogram of the results is shown below - not the most even
distribution but certainly random enough for my purposes. This test also
doubled as a stability test, and I'm happy to report that it ran flawlessly,
with no errors or hiccups, all 100 times in a row!

![Histogram showing the results of 100 test runs of the RNG. The distribution is
satisfactorily random.](code/main_code/rng_histogram.png)
