# TTL Logic Analyzer Build Log
## 5/22
Built bare minimum driver for a single 8x8 dot matrix as a test for display subsystem. 

Rows (matrix anodes) were driven by a high-sidedriver controlled by hardcoded inputs. A binary counter was connected to a 3-8 demultiplexer to select the active column, whose signal controlled a low-side driver. Driver output was connected via 330 ohm resistors to the columns (matrix cathodes).

Ben Eater's design of 555 timer-based clock module was used for incrementing the binary counter. 

Note: A `74LS138` was used as the demultiplexer since it was what was on hand, but it uses active low signalling so it effectively selects 7 columns at once. Its outputs were negated with 2 `74LS14` chips. A `74LS238` (active high) will be used in the future to improve the design.

### 8x8 Dot Matrix Driver
![Dot matrix driver](../images/build-progress/prog1.png)

### Used Components
- 1 `UD2981` (high-side  driver)
- 1 `ULN2803` (low-side driver)
- 1 `74LS138` (3-8 demulitplexer) 
- 1 `74LS14` (hex inverter/schmitt trigger)
- 1 `74LS161` (binary counter)
- Too many 104 caps and 8x 330 ohm resistors

### Results/Future
- Good compatability between `UDN2981` and `ULN2803`
- Need polished [breadboard-compatible PCB](../pcb/8x8) for better breadboard prototyping
- Need to check scalability (final to have 8 total matrices)

## 5/23
Built 16x8 memory subsystem laid out in [simulation](../simulations/analyzer_7400.circ), though halt word enable system and RAM output inversions were omitted for simplicity.

**Design change #1**: `74LS245` tri-state buffer added to avoid having to build a 32-8 line multiplexer. Each RAM unit will have a buffer whos outputs are shared.

**Design change #2**: `74189` chips have open collector output (not consider in simulation), so 10k pull-up resistors were added.

**Design change #3**: Incoming clock signal had to be converted to rising edge via RC circuit (not considered in simulation). Implementing this meant passing the clock pulse through an RC circuit and into a schmitt trigger, effectively negating the clock pulse. The circuit had to be redesigned with this in mind.

**Potential design change**: D flip-flop might be completely unnecessary. Though in the original design it made for sample buffering (sampled data on the clock pulse when analyzer was halted), this may be removed entirely. It would make the system significantly more simple, and it makes sense to limit the number of samples given the already limited 64 sample memory.

**Design change updates will be reflected in the simulation soon.**

### 16x8 Memory Subsystem
![16x8 memory subsystem](../images/build-progress/prog2.png)

### Used Components
- 2 `74189` (RAM)
- 1 `74LS157` (4x 2-1 multiplexer)
- 1 `74LS161` (binary counter)
- 1 `74LS279` (SR-latch)
- 1 `74LS74` (D flip-flop)
- 1 `74LS32` (OR gate)

After the memory subsystem was finished, it was connected to the matrix driver for a quick test. Its behavior was quite unpredictable, likely due to button debouncing and the edge detection circuit.

### 16x8 Memory Subsystem with Matrix Driver
![16x8 memory subsystem w/ matrix driver](../images/build-progress/prog3.png)

### Results/Future
- Major noise despite a plethora of 104 caps. This size memory unit is probably the maximum that can be built on breadboards. Moving forward it will be done on modular PCBs. 
- Reconsider clock gating on RAM chips since 74xx they aren't meant for high frequency operations.
- Redesign simulation w/ design changes
- If simulation still works, rebuild the entire system (still only 16x8, but possibly with a "dummy" secondary RAM unit to test RAM unit selection). 
