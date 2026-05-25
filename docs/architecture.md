# TTL Logic Analyzer Architecture

## Overview

This project is an 8-channel, 64-sample TTL logic analyzer built primarily from 74LS-series logic ICs and 74189 RAM chips.

The system continuously samples 8 input lines into RAM until either:
- a halt word is detected
- the manual halt button is pressed

After halting, the system enters read mode so captured data can be displayed and inspected.

---

# System Layout

The analyzer is divided into two major halves:

1. Memory subsystem
2. Display subsystem

---

# Memory Subsystem

The memory subsystem stores captured samples.

## Capacity

- 64 samples
- 8 bits per sample

Implemented using:
- 8 total 74189 RAM chips
- arranged as 4 sections
- each section contains:
  - one RAM chip for upper 4 bits
  - one RAM chip for lower 4 bits

Each section therefore stores:
- 16 addresses
- 8 bits wide

---

# Addressing Scheme

The system uses a 6-bit address.

- Upper 2 bits select the RAM section
- Lower 4 bits select the address within that section

## Address Breakdown

A5 A4:
- RAM section select

A3 A2 A1 A0:
- address inside selected section

---

# Write Address Generation

During capture mode:
- a 74LS161 counter generates sequential addresses
- addresses increment once per sample clock

The counter output is routed through a 74LS157 multiplexer.

---

# Read Addressing

During read mode:
- external/manual address lines are selected through the 74LS157
- this allows browsing captured memory contents

---

# Run/Halt Control

A 74LS279 SR latch controls analyzer state.

## Run Mode
- counter enabled
- RAM write active
- sequential sampling active

## Halt Mode
- counter disabled
- write disabled
- memory switched to read mode

The latch may be triggered by:
- manual halt button
- halt word detection logic

---

# Halt Word Detection

The analyzer supports automatic capture stopping using a configurable halt word.

When the input data matches the halt condition:
- the SR latch is set
- capture stops
- system enters read mode

---

# Clocking

The sample clock drives:
- RAM write timing
- address counter increments

Clean clock edges are critical to prevent:
- double clocks
- invalid writes
- metastability

---

# Future Improvements

- External clock mode
- Circular buffer
- Trigger edge selection
- Faster SRAM replacement
- USB/MCU interface
