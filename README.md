# Assembler Programming Project - User Handbook

## Created by: Nikhil Sodemba

### Refer to this project for educational purposes only

The following link is the instructions needed to carry out the functionality of this project: [Assembler Programming Project](https://www.cs.kzoo.edu/cs230/Projects/AssemblerProj.html)

Marks received for project: 108.75 / 110.0 points (98.86%).

### Welcome to the assembler program

This programs main use is to act as a compiler for the transition from assembly language to machine language.

An assembler is important because it gives instructions to a machine (computer/phone/ect.), in a format which that machine can comprehend. It is one of the many forms of compilers which exists in the real world today. It is crucial to understand how assembly language is transmittd to machine language.

**Important Notes:**

- The program will take a (.txt) file, where each line of the line is read and processed as an individual instruction. The files used for this program should contain assembly language.
- If the assembly language instruction contains a branch/jump operation, ensure that the instruction has a valid label for the operation.
- This program is friendly with comments in the file, and will process the instructions regardless of the fact that the assembly language file has comments ('#').
- The program uses all files (except test-files) in the directory to function, each file has in-depth declaration and comments about its' functionality.

**How to use the program:**

- Open your terminal and direct the path to this programs directory. Use "make assembler" to generate the files this program will use.
- After the "make" command has initiated the output file for the program. Run "./assembler test.txt 0" into the command line to see the magic happen. User may specify to turn debugging mode off/on by using either 0 or 1, after the text file: 0 = turn debugging mode off, 1 = turn debugging mode on.

**Test files:**

- In order to maintain efficiency and correctness, this program includes many test files to benchmark test this program. The following files are listed below, alongside with the test input/output (debugging mode has been turned off) and declaration. I will only showcase the input/output for the 'test.txt' file. All other files will only have its' declaration.

### 1) test.txt

- This file is intended for new users, it runs with no errors. The file has valid assembly language instructions for all format types and uses labels.

- **Input:**

        main:   lw $a0, 0($t0) 
        begin:  addi $t0, $zero, 0        # beginning
                addi $t1, $zero, 1
        loop:   slt $t2, $a0, $t1         # top of loop
                bne $t2, $zero, finish
                add $t0, $t0, $t1
                addi $t1, $t1, 2
                j loop                    # bottom of loop
                jr $ra
                sll $a0, $a1, 4
                lui $a0, 300
        finish: add $v0, $t0, $zero

- **Output:**

        10001101000001000000000000000000

        00100000000010000000000000000000

        00100000000010010000000000000001

        00000000100010010101000000101010

        00010101010000000000000000000111

        00000001000010010100000000100000

        00100001001010010000000000000010

        00001000000000000000000000000011

        00000011111000000000000000001000

        00000000000001010010000100000000

        00111100000001000000000100101100

        00000001000000000001000000100000

### 2) testAllRegisters.txt

- This file is intended to test all 32 registers. It will run with no errors.

### 3) testAllErrors.txt

- This file is intended to test all errors in the program. It will run with errors.

### 4) testAllOps.txt

- This file is intended to test all of the format type instructions in the program.

Feel free to experiment with the program, using any of the provided files or your own assembly language instruction files.

You can also see the input in all of the files in their corresponding files and see the output in their respective ".out" files
