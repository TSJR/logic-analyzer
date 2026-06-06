### ATtiny Logic Analyzer
24-channel ATtiny85-based logic analyzer built on a custom PCB

## Overview
This project is a tool for use in debugging other projects. It reads from 24 data inputs using 3 `74LS595` chips connected to the ATtiny85. The ATtiny then displays the inputs on an LCD screen via I2C protocol. It is asynchronous, meaning it displays what data is being read at all times, and it does not store read data. This makes it unusable for situations where consecutive sample rates are necessary, but it's helpful for taking a look at the state of a system one sample at a time. 

The first prototype of the project is complete.

## Features
- 24 channel analysis
- `74LS595` shift registers for many inputs
- ATtiny MCU
- 16x2 LCD via I2C protocol
- 3D printed housing

## Repository Structure
```text
code/               Arduino code
images/             Images of schematics and builds
models/             3D model files (STLs designed with onshape)
pcb/                KiCad schematic and PCB design
```

## License
MIT License