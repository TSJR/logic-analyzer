# TTL Logic Analyzer Architecture 
## Overview
- Analyzer is comprised of two halves
    - **Memory Subsystem**
    - **Display Subsystem**
- Operates in read or write mode
    - Read mode: data is read from **Memory Subsystem** and is output on the **Display Subsystem**
    - Write mode: on each clock pulse, data from target device is sequentially saved into **Memory Subsystem**
## Design Goals
- Entire system built on 74xx chips (no MCU)
- Modular enough to increase memory capacity/display size
- Capable of capturing 64 samples
- Capable of displaying samples with vertical and horizontal scrolling
## Analyzer I/O
### Target device connections
- **CLK**: target device clock
- **Data In**: 8 channels of target device
- **GND**: common ground between analyzer and target device
### System Controls
- **RUN** (active high): enable write mode 
- **HLT** (active high): enable read mode
- **HLT Word EN** (active high): enables word-based halting 
- **HLT Word**: defines 8-bit input where the analyzer should halt
## Example Usage
1. **HLT Word EN** is tied low to disable word-based halting
2. **CLK**, **Data In**, and **GND** are connected to target device
3. **RUN** is briefly pulled high, putting analyzer into write mode
4. On each clock pulse, data from the target device is saved to the **Memory Subsystem**
5. **HLT** is briefly pulled high, putting the analyzer into read mode
6. The **Display Subsystem** addresses data from the **Memory Subsystem** and displays it on LED matrices

## Memory Subsystem Architecture
The memory subsystem captures 8-bit parallel data from a target device and stores sequential samples into RAM using an internally clocked address counter.  

**Capacity**: 64 samples x 8-bit sample size

___
### Memory Subsystem Interface
Inputs:
- **CLK**: target clock used for sampling
- **Data In**: 8-bit captured input bus
- **RUN**: enters write mode
- **HLT**: enters read mode
- **HLT Word EN**: enables automatic halt matching
- **HLT Word**: 8-bit halt-match value
- **Address In**: external read address from **Display Subsystem**

Outputs:
- **Data Out**: 8-bit stored sample output to **Display Subsystem**
- **R/W State**: current analyzer mode
___
## Memory Subsystem Organization
### R/W Mode Control
R/W state is stored in SR-latch  
- SR-latch set = write mode  
- SR-latch reset = read mode


The latch is manually reset through briefly bringing the **HLT** signal high or automatically through word-based halting logic. The latch is reset by briefly bringing the **RUN** signal high
___
### RAM Units (4 total)
Each unit is constructed with:
- 1 RAM chip for high 4 bits
- 1 RAM chip for low 4 bits
- 1 octal tri-state buffer
Total of 16 samples with 8 bits of data per unit

Decoder chip uses upper 2 address bits to select active RAM unit

All tri-state buffer outputs connect forming the data bus. Since the `74189` chip has inverted outputs, the bus must be negated with hex inverters before becoming **Data Out**
___
### Addressing
System supports internal (**Memory Subsystem**'s 6-bit counter) and external addressing (**Display Subsystem**'s 6-bit counter)

Internal addressing (write mode)
- Clock pulse advances the **Memory Subsystem**'s counter
- **Data In** is written into memory

External addressing (read mode)
- **Display Subsystem** is able to cherry pick saved data from the **Memory Subsystem** and display it

In both addressing modes, the upper 2 address bits select a RAM unit and lower 4 address bits select the current location in memory
___
### Clocking and Write Control
Two operations per clock cycle during write mode
- On rising edge, data is written to RAM
- On falling edge, internal counter is incremented
Decoder selection gates clock pulse so **Data In** is only written to the selected RAM unit

Clock is ignored in read mode as memory contents are to be accessed asyncronously
___
### Halting Modes
- Word-based Halting
    - Enters read mode when **Data In** matches user-defined 8-bit sequence **HLT Word**. Mode is only available when **HLT Word EN** is tied high
- Manual Halting
  - Enters read mode when **HLT** is pulled high
  - Available regardless of **HLT Word EN**'s state.

Neither halting mode takes a data sample when the halt word is detected to maximize the analyzer's limited memory

## Operating Mode Flows
### Read Mode
1. System is halted
   -  **HLT** pulled high or **Data In** matches **HLT Word** during word-based halting mode
2. SR-latch is reset
3. Selector chips route **Address In**, allowing **Display Subsystem** to address **Memory Subsystem** asyncronously
### Write Mode
1. **Run** is pulled high
2. SR-latch is set
3. Selector chips route internal counter
4. Internal counter is reset
5. High clock pulse writes data into RAM at memory location
6. Low clock pulse advances counter and targets next RAM memory location
n 

## Current Limitations
- 64 total samples
- 8-channel capture width
- May only work with low-frequency systems
- No internal clock
- No timestamp tracker

## Future Improvements
- 128 samples and/or 16-channel capture width
- Less primitive display (higher resolution/colors)
- Internal clock implementation
  - User-defined sample rate
  - Manual sampling with button
- If project moves away from being exclusively TTL
  - USB interface
  - Microcontroller usage
  - RAM upgrade (eg. 6116 or 6264 SRAM)