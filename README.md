# Embedded-AGC-DSKY-emulator
Apollo Block II AGC + DSKY emulator based on the virtualagc project (https://github.com/virtualagc/virtualagc).
The system is based on an STM32 32-bit ARM Cortex MCU, with custom PCB layout to match the position of buttons and lamps 
on the original DSKY.

### Repository Layout
* **agg-kicad:** submodule by Adam Greig containing useful KiCAD libraries, footprints and scripts.
* **binary_transcoder:** simple C program to rearrange binary output of the yaYUL assembler (see **virtualagc** 
submodule) into the order required for yaAGC emulator (also contained within **virtualagc**). Note that a pre-transcoded
binary file for Luminary099 is provided in the **firmware** directory.
* **ChibiOS:** ChibiOS RTOS submodule, developed by Giovanni Di Sirio.
* **firmware:** directory containing project source code.
* **gen-board.h:** submodule containing Python tool for generating ChibiOS 'board.h' header from a YAML file.
* **pcb:** directory containing project schematics and PCB design:
    * **agc-dsky:** KiCAD schematic and PCB files.
    * **agc-dsky.pretty:** Various component footprints.
    * **lib:** Various schematic symbols.
* **virtualagc:** Virtual Apollo Guidance Computer submodule. Contents include yaYUL (Apollo language assembler) and 
yaAGC (Apollo Guidance Computer emulator).