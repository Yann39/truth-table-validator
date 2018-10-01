# Truth table validator

The purpose of this project was to offer a simple Windows console application for calculating truth tables of combinatorial logic circuit using **C++** and **ASM** (**Assembly**) languages.

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

We call **node** any input of the circuit and any logic gate output.
The nodes are numbered beginning with the entries and ending with the exit of the circuit.
A circuit can then be represented by a sequence of integers including the number of entries,
the number of logical gates, and the numbers (identifiers) representing the two input and output of each door.

The example circuit above would be represented as follow :

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

represents the following circuit :

![Combinatorial circuit example](doc/circuit2.png?raw=true "Combinatorial circuit example")

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

## Licence

WTFPL license : http://www.wtfpl.net/

But a mention is always appreciated :)