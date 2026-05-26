# TTL Logic Analyzer Architecture
*todo:
- CLK must be ANDed with read/write 
- rework BUILD section
  - how hardware-based should it be? "this connects to this" etc?
  - should it be more flow based since connections are in diagrams?
  - should it be more explanation based?
  
## Overview
- Analyzer is comprised of two halves
    - **Memory Subsystem**
    - **Display Subsystem**
- Operates in read or write mode
    - Read mode: data is read from **Memory Subsystem** and is output on the **Display Subsystem**
    - Write mode: on each clock pulse, data from target device is sequentially saved into **Memory Subsystem**
## System I/O
### Target device connections
- **CLK**: target device clock
- **Data In**: 8 channels of target device
- **GND**: common ground between analyzer and target device
### System Controls
- **RUN** (active high): enable write mode 
- **HLT** (active high): enable read mode
- **HLT Word EN** (active high): enables word-based halting 
- **HLT Word**: defines 8-bit input where system should halt
## Example Usage
1. **HLT Word EN** is tied low to disable word-based halitng
2. **CLK**, **Data In**, and **GND** are connected to target device
3. **RUN** is briefly pulled high, putting the system into write mode
4. On each clock pulse, data from the target device is saved to the **Memory Subsystem**
5. **HLT** is briefly pulled high, putting the system into read mode
6. The **Display Subsystem** addresses data from the **Memory Subsystem** and displays it on LED matrices

## Memory Subsystem Architecture
**Capacity**: 64 samples x 8-bit sample size
### 74xx Hardware
- 8 `74189` RAM chips
- 2 `74LS157` selector chips
- 2 `74LS161` binary counter chips
- 2 `74LS14` hex inverter/schmitt trigger
- 1 `74LS32` OR gate chip
- 2 `74LS85` 4-bit comparator chips
- 1 `74LS21` quad input AND gate chip
- 1 `74LS279` SR-latch chip
- 4 `74LS245` octal tristate buffer chips
- 2 `74LS08` AND gate chips
- 1 decoder

___
### Low level I/O
- Target device connections
    - **CLK** (rising edge): advance internal counter
    - **Data In**: 8 channels of target device
    - **GND**: common ground between analyzer and target device
- Controls
    - **RUN** (active high): set SR-latch
    - **HLT** (active high): reset SR-latch
    - **HLT Word EN** (active high): enables word-based halting 
    - **HLT Word**: defines 8-bit input where system should halt
- **Display Subsystem** connections
    - **R/W** (high on write): state of SR-latch
    - **Address In** (6-bit): for external addressing during read mode

## Build
### R/W latch
- R/W state is stored in SR-latch (set = write, reset = read)
### RAM units (4 total)
- 1 RAM chip for high 4 bits
- 1 RAM chip for low 4 bits
- Pullup resistors on RAM chips' outputs
- 1 tristate buffer
- All units share buffers connected to data bus, which is negated with hex inverters to become **Data Out**
### Addressing (6-bit)
- Decoder chips use A5-A4 to select active RAM unit
- A3-A0 select data on active RAM unit
- 2 binary counter chips comprise 6-bit internal counter
- 6-bit external counter is from **Address In** of **Display Subsystem**
- Internal and external counters are routed through 2 selector chips
    - Read mode (select high) enables internal counter
    - Write mode (select low) enables external counter
### Word-based Halting
- **Data In** is routed to side A of comparator chips
- **HLT Word** is routed to side B of comparator chips
- Equivalence signal from comparators and **HLT Word EN** are routed to quadrouple input AND gate
- Output of AND gate is fed through OR gate to reset of SR-latch
### Manual Halting (available regardless of halt mode)
- **HLT** is routed through OR gate to reset of SR-latch

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
5. On each **CLK** pulse, internal counter advances and targets next RAM memory location
6. **CLK** pulse writes data into RAM at memory location 