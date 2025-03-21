# Pipex

<div align="center">
  <img src="https://drive.google.com/uc?id=1hlW2jOBZc3XvXujkAsG17ODC4yG0PJ66" alt="PipeX Header" width="100%">
  <p><strong>A custom implementation of Unix pipes in C</strong></p>
  <p>
    <a href="#overview">Overview</a> •
    <a href="#functionality">Functionality</a> •
    <a href="#installation">Installation</a> •
    <a href="#usage">Usage</a> •
    <a href="#examples">Examples</a> •
    <a href="#technical-details">Technical Details</a>
  </p>
</div>

## Overview

Pipex is a system programming project that replicates the behavior of Unix pipes. It demonstrates low-level process management, file descriptor manipulation, and inter-process communication techniques in C.

This project implements the core functionality of shell command pipelines, enabling data to flow seamlessly between multiple processes while maintaining proper error handling and resource management.

## Functionality

The Pipex program recreates the behavior of the shell command:

```bash
< file1 cmd1 | cmd2 > file2
```

### Process Flow

1. Read input data from `file1`
2. Execute `cmd1` with the input data
3. Pass the output of `cmd1` as input to `cmd2`
4. Write the final output to `file2`

## Installation

### Prerequisites

- C Compiler (GCC/Clang)
- Unix-based environment (Linux/macOS)
- Make

### Build Process

```bash
# Clone the repository
git clone https://github.com/ssbaytri/pipex.git

# Navigate to the project directory
cd pipex

# Compile the program
make

# Optional: Compile with bonus features
make bonus
```

## Usage

### Standard Operation

```bash
./pipex infile cmd1 cmd2 outfile
```

### Advanced Features (Bonus)

**Multiple command pipeline:**
```bash
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

**Here document support:**
```bash
./pipex here_doc DELIMITER cmd1 cmd2 outfile
```

## Examples

### Basic Command Execution

```bash
# Count the number of files in the current directory
./pipex infile "ls -l" "wc -l" outfile

# Equivalent shell command:
# < infile ls -l | wc -l > outfile
```

### Text Processing

```bash
# Count occurrences of a pattern
./pipex infile "grep pattern" "wc -w" outfile

# Equivalent shell command:
# < infile grep pattern | wc -w > outfile
```

### Advanced Pipeline (Bonus)

```bash
# Filter and process data through multiple commands
./pipex infile "cat -e" "grep pattern" "sort" outfile

# Equivalent shell command:
# < infile cat -e | grep pattern | sort > outfile
```

### Here Document (Bonus)

```bash
# Process input until delimiter with append output
./pipex here_doc EOF "grep hello" "wc -l" outfile

# Equivalent shell command:
# grep hello << EOF | wc -l >> outfile
```

## Technical Details

### Architecture

Pipex employs a parent-child process model with the following components:

- **Process Management**: Fork-based command execution
- **Pipe Communication**: Data tunneling between processes
- **File Redirection**: Input/output stream manipulation
- **Error Handling**: Robust system call validation

### Core Functions

| Category | Functions |
|----------|-----------|
| File Operations | `open`, `close`, `read`, `write`, `unlink`, `access` |
| Memory Management | `malloc`, `free` |
| Process Control | `fork`, `execve`, `wait`, `waitpid`, `exit` |
| Stream Manipulation | `pipe`, `dup`, `dup2` |
| Error Handling | `perror`, `strerror` |

### Implementation Highlights

- Zero memory leaks through careful resource management
- Comprehensive error handling for all system calls
- Minimal external dependencies (libft only)
- Follow-the-42-norm compliant code style

---

<div align="center">
  <p>Developed as part of the 42 School curriculum</p>
</div>
