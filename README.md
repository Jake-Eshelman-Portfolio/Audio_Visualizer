LCD Audio Visualizer

An ongoing project to explore audio visualization on the Teensy 4.1 MCU. This setup takes in audio from a microphone via I2S, processes it with FFT, and displays it on an LCD screen over SPI.

Components
- **Teensy 4.1**
- **SGTL5000** audio codec
- **ILI9341_t3** LCD

Building & Flashing
- Built using PlatformIO (Arduino framework) for VS Code.
- Flashing is handled via Teensy Loader using PlatformIO's integrated tool.

Progress (as of 9/3/24)
- Basic LCD audio visualization is functional.
- Project video: https://drive.google.com/drive/folders/1r5S8tVGhgMvAbBuU4rN-VzRu5Oz8auLu?usp=sharing

References
- Prototyping System for Teensy 4.1: https://protosupplies.com/product/prototyping-system-for-teensy-4-1/
- Audio Tutorials and Workshop: https://protosupplies.com/learn/audio-tutorials-and-workshop/
