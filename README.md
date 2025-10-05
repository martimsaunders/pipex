# pipex

## 💡 Overview
**pipex** is a project from [42 Lisboa](https://www.42lisboa.com) that recreates the behavior of shell pipelines.  
It focuses on understanding **process creation**, **inter-process communication**, and **file descriptor management** in UNIX systems using system calls such as `pipe`, `fork`, `dup2`, and `execve`.  

This version includes **bonus features integrated into the main program**, such as **multiple pipes** and **here_doc** support.

---

## Key Concepts
- File descriptors and I/O redirection  
- Pipes and inter-process communication  
- Using `fork`, `execve`, and `waitpid`  
- Error handling and resource management  
- Handling **multiple pipes** and **here_doc** input  

---

## Compilation / Installation
```bash
git clone https://github.com/martimsaunders/pipex.git
cd pipex
make
```

---

## Usage
### Standard Pipeline
```bash
./pipex infile "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 > outfile
```
### Multiple Commands
```bash
./pipex infile "cmd1" "cmd2" "cmd3" ... "cmdN" outfile
```
Equivalent to:
```bash
< infile cmd1 | cmd2 | cmd3 | ... | cmdN > outfile
```
### Here Document
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
Equivalent to:
```bash
cmd1 << LIMITER | cmd2 >> outfile
```

---

## Tech Stack
- C
- UNIX API (`pipe`, `fork`, `dup2`, `execve`, `access`, `waitpid`)
- Makefile

---

## Challenges / Lessons Learned
- Managing file descriptors between parent and child processes
- Dynamically creating and chaining multiple pipes
- Handling here_doc correctly and safely
- Implementing solid error handling for system calls
- Deepening understanding of UNIX process management

---

## System Calls Used
- `pipe()` – creates a communication channel between processes
- `fork()` – spawns new processes
- `dup2()` – redirects file descriptors
- `execve()` – executes commands
- `waitpid()` – waits for process completion
- `access()` – checks file accessibility

---

Author

- Martim Prazeres Saunders
