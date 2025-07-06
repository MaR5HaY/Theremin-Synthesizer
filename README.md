**Theremin Synth + FX Box**

A gesture-controlled Theremin-style musical instrument with built-in digital effects. Powered by Arduino, this project transforms hand motion into pitch while applying real-time FX like tremolo, glitch, and reverb.


**Features:**

- Ultrasonic pitch detection
- Musical notes from A (440 Hz) to A5 (880 Hz)
- FX Modes: Clean, Tremolo, Glitch, Reverb
- LCD display showing current FX mode and musical note
- Mute toggle using long-press button
- Potentiometer-controlled FX speed/depth


**Components Used:**

- Arduino Uno/Nano
- HC-SR04 Ultrasonic Sensor
- I2C 16x2 LCD Module
- Push Button
- 10k Potentiometer
- NPN Transistor + 100Ω Resistor
- 3.5mm Audio Jack (for external speaker/headphones)
- Optional: PT2399 digital delay (future extension)


**FX Modes:**

| Mode   | Description                  |
|--------|------------------------------|
| 0      | Clean – Just the note        |
| 1      | Tremolo – Volume modulation  |
| 2      | Glitch – Fast stutters       |
| 3      | Reverb – Simulated echo tail |

Note: Button tap toggles modes. Long press mutes/unmutes output.


**Pin Connections:**

| Component         | Arduino Pin |
|-------------------|-------------|
| Trig (Ultrasonic) | D10         |
| Echo (Ultrasonic) | D11         |
| Audio Out         | D9          |
| PWM FX Control    | D5          |
| Button            | D2          |
| Potentiometer     | A0          |
| I2C SDA (LCD)     | A4          |
| I2C SCL (LCD)     | A5          |


**How It Works:**

1.Distance to Pitch 
   The HC-SR04 measures hand distance and maps it to 8 musical notes (A–A5).

2.FX Chain
   PWM signal (via transistor) modulates the volume dynamically depending on the mode.

3.Audio Output  
   Audio signal is sent to a 3.5mm jack using a transistor amplifier circuit.


**Future Improvements:**
- Modular FX switching
- PT2399 digital delay integration
- Sine wave or wavetable sound synthesis
