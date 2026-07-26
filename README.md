# Skippy

A fully custom mechanical keyboard designed for mac from the ground up, including the PCB, and 3D-printed case. This project combines electronics and mechanical design to create a unique ergonomic keyboard.

## Features

+ Custom PCB designed in KiCad

+ RP2040-based controller

+ QMK Firmware support

+ Hot-swappable mechanical switches

+ Custom 3D-printed case

+ Custom switch plate design

+ Rotary encoder for media controls

+ OLED display for custom information display

+ RGB lighting support

+ Designed for an ergonomic typing experience

## Design Tools

### Electronics

  + KiCad — PCB schematic and layout
  
### Mechanical Design

  + Fusion 360 — CAD modeling

## Hardware

  + Raspberry Pi Pico W RP2040 Development board
  + Outemu Yellow Jade Silent Switch 
  + EC11 15 mm Half Handle
  + 1.3" OLED SSH1106 128X64 I²C Communication (White)
  + SK6812 MINI-E RGB
  + Kailh Hot-Swap PCB Socket
  + White Steel Stabilizers (Plate Mount)
  + M2 screws (legth=4mm)
  + Threaded inserts (length=4.5mm)

## Firmware

The keyboard runs custom QMK firmware with the following features:

### RGB Lighting
+ Theme 1: RGB Off
+ Theme 2: White reactive ripple effect on key press
+ Theme 3: RGB rainbow loop animation
### OLED Display

The OLED displays the current Words Per Minute (WPM) using QMK's WPM feature, accompanied by a smooth wave animation.

<img width="1029" height="551" alt="Screenshot 2026-07-26 at 7 34 46 AM" src="https://github.com/user-attachments/assets/0d2793b5-3119-4164-8eab-d461cdc1a863" />

### Rotary Encoder
+ Rotate clockwise: Increase system volume
+ Rotate counterclockwise: Decrease system volume
+ Press the encoder: Mute or unmute the system volume

### Firmware Compilation and Flashing


The firmware for Skippy is located in the `Firmware` folder. It contains the custom QMK files used for the keyboard, including:

- `keyboard.json`
- `config.h`
- `rules.mk`
- `keymap.c`

### Compiling

To compile the firmware, copy the `Firmware` folder into your local QMK `keyboards` directory and rename it to `skippy` if needed.

Then run:

```bash
qmk compile -kb skippy -km default
```

### Flashing

Since Skippy uses an RP2040, hold the **BOOTSEL** button while plugging the keyboard into your computer. A drive named **RPI-RP2** will appear. Copy the generated `.uf2` file onto the drive, and the keyboard will automatically reboot with the new firmware.


    
## Gallery



#### AI generated Mock up


<img width="735" height="263" alt="Screenshot 2026-07-10 at 1 04 04 AM" src="https://github.com/user-attachments/assets/a3a266cd-49bc-430b-a05c-ec646eedfb89" />



#### Image from Keyboard Layout Editor


<img width="780" height="309" alt="Screenshot 2026-07-10 at 1 04 09 AM" src="https://github.com/user-attachments/assets/12991e20-77d1-441c-9fc8-44a9567a0d74" />



#### PCB Schematic


<img width="994" height="638" alt="Screenshot 2026-07-10 at 1 02 39 AM" src="https://github.com/user-attachments/assets/e7d31eca-38f7-4dd9-a4cb-758c12d4cca3" />



#### Final PCB


<img width="1121" height="455" alt="Screenshot 2026-07-10 at 1 02 55 AM" src="https://github.com/user-attachments/assets/71d9a1b1-86b3-4741-a011-5f1758d05365" />



#### Final PCB 3D Model with all the Components 


<img width="1311" height="754" alt="Screenshot 2026-07-10 at 12 31 56 AM" src="https://github.com/user-attachments/assets/a601bc16-44f0-472a-acde-be64c5b086cc" />



#### Plate 3D Model


<img width="1409" height="717" alt="Screenshot 2026-07-10 at 1 04 48 AM" src="https://github.com/user-attachments/assets/6f8ce34e-b4fa-4b01-ac0e-a72db26eabf5" />



#### 3D Model of the Case


<img width="1354" height="782" alt="Screenshot 2026-07-10 at 1 05 00 AM" src="https://github.com/user-attachments/assets/051b23e9-e6fe-4602-98ef-b9d891480704" />



#### Final Render


<img width="1276" height="719" alt="Render" src="https://github.com/user-attachments/assets/0f8eb0da-3cde-44ba-8581-0c32aad06206" />

