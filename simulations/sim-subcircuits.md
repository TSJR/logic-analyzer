# Simulation Subcircuits

## `analyzer_7400.circ` — 74xx IC Implementation

- **main**: Current implementation connecting the memory subsystem (`mem_16x8`) to the display subsystem (`disp_16x16`).
- **mem_64x8**: Full memory subsystem test built from 74xx chips using 4 `ram_unit` subcircuits.
- **ram_unit**: 16x8 RAM unit built from 74xx  chips; used as building block for `mem_64x8`.
- **mem_16x8**: Limited-capacity memory subsystem test; reflects the current working design
- **disp_16x16**: Limited-capacity display subsystem test; does not include the physical driver circuitry needed for hardware

## `analyzer_ttl.circ` — Abstract Logic Implementation

- **main**: Current implementation connecting `mem_64x8_async` to the display subsystem (`disp_16x32`).
- **mem_64x8_async**: Asynchronous version of the 64x8 memory subsystem; same capacity as the final intended design
- **mem_64x8**: Original 64x8 memory subsystem design; same capacity as the final intended design
- **disp_16x32**: Full-capacity display subsystem test