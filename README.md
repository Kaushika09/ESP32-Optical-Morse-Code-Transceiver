# ESP32 Optical Morse Code Transceiver

An ESP32-based optical Morse Code Transceiver that can both **transmit and receive Morse code** using an LED and an LDR.

The project supports two operating modes: transmission through LED light signals and reception by detecting light variations with an LDR. A buzzer provides audio feedback during transmission, while decoded Morse characters are displayed through the Serial Monitor.

## Features

- 🔴 Optical Morse code transmission using an LED
- 🔊 Buzzer feedback during transmission
- 💡 Optical Morse code reception using an LDR
- 🔄 Switchable Transmit / Receive modes
- 🎛️ Adjustable light detection threshold using a potentiometer
- 🔤 Supports letters A–Z and numbers 0–9
- 🖥️ Serial Monitor for input and decoded output
- 🧪 Simulated and tested using Wokwi

## How It Works

### Transmit Mode

1. Enter a character or message through the Serial Monitor.
2. The ESP32 converts the characters into Morse code.
3. The LED flashes the corresponding Morse pattern.
4. The buzzer provides audio feedback.

### Receive Mode

1. An external light source is directed toward the LDR.
2. The LDR detects changes in light intensity.
3. The ESP32 determines whether the signal represents a dot or dash.
4. The Morse pattern is decoded into the corresponding character.
5. The decoded message is displayed in the Serial Monitor.

## Hardware Components

| Component | Purpose |
|---|---|
| ESP32 | Main microcontroller |
| LED | Optical Morse transmission |
| Buzzer | Audio feedback |
| LDR | Optical signal detection |
| Potentiometer | Light detection threshold adjustment |
| Push Button | Mode selection |

## Pin Configuration

| Component | ESP32 GPIO |
|---|---:|
| LED | GPIO 2 |
| Buzzer | GPIO 4 |
| Mode Switch | GPIO 18 |
| Potentiometer | GPIO 34 |
| LDR | GPIO 35 |

## Technologies Used

- ESP32
- Arduino C/C++
- Wokwi
- Analog Light Detection
- Morse Code Encoding & Decoding
- Serial Communication

## Project Structure

```text
ESP32-Optical-Morse-Code-Transceiver/
│
├── diagram.json
├── sketch.ino
└── wokwi-project.txt
