# Built-in Commands Documentation

This document describes the currently implemented built-in commands in the minishell project.

## Overview

The minishell currently implements **5 out of 7** required built-in commands:
- ✅ `echo` - Display text with optional formatting
- ✅ `cd` - Change directory with multiple options
- ✅ `pwd` - Print working directory
- ✅ `env` - Display environment variables
- ✅ `exit` - Exit the shell with optional exit code
- ❌ `export` - **NOT IMPLEMENTED** (export variables to environment)
- ❌ `unset` - **NOT IMPLEMENTED** (remove environment variables)

---

## 1. `echo` - Display Text

**File**: `src/built-in/bi_echo.c`

### Description
Displays the provided arguments separated by spaces, with an optional newline at the end.

### Syntax
```bash
echo [OPTION] [STRING...]
```

### Options
- `-n`: Do not output the trailing newline

### Implementation Details
- **Line 10-14**: Detects `-n` flag and sets `n_flag` if present
- **Line 15-21**: Iterates through arguments, printing each with spaces between
- **Line 22-23**: Adds newline unless `-n` flag was used
- **Line 24**: Sets exit status to 0 (success)

### Examples
```bash
$ echo hello world
hello world
$ echo -n hello world
hello world$ 
```

### Exit Status
Always returns 0 (success).

---

## 2. `cd` - Change Directory

**File**: `src/built-in/bi_cd.c`

### Description
Changes the current working directory and updates PWD and OLDPWD environment variables.

### Syntax
```bash
cd [DIRECTORY]
cd -
cd
```

### Behavior
- **`cd`** (no arguments): Changes to HOME directory
- **`cd -`**: Changes to OLDPWD directory  
- **`cd <path>`**: Changes to specified directory

### Implementation Details
- **Line 17**: Saves current directory as OLDPWD
- **Line 23-41**: Handles `cd` with no arguments (uses HOME)
- **Line 42-60**: Handles `cd -` (uses OLDPWD)
- **Line 61-71**: Handles `cd <directory>`
- **Line 72-78**: Attempts directory change with `chdir()`
- **Line 87-89**: Updates PWD and OLDPWD environment variables

### Error Handling
- HOME not set or empty
- OLDPWD not set or empty
- Directory doesn't exist
- Permission denied

### Examples
```bash
$ cd /home/user    # Change to /home/user
$ cd               # Change to HOME directory
$ cd -             # Change back to previous directory
```

### Exit Status
- 0: Success
- 1: Error (invalid directory, HOME not set, etc.)

---

## 3. `pwd` - Print Working Directory

**File**: `src/built-in/bi_pwd.c`

### Description
Prints the absolute pathname of the current working directory.

### Syntax
```bash
pwd
```

### Implementation Details
- **Line 5**: Uses `getcwd(NULL, 0)` to get current directory
- **Line 6-11**: Error handling if getcwd fails
- **Line 12-13**: Prints directory path with newline
- **Line 14-15**: Cleanup and set exit status

### Examples
```bash
$ pwd
/home/user/projects/minishell
```

### Exit Status
- 0: Success
- 1: Error (unable to determine current directory)

---

## 4. `env` - Display Environment Variables

**File**: `src/built-in/bi_env.c`

### Description
Displays all environment variables in the current shell session.

### Syntax
```bash
env
```

### Implementation Details
- **Line 7-12**: Error handling for too many arguments
- **Line 13-17**: Handle case where environment is empty
- **Line 18-25**: Iterate through environment array and print each variable

### Error Handling
- Rejects any arguments with "too many arguments" error

### Examples
```bash
$ env
PATH=/usr/bin:/bin:/usr/sbin:/sbin
HOME=/home/user
USER=user
PWD=/home/user/projects
...
```

### Exit Status
- 0: Success
- 127: Too many arguments provided

---

## 5. `exit` - Exit Shell

**File**: `src/built-in/bi_exit.c`

### Description
Exits the shell with an optional exit code.

### Syntax
```bash
exit [EXIT_CODE]
```

### Implementation Details
- **Line 5**: Prints "exit" message
- **Line 6-11**: Error handling for too many arguments
- **Line 12-13**: Sets exit status from argument if provided
- **Line 14**: Calls cleanup function and exits

### Behavior
- **`exit`**: Exits with current shell exit status
- **`exit N`**: Exits with status N (converted via `ft_atoi`)
- **`exit N M ...`**: Error - too many arguments

### Examples
```bash
$ exit          # Exit with current status
exit
$ exit 42       # Exit with status 42
exit
$ exit 1 2      # Error - too many arguments
env: too many arguments
```

### Exit Status
- Uses provided argument or current shell exit status
- 1: Too many arguments error (but doesn't exit)

---

## Built-in Detection System

**File**: `src/built-in/built_in.c` (referenced)
**File**: `src/utils/main_utils.c:15-43` (dispatcher)

### Detection Function
The `is_builtin()` function checks if a command is a built-in by comparing the first argument.

### Dispatcher Function  
The `dispatch_builtin()` function in `main_utils.c` routes built-in commands to their respective implementations:

```c
static int dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt)
{
    if (ft_strncmp(cmd->args[0], "env", 4) == 0)
        bi_env(sh, cmd);
    else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
        bi_echo(sh, cmd);
    else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
        bi_exit(sh, cmd, prompt);
    else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
        bi_pwd(sh);
    else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
        bi_cd(sh, cmd);
    return (0);
}
```

---

## Missing Built-ins (To Be Implemented)

### `export` - Export Environment Variables
**Status**: ❌ Not implemented
**Priority**: High
**Expected behavior**: Export variables to make them available to child processes

### `unset` - Remove Environment Variables  
**Status**: ❌ Not implemented
**Priority**: High
**Expected behavior**: Remove variables from the environment

---

## Notes for Implementation

1. **Memory Management**: All built-ins properly clean up allocated memory
2. **Exit Status**: All built-ins set appropriate exit status in `sh->exit_status`
3. **Error Handling**: Comprehensive error messages written to stderr (fd 2)
4. **Environment Integration**: cd properly updates PWD/OLDPWD variables
5. **Bash Compatibility**: Behavior matches bash for implemented features