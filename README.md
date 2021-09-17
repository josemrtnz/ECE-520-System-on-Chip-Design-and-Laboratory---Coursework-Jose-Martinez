# System on Chip Design and Laboratory
# ECE 520
## Student: Jose Martinez
### Professor: Dr Shahnam Mirzaei


###### All labs and projects for this class are located here. This repository is intended for potential employers to look at to verify knowledge of SoC Design with FPGA.

#### Course Description:
###### Introduction to system on chip design methodology that includes the study of ZYNQ and ARM architectures, AXI Interconnect, memory, real-time operating system (RTOS), peripheral interface and components, and contemporary high-density FPGAs. Lab: This laboratory course reinforces the system-on-chip design concept developed in the lecture course. It focuses on software hardware co-design and development and hardware verification of ZYNQ systems using Vivado software tools and ZYNQ development boards.

#### Coursework:

| Assignment | Description |
|--- | --- |
| [Lab 1](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%201/ECE_520L_LAB1_Jose_Martinez.pdf)  | First Design on Zynq GPIO |
| [Lab 2](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%202/ECE_520L_LAB2_Jose_Martinez.pdf)  | UART & GPIO |
| [Lab 3](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%203/ECE520L_Lab3_JoseMartinez.pdf)  | IP Creation and Integration |
| [Lab 4](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%204/ECE_520L_LAB4_Jose_Martinez.pdf)  | Design of SPI Slave Core |
| [Lab 5](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%205/ECE_520L_LAB5_Jose_Martinez.pdf)  | Interrupts |
| [Lab 6](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%206/ece520L_JoseM_Lab6.pdf)  | High Level Synthesis |
| [Lab 7](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%207/ece520L_JoseM_Lab7.pdf)  | Vivado HLS Design Flow |

#### Course Projects: 

| Project | Description |
|---|---|
|**Mini Project 1**|A project where the Zynq processor was used to generate a waveform based on parameters given to the function. Data generated from this function is stored in BRAM.|
|[*Mini Project 1 Folder*](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Lab%207/ece520L_JoseM_Lab7.pdf)|All of mini project 1 contents are located here.|
|[*waveformGen.c*](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Mini%20Project%201/waveformGen.c)|File used to generate data, store to BRAM, and transmit to computer using UART.|
|[*Matlab Script to Display Waveform*](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Mini%20Project%201/matlab_script/wgff.m)||
|[*Waveform*](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Mini%20Project%201/waveform.PNG)|![Waveform](Mini%20Project%201/waveform.PNG)|
|**Mini Project 2**|A project where code for Vivado HLS was used to take an image preform binary conversion, an average filter, inverting pixels, scaled pixels, and compressing/decompressing an image. |
|[*Mini Project 2 Folder*](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/tree/main/Mini%20Project%202)|All of mini project 1 contents are located here.|
|[*Matlab Script to Display Images*](https://github.com/josemrtnz/ECE-520-System-on-Chip-Design-and-Laboratory---Coursework-Jose-Martinez/blob/main/Mini%20Project%202/matlab_script/r_g.m)||
|[HLS Code](/Mini%20Project%202/HLS)|HLS code written in c applying the filters required.|
|[Results]()|![Results](Mini%20Project%202/matlab_output.PNG)|
|**Final Class Project**| Project of my choosing in which I decided to attach a laser diode to a pair of servos. My design included Zynq Processors as well as PLL elements such as PWM control and IPS for controlling various PMOD peripherals. |
|[*Project Overview*](/Course%20Project/ECE520%20Final%20Presentation%20Jose%20Martinez.pdf)| Slides in which the project was presented to the class to give a brief overview about the project. (Includes video demonstration) |
|[*Vivado Block Design*](/Course%20Project/block_design.PNG)|![Block Design](/Course%20Project/block_design.PNG)|
|[PS C code](Course%20Project/main.c)| C code for the Zynq processor to control the logic of the program.|
