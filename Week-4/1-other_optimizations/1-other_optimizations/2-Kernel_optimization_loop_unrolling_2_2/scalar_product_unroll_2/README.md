# Code Usage
This sample code is meant to be used within Vivado HLS 2017.2.
Within this document you can find instructions on how to create a new Vivado HLS project starting from the source code from this folder and on how to execute:

1. Vivado HLS Synthesis
2. Software Simulation
3. Hardware Emulation

## Create a Vivado HLS project

1. Open Xilinx Vivado HLS 2017.2
2. Select a specific workspace (unless you specified to not ask again)
3. From the top menu click on: File -> New Project
4. Provide a name and location for the Project, then click "Next"
5. Click on "Add files..." and import the kernel source code: **scalar_product.cpp**
6. Specify the top function by clicking on "Browse" and selecting **scalar_product**, then click "Next"
7. Click on "Add files..." and import the TestBench file: **test.cpp**, then click "Next"
8. Select a target FPGA by clicking on "..." in the "Part Selection" area, then click "Finish"

## Running Vivado HLS Synthesis

1. From the top menu click on: Solution -> Run C Synthesis -> Active Solution
2. If the synthesis completes successfully, the synthesis report will show up providing information on the kernel latency and resource utilization
3. By clicking on the "Analysis" button on the top right part of the window you can access the scheduling performed by Vivado HLS

## Running Software Simulation

The software simulation can be used to verify the correctness of your high-level C/C++ code. The software simulation will compile your code and launch the TestBench files (here **test.cpp**) that will run the kernel function and verify the output results.
In order to run the C Simulation, from the top menu simply click on: Project -> Run C Simulation.

## Running Hardware Emulation

The hardware emulation can be used to verify the correctness of the RTL generated from the Vivado HLS Synthesis. When running the hardware emulation, Vivado HLS use the same TestBench used for software simulation and automatically generates the corresponding RTL logic for testing. In order to run the hardware emulation, from the top menu simply click on: Solution -> Run C/RTL Co-simulation, then click "OK".

