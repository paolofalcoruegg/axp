<p  align="center"><img width="auto" src=".github/Cover.jpg" alt="cover"></p>
<h1 align="center">
  Audio Experience Design
</h1>

<p  align="center">
<sup>
  <a href="https://github.com/pa17">Paolo Rüegg</a> 
</sup>
</p>

<p  align="center">
<sup><sup>
  Dyson School of Design Engineering, Imperial College London
</sup></sup>
</p>

**Arena** is an interactive cymatics installation that lets people discover how sound waves excite vibration patterns in liquids. It consists of two stations, one of which explores the effects of pure tones, and one that allows the spectator to see their own music. The genereated patterns are a visualisation of the wealth of information contained in audio signals, and are mesmerising and surprising alike. The installation was exhibited at the Dyson School of Design Engineering at Imperial College London on the 18th and 22nd of March 2019. 

### Background & Inspiration

<details>
<summary>Click to expand this section</summary><br>

A Chladni plate visualises the standing wave patterns generated at its natural resonating frequencies. The original experiment used fine particles such as sand on a steel plate, which is then excited with a bow or a loudspeaker. As the plate starts to resonate, the sand bounces from the vibrating antinodes to the stationary nodes. In mathematic terms, the nodes are the solutions (zero points) of the plate's 2D wave equation at a given frequency. At the plate's resonating frequencies, the sand coalesces around the nodal lines of the standing wave. As a consequence, so-called Chladni figures become visible, as shown below for a guitar body.

<p align="center"><img width="700" src=".github/Chladni.svg" alt="cover"></p>

This effect can be extended to liquids that are placed on a moving diaphragm. It results in beautiful patterns that are dependent on frequency and ampltitude. The project team decided to create an installation around vibrational patterns generated in liquids.

</details>

### Aims & Work Packages

<details>
<summary>Click to expand this section</summary><br>

The idea for this installation evolved from the beautiful effect oscillations can have on substances such as Non-Newtonian fluids. During a brief research phase, the team looked at previous installations, which were mostly focused on pure tones. The aim of this installation was to highlight cymatics both bottom-up and top-down, i.e. from a pure tone and complex signal (music) perspective. 

My specific responsibilities were focused on the station with custom music input and included:

1. Sound Visualisation (Light): Developing and assembling an LED array that changes in color and brightness in response to varying amplitudes in defined frequency bins
2. Sound Processing: Creating a Max MSP patch that processes music input through an AUX cable, crossfades between raw and waveshaped signals, and delivers an output signal to the driver (filtered) and headphones (raw)
3. Integration: Sourcing the required audio components and connecting hardware to software

</details>

### Sound Visualisation

This subsystem was essentially a color-changing equaliser with three frequency bins, where red, green & blue represented bass, midrange & highs. As such, a simple one-way data stream from Max MSP to a microcontroller was required, where RGB values where serially transferred. On the Max side, the full signal was passed into two crossover objects (cross~), scaled and then sent to the microcontroller. This was introduced as a bpatcher object in the top-level Max patch, retaining toggling functionality to manually control RGB levels. The full Max patch for sending data serially is available in the repository.

<p align="center"><img width="700" src=".github/LEDControl.jpeg" alt="cover"></p>

On the receiving end, the microcontroller interpreted the bytes as RGB values and controlled the LED strip. The loop function is shown below. 

```
void loop() 
{

    // Slider from MaxMSP 
    int maxmspSlider1, maxmspSlider2, maxmspSlider3;

    // Parse incoming value from MaxMSP
    // -99 is a control value 
    if (Serial.parseInt() == -99){ 
        maxmspSlider1 = Serial.parseInt();  
        maxmspSlider2 = Serial.parseInt();  
        maxmspSlider3 = Serial.parseInt();  
    }

    // Set RGB values based on Max MSP values
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i  , strip.Color(maxmspSlider1, maxmspSlider2, maxmspSlider3)); // Draw new pixel
    }
    strip.show();

    delay(20);
}
```
### Sound Processing

The normalised input audio was passed into a crossfader along with the waveshaped signal on the second input. Potentiometers actuated by the user informed both output volume and the mixing between the two channels. The output to the subwoofer was furthermore filtered using a biquad~ object, at a cutoff frequency of 120 Hz during the installation. The filtered sub  and the unfiltered headphone mono signals were sent to individual DAC outputs.

<p align="center"><img width="700" src=".github/Fader.jpeg" alt="cover"></p>

### Integration

A clear system overview was required to combine the different subsystems into a working functional prototype. It is shown below for the station I was working on.

### Build

A wooden top piece with an organic curvature was manufactured to overlay the subwoofer. The knobs were attached along with a wooden frame to hold the structure. The frame could subsequently be placed over the subwoofer, with the electronics tucked away underneath the presentation table.

### License

The source code is licensed under [GNU General Public License v3.0](LICENSE)

<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.