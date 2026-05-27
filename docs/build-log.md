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
- 2 `74LS14` (hex inverter/schmitt trigger)
- 1 `74LS161` (binary counter)
- Too many 104 caps and 8x 330 ohm resistors

### Results
- Good compatability between `UDN2981` and `ULN2803`
- Need polished [breadboard-compatible PCB](../pcb/8x8) for better breadboard prototyping
- Need to check scalability (final to have 8 total matrices)


 format
    - [ ] 16x8 memory subsystem test (5/22)
    - [ ] design change (5/27)