# Command Execution Study Guide - Minishell

## Overview

This document explains how command execution works in your minishell, covering both built-in commands and external command execution with detailed diagrams and examples.

---

## Table of Contents

1. [Command Flow Overview](#command-flow-overview)
2. [Built-in vs External Commands](#built-in-vs-external-commands)
3. [Fork-Exec Pattern](#fork-exec-pattern)
4. [Path Resolution System](#path-resolution-system)
5. [exec_child() Deep Dive](#exec_child-deep-dive)
6. [Process Diagrams](#process-diagrams)
7. [Error Handling](#error-handling)
8. [Memory Management](#memory-management)

---

## Command Flow Overview

### Main Loop Structure
```c
while (6)  // Infinite loop
{
    args = read_input(&prompt);              // Get user input
    if (!args) break;                        // Handle Ctrl-D
    status = cmd_setup(&shell, &cmd, args, prompt);  // Process command
    free_matrix(args);                       // Cleanup
    free(prompt);
    if (status == -1) return (shell.exit_status);   // Exit command
}
```

### Command Decision Tree
```
User Input → cmd_setup()
              ↓
         is_builtin()?
         ↙          ↘
      YES             NO
       ↓               ↓
dispatch_builtin()  exec_cmd()
       ↓               ↓
   Handle in shell  Fork + execve
```

---

## Built-in vs External Commands

### Built-in Commands (Handled Internally)
- **Commands**: `echo`, `cd`, `pwd`, `env`, `exit`, `export`, `unset`
- **Execution**: Function calls within shell process
- **No forking**: Runs in same process as shell
- **Fast**: No process creation overhead

### External Commands (Fork + Exec)
- **Commands**: `ls`, `cat`, `grep`, `vim`, etc.
- **Execution**: Create child process, replace with target program
- **Forking required**: Separate process to preserve shell
- **Slower**: Process creation overhead

---

## Fork-Exec Pattern

### Why Fork is Essential

**Without Fork (WRONG):**
```c
// This would kill your shell!
execve("/bin/ls", args, envp);  // Shell process becomes 'ls'
// Shell is gone forever after 'ls' exits
```

**With Fork (CORRECT):**
```c
pid_t id = fork();              // Create child copy
if (id == 0) {                  // Child process
    execve("/bin/ls", args, envp);  // Child becomes 'ls'
}
else if (id > 0) {              // Parent (shell)
    waitpid(id, &status, 0);    // Wait for child
    // Shell survives and continues
}
```

### Process Creation Diagram
```
Before fork():
┌─────────────┐
│   Shell     │
│ (PID: 1234) │
└─────────────┘

After fork():
┌─────────────┐    ┌─────────────┐
│   Shell     │    │   Shell     │
│ (PID: 1234) │    │ (PID: 5678) │
│   Parent    │    │    Child    │
│  - waits    │    │  - executes │
│  - survives │    │  - dies     │
└─────────────┘    └─────────────┘
```

---

## Path Resolution System

### set_path() Function Logic

```c
char *set_path(char *cmd)
{
    if (ft_strchr(cmd, '/'))        // Has '/' character?
    {
        if (access(cmd, X_OK) == 0)
            return (cmd);           // Return as-is if executable
        return (NULL);              // Not executable
    }
    return (search_in_paths(cmd));  // Search in PATH directories
}
```

### Two Types of Commands

#### Commands with '/' (Absolute/Relative paths):
```bash
# Absolute path
shell>> /bin/ls          # Uses exactly "/bin/ls"
shell>> /usr/bin/cat     # Uses exactly "/usr/bin/cat"

# Relative path  
shell>> ./my_program     # Uses exactly "./my_program"
shell>> ../tools/script  # Uses exactly "../tools/script"
```

#### Simple command names:
```bash
shell>> ls    # Searches through PATH directories
shell>> cat   # Searches through PATH directories
shell>> grep  # Searches through PATH directories
```

### PATH Search Process

When you type `ls`:

1. **Get PATH environment variable**:
   ```
   PATH = "/usr/local/bin:/bin:/usr/bin:/usr/sbin"
   ```

2. **Split by ':'**:
   ```
   {"/usr/local/bin", "/bin", "/usr/bin", "/usr/sbin"}
   ```

3. **Try each directory**:
   ```c
   1. "/usr/local/bin/ls" → access() → Not found
   2. "/bin/ls"           → access() → FOUND! ✓
   3. Return "/bin/ls"
   ```

### Visual Path Search Flow
```
User types: "ls"
     ↓
┌─────────────────────────┐
│ set_path("ls")         │
│                        │
│ No '/' in "ls"         │
│ → search_in_paths()    │
└─────────────────────────┘
     ↓
┌─────────────────────────┐
│ Get PATH variable:     │
│ "/usr/local/bin:/bin:  │
│  /usr/bin:/usr/sbin"   │
└─────────────────────────┘
     ↓
┌─────────────────────────┐
│ Try /usr/local/bin/ls  │ → Not found
│ Try /bin/ls            │ → FOUND! ✓
│ Return "/bin/ls"       │
└─────────────────────────┘
     ↓
┌─────────────────────────┐
│ execve("/bin/ls", ...) │
└─────────────────────────┘
```

---

## exec_child() Deep Dive

### Function Purpose
- Runs **only in child process**
- Finds executable program
- Replaces child process with target program
- Handles errors

### Step-by-Step Breakdown

#### 1. Find Executable Path
```c
path = set_path(cmd->args[0]);
```
- **Input**: Command name (e.g., "ls")
- **Process**: Search through PATH or validate absolute/relative path
- **Output**: Full path ("/bin/ls") or NULL

#### 2. Handle Command Not Found
```c
if (!path)
{
    print_cmd_err(cmd->args[0]);  // "command not found"
    exit(127);                    // Standard exit code
}
```

#### 3. Update Command Arguments
```c
cmd->args[0] = path;
```
- **Before**: `{"ls", "-la", NULL}`
- **After**: `{"/bin/ls", "-la", NULL}`

#### 4. Replace Process
```c
execve(path, cmd->args, sh->envp);
```
- **Replaces** child process with target program
- **Never returns** on success
- **Child becomes** the new program

#### 5. Handle execve() Failure
```c
perror("minishell");      // Print error
if (path != cmd->args[0])
    free(path);           // Cleanup
exit(127);                // Exit with error
```

---

## Process Diagrams

### Complete Execution Flow

#### Initial State
```
Terminal:
shell>> ls -la

┌─────────────────────────┐
│     Shell Process       │
│ PID: 1234              │
│ State: Running         │
│ Memory: Shell code     │
│ Args: {"ls", "-la"}    │
└─────────────────────────┘
```

#### After fork()
```
Parent Process                Child Process
┌─────────────────────────┐  ┌─────────────────────────┐
│     Shell Process       │  │     Shell Process       │
│ PID: 1234              │  │ PID: 5678 (new!)      │
│ fork() returns: 5678   │  │ fork() returns: 0      │
│ State: Waiting         │  │ State: About to exec   │
│ Memory: Shell code     │  │ Memory: Shell code     │
│ Action: waitpid()      │  │ Action: exec_child()   │
└─────────────────────────┘  └─────────────────────────┘
```

#### execve() Transformation
```
BEFORE execve():
┌─────────────────────────┐
│     Child Process       │
│ PID: 5678              │
│ Memory: Shell code     │
│ Program: minishell     │
└─────────────────────────┘

execve("/bin/ls", {"/bin/ls", "-la", NULL}, envp)
                    ↓

AFTER execve():
┌─────────────────────────┐
│     Child Process       │
│ PID: 5678 (same PID!)  │
│ Memory: ls program     │ ← COMPLETELY REPLACED!
│ Program: ls            │
└─────────────────────────┘
```

#### Program Execution
```
Parent (Shell)             Child (ls program)
┌─────────────────────────┐  ┌─────────────────────────┐
│ PID: 1234              │  │ PID: 5678              │
│ State: WAITING         │  │ State: RUNNING         │
│ waitpid(5678, ...)     │  │ Executing ls -la       │
│ Blocked until child    │  │ Printing files...      │
│ finishes               │  │ total 24               │
│                        │  │ drwxr-xr-x  user file1 │
│                        │  │ -rw-r--r--  user file2 │
└─────────────────────────┘  └─────────────────────────┘
```

#### Child Exit and Cleanup
```
Child finishes:
┌─────────────────────────┐
│ ls program completes    │
│ exit(0) - success!     │
│ Process 5678 DIES      │
└─────────────────────────┘
                ↓
Parent wakes up:
┌─────────────────────────┐
│ waitpid() returns      │
│ Gets exit status: 0    │
│ shell.exit_status = 0  │
│ Ready for next command │
└─────────────────────────┘
```

### Memory Layout Transformation

#### Before execve()
```
Child Process Memory:
┌─────────────────────────┐
│ Shell Code              │
│ - main()               │ 
│ - exec_child()         │
│ - All shell functions  │
│ - Variables            │
│ - Stack                │
└─────────────────────────┘
```

#### After execve()
```
Child Process Memory:
┌─────────────────────────┐
│ ls Program Code         │
│ - ls main()            │
│ - directory reading    │
│ - file formatting      │
│ - ls variables         │
│ - ls stack             │
└─────────────────────────┘
```

**Key Point**: Same PID, completely different program!

---

## Error Handling

### Command Not Found Flow
```
path = set_path("badcmd")
         ↓
   Returns NULL
         ↓
┌─────────────────────────┐
│ print_cmd_err("badcmd") │
│ Output: "badcmd: cmd    │
│         not found!"     │
│ exit(127)              │
└─────────────────────────┘
         ↓
Parent gets exit code 127
```

### Permission Denied
```bash
# User types: /root/secret_file (no execute permission)
```
1. `set_path("/root/secret_file")` → Returns `"/root/secret_file"`
2. `execve()` fails (permission denied)
3. Prints: `"minishell: Permission denied"`
4. Child exits with code 127

### Standard Exit Codes
- **0**: Success
- **127**: Command not found or execution failed
- **Other**: Program-specific exit codes

---

## Memory Management

### Key Points
- **Parent process**: Frees `args` and `prompt` after command execution
- **Child process**: May allocate `path` string, must free before exit
- **execve() success**: No cleanup needed (process replaced)
- **execve() failure**: Must free allocated memory before exit

### Memory Flow
```c
// In child process:
char *path = set_path(cmd->args[0]);  // May allocate memory

if (!path) {
    // No memory to free
    exit(127);
}

cmd->args[0] = path;
execve(path, cmd->args, sh->envp);    // Success = no cleanup needed

// Failure path:
if (path != cmd->args[0])             // Was path allocated?
    free(path);                       // Free it
exit(127);
```

---

## Key Concepts Summary

1. **Fork-exec pattern**: Standard Unix way to run programs
2. **Process isolation**: Child runs separately, can't crash parent
3. **PATH resolution**: Automatic searching for executables
4. **Synchronous execution**: Shell waits for command to finish
5. **Exit status preservation**: Command's exit code saved for `$?`
6. **Memory safety**: Proper cleanup in all execution paths

---

## Real-World Analogy

Think of `exec_cmd` like **cloning yourself** before doing a dangerous job:

- **You (shell)**: Stay safe at home
- **Your clone (child)**: Goes out, does the risky work (`ls`), might die
- **You**: Wait for clone to report back, then continue living

The fork-exec pattern ensures your shell **survives** by creating a sacrificial child that gets replaced by the target program! 🔄

---

## Study Questions

1. Why can't we use `execve()` directly without `fork()`?
2. What happens to the shell if `fork()` fails?
3. How does the PATH environment variable work?
4. What's the difference between absolute and relative command paths?
5. Why does `execve()` never return on success?
6. What exit code indicates "command not found"?
7. How does the parent process know when the child has finished?

---

*This guide covers the core concepts of command execution in your minishell. Understanding these patterns is crucial for implementing more advanced features like pipes and redirections.*