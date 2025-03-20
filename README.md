# Pipex

## Overview
This project implements a program that simulates the functionality of shell pipes in C. It creates a pipeline between commands, redirecting the output of one command as input to the next, while also handling file input/output redirection.

## Table of Contents
- [Functionality](#functionality)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Implementation Details](#implementation-details)
- [Bonus Features](#bonus-features)

## Functionality
The program `pipex` replicates the behavior of the shell command:
```bash
< file1 cmd1 | cmd2 > file2
```

It takes input from `file1`, processes it through `cmd1`, pipes the output to `cmd2`, and stores the final result in `file2`.

## Requirements
- GCC compiler
- Unix-based environment (Linux/macOS)
- Make

## Installation
Clone the repository and compile the program:
```bash
git clone https://github.com/yourusername/pipex.git
cd pipex
make
```

## Usage
### Mandatory part
```bash
./pipex file1 cmd1 cmd2 file2
```

### Bonus part
For multiple pipes:
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

For here_doc functionality:
```bash
./pipex here_doc LIMITER cmd1 cmd2 file
```

## Examples
```bash
# Example 1
./pipex infile "ls -l" "wc -l" outfile
# Equivalent to: < infile ls -l | wc -l > outfile

# Example 2
./pipex infile "grep a1" "wc -w" outfile
# Equivalent to: < infile grep a1 | wc -w > outfile

# Bonus example (multiple pipes)
./pipex infile "ls -l" "grep a" "wc -l" outfile
# Equivalent to: < infile ls -l | grep a | wc -l > outfile

# Bonus example (here_doc)
./pipex here_doc EOF "grep hello" "wc -w" outfile
# Equivalent to: grep hello << EOF | wc -w >> outfile
```

## Implementation Details
This program focuses on:
- File input/output redirection
- Process creation and management using `fork()`
- Interprocess communication via pipes
- Command execution using `execve()`
- Proper error handling and memory management

### Functions used:
- `open`, `close`, `read`, `write`
- `malloc`, `free`
- `perror`, `strerror`
- `access`
- `dup`, `dup2`
- `execve`
- `exit`
- `fork`
- `pipe`
- `unlink`
- `wait`, `waitpid`

## Bonus Features
- Multiple pipe handling: Ability to handle any number of commands in the pipeline
- Here_doc support: Implementation of the `<<` (heredoc) and `>>` (append) functionality
