# Truth table validator

The purpose of this project was to offer a simple Windows console application for calculating truth tables of combinatorial logic circuit using **C++** and **ASM** (**Assembly**) languages.

This program was part of a school project and was created in **May 2007**.

It was originally created with **Microsoft Visual Studio 2003**. The ASM part was validated using **Emu8086**.

## Usage

Just run the _truth-table-validator.exe_ file, then enter some circuit representation and execute to obtain the output.

See below for input format.

## Description

### Combinatorial logic circuit

The program only consider combinatorial circuits composed of **NAND** logical gates.

Example :

![Combinatorial circuit example](doc/circuit1.png?raw=true "Combinatorial circuit example")

## Circuit representation

We call **node** any input of the circuit and any logic gate output.
The nodes are numbered beginning with the entries and ending with the exit of the circuit.
A circuit can then be represented by a sequence of integers including the number of entries,
the number of logical gates, and the numbers (identifiers) representing the two input and output of each door.

So the example circuit above would be represented as follow :

```bash
2,4,1,2,3,1,3,4,2,3,5,4,5,6
```

in which :
- the first value `2` indicates that the circuit contains 2 inputs
- the second value `4` indicates that the circuit contains 4 gates
- the next 3 values (`1,2,3`) indicate that a gate has entry nodes identified as n°1 and n°2 and output gate n°3
- and so on for each gates

As an other example, the following input string :

```bash
3,5,1,2,3,1,3,4,2,3,5,4,5,6,7,5,8
```

would represents the following circuit :

![Combinatorial circuit example](doc/circuit2.png?raw=true "Combinatorial circuit example")

Note that we could have entered the gate nodes (groups of 3 identifiers) in any order, for example `3,5,4,5,6,1,3,4,2,3,5,1,2,3,7,6,8`.
Only the output node must stay in last position.

## Program

The program accept as input string a coded circuit as described in the previous section, and then :
- check the integrity of the circuit, so that the set of antecedents of any node `n` associated with
the exit of a gate must contain at least one input node of the circuit and must not contain `n`
- displays the truth table of the circuit

The algorithm is quite simple, and consists of the following steps :
1. ask for user input as string
2. convert this input string (array of characters) into an array of integers (by removing the commas)
3. check the integrity of the circuit
4. if the circuit has no errors, continue
5. otherwise, stop and display the related error message(s)
6. display the number of entries of the circuit and their identifier
7. display the number of nodes / outputs of the circuit and their identifier
8. display the whole circuit truth table

Here is the program output for the input string `2,4,1,2,3,1,3,4,2,3,5,4,5,6` :

![Example circuit output](doc/example_output.png?raw=true "Example circuit output")

## Checks

The program checks the user input so it matches the following requirements :
- does not start with a comma
- does not end with a comma
- does not contain 2 commas in a row
- contain only numbers and commas
- contain at least 5 numbers
- contain at least one gate
- one circuit input has been set
- the output of a gate is not linked to one of its own inputs
- 2 gates does not have the same output
- the circuit output is really an output (not used)
- all outputs of all gates are used (except last gate)
- the number of gates indicated corresponds to the number of gates really entered
- the number of inputs indicated corresponds to the number of inputs really entered
- each numbers are less than 1000 (to avoid generating too large arrays)
- each gates has 2 inputs defined

An example error output :

![Example circuit error output](doc/example_error_output.png?raw=true "Example circuit error output")

## Assembly code

One of the requirement was to write a `int evalCircuit (int * circuit, int * entries)` function in **assembly** code (ASM).
This function accepts as parameter a pointer to the representation in memory of a circuit and a pointer
to a table of integers that contain values in {0,1}. It returns the circuit output result value.

The function was developed using the **Emu8086** software (for Intel 80x86 processors), and is integrated to the **C** program using the `_asm` instruction.

The program :
- loads tables (addresses) in the `si` and `di` registers using the `LEA` directive.
- calculates the size of the table (3 times the number of gates + 2).
- goes through the table 3 by 3, and compares the 2 entries of each door, then we execute a `NAND` operation if the 2 entries are defined (if they are 0 or 1)
- replaces the new value of the output in the result table in order to be able to calculate the other gates.

To integrate the assembly code into the **C** program, I had to use **32 bits** registers (and not **16 bits** registers as with Emu8086).
Often we even used **8 bits** registers. It is also necessary to have **32 bit** registers to be able to save the values in a **C** variable of type `int`.

Another change was to replace the `LEA` instruction by `MOV` to load the tables into the `esi` and `edi` registers, because `LEA` is difficult to handle in a C program.

We then had to modify the incrementation of the pointers of the tables as it is necessary,
with the `MOV` instruction, to increment of 4 bytes the pointer to be able to move correctly through the table (indeed integers
are coded on 32 bits : 1 byte = 8 bits, 4 bytes = 32 bits). It was therefore necessary to avoid using 16 bits and 8 bits registers.

The use of procedures has also been compromised, as the `proc` and `endp` directives are not supported by **Microsoft Visual C++** in inline assembly code.

## Licence

WTFPL license : http://www.wtfpl.net/

But a mention is always appreciated :)