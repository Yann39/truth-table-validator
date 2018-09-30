# Truth table validator

The purpose of this project was to offer a simple Windows console application for calculating truth tables of combinatorial logic circuit using **C** and **ASM** (**Assembly**) languages.

This program was part of a school project and was created in **May 2007**.

It was originally created with **Microsoft Visual Studio 2003**. The ASM part was validated using **Emu8086**.

## Usage

Just run the _truth-table-validator.exe_ file, then enter some circuit representation and execute to obtain the output.

See below for input format.

## Description

### Combinatorial logic circuit

The program only consider combinatorial circuit composed of **NAND** logical gates.

Example :

![Combinatorial circuit example](doc/circuit1.png?raw=true "Combinatorial circuit example")

## Input format

We call node any input of the circuit and any logic gate output.
The nodes are numbered beginning with the entries and ending with the exit of the circuit.
A circuit can then be represented by a sequence of integers including the number of entries,
the number of logical gates, and the numbers (identifiers) representing the two input and output of each door.

The example circuit above would be represented by:

```bash
2, 4, 1, 2, 3, 1, 3, 4, 2, 3, 5, 4, 5, 6
```

Another example :

```bash
3,5,1,2,3,1,3,4,2,3,5,4,5,6,7,5,8
```

![Combinatorial circuit example](doc/circuit1.png?raw=true "Combinatorial circuit example")

## Licence

WTFPL license : http://www.wtfpl.net/

But a mention is always appreciated :)