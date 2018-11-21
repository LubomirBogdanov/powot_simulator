Description
===================================================================
Embedded software developers often write code that works
with battery-backed devices or eco-friendly equipment. Usually
they finish their code, measure its execution time and power
consumption, and try to anticipate battery life with the acquired
data. They have no preliminary knowledge of what the results
might be, because they write code at high level of abstraction
and can’t see the output assembly directly. Even if any
assembly analysis is done, it can only estimate time
performance, as long as data dependency is not involved.

Powot Simulator is an Instruction Set Simulator (ISS) that was 
first introduced in 2013 and did energy
estimations on a C function-level basis. This approach,
however, yields results that can be erroneous due to
dependency of function’s code on input data. Version 2 of the
simulator addresses this problem – by analyzing code on a
statement-level basis one can achieve better energy estimates
and localize the power-hungry sections of code. To do this,
the simulator uses simple lookup table-based model files
of microcontrollers. 

The Powot Simulator v2 is a shared object library
(libpowot_simulator.so) that could be part of a bigger
development environment. It uses Lesser GPL v3 license 
which means that can be used free of charge by other 
open source and closed source programs.


Example usage
===================================================================
1. The simulator depends heavily on the GCC toolchain. Install your
cross GCC and provide its prefix in:

powot_simulator/simulator_configs/[arch name].cfg

where each tag contains the prefix and the command line parameters
of the corresponding tools (nm, gdb, objdump):

SYMBOLLIST_COMMAND [compiler prefix]-nm
GDBDUMP_COMMAND [compiler prefix]-gdb
OBJDUMP_COMMAND [compiler prefix]-objdump -S -d

2. Next, provide a lookup table-based model of your target, that 
contains energy estimates for each instruction, in:

powot_simulator/models/mcu/[provider name]/[target name].mdl

If you can't make a model yourself check the existing ones.

3. Compile and link the code you want to analyze with NO 
optimizations, e.g.:

[compiler prefix]-gcc -O0 -o myfirmware.axf myfirmware.c

4. The repository powot_simulator_v2 contains an example front-end
application, called "powsimu", that uses the shared object file
"libpowot_simulator.so", and is a good starting point for your 
first simulation. Change to the directory where the executable 
"powsimu" is (powot_simulator_v2/powot_simulator_build/powsimu) and type:

powsimu -j /path/to/your/executable/myfirmware.axf 
-a [arch name] -p [provider name] -m [target name] -e [function name]

where [function name] is the name of the function from the executable
file myfirmware.axf that needs to be analyzed (simulated). 

Note: to make the executable work you must have Qt-Creator installed
on your machine. Also make sure that you export the .so library of the
simulator in your LD_LIBRARY_PATH (on Ubuntu):

export LD_LIBRARY_PATH+=:/path/to/git/project/powot_simulator_v2/powot_simulator_build/powot_simulator

If you run: 

echo $LD_LIBRARY_PATH

you should see the correct path to the build directory of the simulator.

5. The simulation may take anything from milliseconds to
seconds depending on the call tree and the size of the analyzed
function. When it finishes an energy table will be printed.

 


