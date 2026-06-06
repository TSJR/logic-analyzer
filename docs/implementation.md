# TTL Logic Analyzer Implementation
## Overview
- Analyzer is comprised of two halves
    - **Memory Subsystem**
    - **Display Subsystem**
- Operates in read or write mode
    - Read mode: data is read from **Memory Subsystem** and is output on the **Display Subsystem**
    - Write mode: on each clock pulse, data from target device is sequentially saved into **Memory Subsystem**
## Memory Subsystem
### 74xx Hardware
- 8 `74189` RAMs
- 2 `74LS157` selectors
- 2 `74LS161` binary counters 
- 2 `74LS14` hex inverter/schmitt trigger
- 1 `74LS32` OR gate chip
- 2 `74LS85` 4-bit comparators
- 1 `74LS21` quad input AND gate
- 1 `74LS279` SR-latch chip
- 4 `74LS245` octal tristate buffers
- 2 `74LS08` AND gates
- 1 `74LS139` decoder
### Additional Hardware
- 8x `1088AS` 8x8 dot matrix
- 32x 5-10k pullup resistors
- unknown amount of breadboards
- a lot of wires

## Build
### RAM Units
The memory subsystem contains 4 RAM units. Each RAM unit is comprised of:
- 2 `74189` 16x4 RAM ICs
- 8 pullup resistors
- 1 `74LS245` octal tri-state buffer

Connections are as follows:
- **Data In Bus**[7:4] to data inputs of first `74189`
-  **Data In Bus**[3:0] to data inputs of second `74189`
- All 8 `74189` outputs are pulled high and connected to side A of `74LS245`
- Side B of `74LS245` is connected to **Data Out Bus**
- The `74LS245` is wired for A->B operation

## Display Subsystem
## Timing/Control Logic
## Bus Architecture
### Data Bus
### Address Bus
## Known Issues
## Implementation notes
