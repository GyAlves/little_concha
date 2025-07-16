# Minishell Execution Flow Guide

## Overview
This document provides a comprehensive guide to understanding how the `little_concha` minishell executes commands, from user input to command completion. Follow this guide to understand the complete execution flow.

---

## 🗺️ Complete Execution Flow Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                    MINISHELL EXECUTION FLOW                     │
└─────────────────────────────────────────────────────────────────┘

1. ENTRY POINT (src/main.c)
   ├── main() 
   ├── init_minishell() ──────► Setup environment variables
   └── run_shell_loop() ───────► MAIN SHELL LOOP

2. MAIN LOOP (src/main.c:28)
   ┌─► while(6) {
   │     ├── setup_prompt() ──► Get user input & tokenize
   │     ├── setup_command() ─► Parse & execute commands
   │     ├── cleanup memory
   │     └── check exit conditions
   └─────┘

3. INPUT PROCESSING (src/utils/prompt_utils.c)
   setup_prompt() 
   ├── readline("shell>> ") ──► Wait for user input
   ├── add_history() ─────────► Save to command history  
   └── lexer() ───────────────► Split by spaces: ["echo", "hello"]

4. COMMAND PARSING (src/command/command.c)
   init_command()
   ├── count_pipes() ─────────► Detect single vs pipeline
   ├── Single: handle_single_cmd() ──► Parse one command
   ├── Multi:  handle_multi_cmd() ───► Parse pipeline
   └── exc_cmd() ─────────────► EXECUTE parsed commands

5. EXECUTION DECISION (src/utils/prompt_utils.c:77)
   exc_cmd()
   ├── process_all_heredocs() ──► Handle << redirections
   ├── IF piped ────────────────► handle_pipes()
   ├── IF parent builtin ──────► dispatch_builtin()
   └── ELSE ───────────────────► exec_cmd() (fork & execve)

6. FINAL EXECUTION
   ├── PIPES: handle_pipes() ──► Fork multiple processes
   ├── BUILTINS: dispatch_builtin() ──► Call bi_cd(), bi_echo(), etc.
   └── EXTERNAL: exec_cmd() ───► fork() + execve() + waitpid()
```

---

## 📍 Step-by-Step Execution Guide

### Step 1: Entry Point - `main()` Function
**File:** `src/main.c:53`

```c
int main(int c, char **v, char **envp)
{
    t_minishell shell;
    int status;
    
    (void)c;
    (void)v;
    
    // 1. Initialize shell structure and environment
    if (!init_minishell(&shell, envp))
        return (1);
    
    // 2. Backup original stdin/stdout for restoration
    shell.original_stdin = dup(STDIN_FILENO);
    shell.original_stdout = dup(STDOUT_FILENO);
    
    // 3. Start main shell loop (the heart of the shell)
    status = run_shell_loop(&shell);
    
    // 4. Cleanup and exit
    free_minishell(&shell);
    return (status);
}
```

**What happens here:**
- **Shell Initialization**: Sets up environment variables and shell state
- **File Descriptor Backup**: Saves original stdin/stdout for later restoration
- **Main Loop**: Enters the infinite shell loop
- **Cleanup**: Frees all allocated memory before exiting

**Key Function:** `init_minishell()` - Copies environment variables and initializes shell structure

---

### Step 2: Main Shell Loop - `run_shell_loop()`
**File:** `src/main.c:28`

```c
static int run_shell_loop(t_minishell *shell)
{
    t_command *cmd;
    char *prompt;
    char **args;

    while (6)  // Infinite loop (while(1) equivalent)
    {
        // 1. Get user input and tokenize into arguments
        if (!setup_prompt(shell, &prompt, &args))
        {
            if (shell->exit_status == 111)  // EOF (Ctrl+D)
                break;
            continue;
        }
        
        // 2. Parse arguments and execute command
        setup_command(&cmd, shell, &prompt, &args);
        
        // 3. Memory cleanup
        free_matrix(args);
        args = NULL;
        free(prompt);
        prompt = NULL;
        
        // 4. Check for exit condition
        if (shell->exit_status == 111)
            break;
    }
    return (shell->exit_status);
}
```

**This is the heart of the shell:**
- **Input Phase**: Gets user input and converts to tokens
- **Execution Phase**: Parses and executes the command
- **Cleanup Phase**: Frees allocated memory
- **Exit Check**: Handles EOF (Ctrl+D) and exit commands

**Special Exit Status 111**: Used to signal EOF condition (Ctrl+D pressed)

---

### Step 3: Input Processing - `setup_prompt()`
**File:** `src/utils/prompt_utils.c`

The input processing happens in `read_input()`:

```c
char **read_input(t_minishell *shell, char **prompt)
{
    // 1. Display prompt and wait for user input
    *prompt = readline(PROMPT);  // PROMPT = "shell>> "
    
    // 2. Handle EOF (Ctrl+D)
    if (!*prompt)
    {
        shell->exit_status = 111;
        return (NULL);
    }
    
    // 3. Handle empty input
    if (!*prompt || **prompt == '\0')
        return (NULL);
    
    // 4. Add command to history
    add_history(*prompt);
    
    // 5. Tokenize input into array of strings
    return (lexer(*prompt));
}
```

**Tokenization Process (`lexer()`):**
**File:** `src/tokenization/lexer/lexer.c`

```c
char **lexer(char *input)
{
    return (ft_split(input, ' '));  // Simple space-based splitting
}
```

**Example:**
- Input: `"echo hello world"`
- Output: `["echo", "hello", "world", NULL]`

**Limitations:**
- No quote handling (major missing feature)
- No escape sequence support
- Simple space-based splitting only

---

### Step 4: Command Parsing - `init_command()`
**File:** `src/command/command.c:34`

```c
int init_command(t_minishell *sh, t_command **cmd, char **args, char *prompt)
{
    int cmd_pipe_count;

    // 1. Validate input
    if (!args || !args[0])
        return 0;
    
    // 2. Count pipes to determine execution type
    cmd_pipe_count = count_pipes(args);
    sh->total_pipeln_cmd = cmd_pipe_count;
    
    // 3. Allocate command array
    if (!init_command_arr(cmd, cmd_pipe_count))
        return (0);
    
    // 4. Parse based on pipe count
    if (cmd_pipe_count == 1)        // Single command
    {
        if (!handle_single_cmd(cmd, args))
            return (0);
    }
    else                            // Pipeline
    {
        if (!handle_multi_cmd(cmd, args))
            return (0);
    }
    
    // 5. Execute the parsed command(s)
    return(exc_cmd(sh, *cmd, prompt));
}
```

**Parsing Decision Tree:**

```
Input: ["echo", "hello", "|", "cat"]
         ↓
count_pipes() → Returns 2 (2 commands)
         ↓
cmd_pipe_count == 1? → NO
         ↓
handle_multi_cmd() → Parse pipeline
         ↓
exc_cmd() → Execute pipeline
```

**Key Functions:**
- `count_pipes()`: Counts `|` tokens to determine number of commands
- `handle_single_cmd()`: Parses single command with redirections
- `handle_multi_cmd()`: Splits pipeline and parses each command separately

---

### Step 5: Execution Decision Engine - `exc_cmd()`
**File:** `src/utils/prompt_utils.c:77`

```c
int exc_cmd(t_minishell *sh, t_command *cmd, char *prompt)
{
    int status;
    t_std_redir backup;

    // 1. Initialize redirection backup
    backup.in = -1;
    backup.out = -1;
    
    // 2. Process all heredocs first (<<)
    if (!process_all_heredocs(sh, cmd))
        return (1);
    
    // 3. Execution decision tree
    if (cmd->is_piped)
    {
        // PIPELINE: Multiple commands connected by pipes
        return (handle_pipes(sh, cmd, count_command_args(cmd->args)));
    }
    else if (is_builtin(cmd) && is_parent_builtin(cmd))
    {
        // PARENT BUILTIN: cd, export, unset, exit
        if (!handle_redir_in_exc(sh, cmd, &backup))
        {
            restore_std_backup(&backup);
            return (sh->exit_status);
        }
        dispatch_builtin(sh, cmd, prompt);
        restore_std_backup(&backup);
        return (sh->exit_status);
    }
    else
    {
        // EXTERNAL COMMAND or CHILD BUILTIN: echo, pwd, env
        exec_cmd(sh, cmd, prompt);
        status = sh->exit_status;
    }
    return (status);
}
```

**Execution Decision Logic:**

```
Command Parsed
      ↓
Has pipes? ──YES──► handle_pipes() (Pipeline execution)
      ↓ NO
Is parent builtin? ──YES──► dispatch_builtin() (cd, export, unset, exit)
      ↓ NO
External command ──────────► exec_cmd() (fork + execve)
```

**Parent vs Child Built-ins:**
- **Parent**: `cd`, `export`, `unset`, `exit` (modify shell state)
- **Child**: `echo`, `pwd`, `env` (can run in forked process)

---

### Step 6A: Pipeline Execution - `handle_pipes()`
**File:** `src/pipe/pipe.c`

For commands like: `echo hello | cat | wc -l`

```c
int handle_pipes(t_minishell *sh, t_command *cmd, int cmd_count)
{
    t_pipe_data data;
    
    // 1. Setup pipes between commands
    if (!setup_pipes(&data, cmd_count))
        return (1);
    
    // 2. Fork and redirect each command
    for (int i = 0; i < cmd_count; i++)
    {
        fork_n_redirect_pipe(sh, &cmd[i], &data, i);
    }
    
    // 3. Close pipes in parent
    close_n_free_parent_pipes(&data);
    
    // 4. Wait for all children
    wait_pipe_child(&data, sh);
    
    return (sh->exit_status);
}
```

**Pipeline Process:**
1. Create `cmd_count - 1` pipes
2. Fork each command with proper stdin/stdout redirection
3. Close all pipe file descriptors in parent
4. Wait for all child processes to complete

---

### Step 6B: Built-in Execution - `dispatch_builtin()`
**File:** `src/built-in/dispatch_builtin.c`

```c
int dispatch_builtin(t_minishell *sh, t_command *cmd, char *prompt)
{
    // Route to appropriate built-in function
    if (ft_strcmp(cmd->args[0], "cd") == 0)
        bi_cd(sh, cmd);
    else if (ft_strcmp(cmd->args[0], "echo") == 0)
        bi_echo(sh, cmd);
    else if (ft_strcmp(cmd->args[0], "env") == 0)
        bi_env(sh, cmd);
    else if (ft_strcmp(cmd->args[0], "exit") == 0)
        bi_exit(sh, cmd, prompt, NULL);
    else if (ft_strcmp(cmd->args[0], "export") == 0)
        bi_export(sh, cmd);
    else if (ft_strcmp(cmd->args[0], "pwd") == 0)
        bi_pwd(sh);
    else if (ft_strcmp(cmd->args[0], "unset") == 0)
        bi_unset(sh, cmd);
    
    return (sh->exit_status);
}
```

**Built-in Command Files:**
- `src/built-in/bi_cd.c` - Change directory
- `src/built-in/bi_echo.c` - Echo text with -n option
- `src/built-in/bi_env.c` - Display environment variables
- `src/built-in/bi_exit.c` - Exit shell with status code
- `src/built-in/bi_export.c` - Set/display environment variables
- `src/built-in/bi_pwd.c` - Print working directory
- `src/built-in/bi_unset.c` - Remove environment variables

---

### Step 6C: External Command Execution - `exec_cmd()`
**File:** `src/commands.c:93`

```c
int exec_cmd(t_minishell *sh, t_command *cmd, char *prompt)
{
    int status;
    pid_t pid;

    (void)prompt;
    
    // 1. Handle pipeline if needed
    if (cmd->is_piped || sh->total_pipeln_cmd > 1)
        return (handle_pipes(sh, cmd, sh->total_pipeln_cmd));
    
    // 2. Fork child process
    pid = fork();
    if (pid == -1)
    {
        perror("minishell: fork failed!");
        sh->exit_status = 1;
        exit(1);
    }
    
    if (pid == 0)  // Child process
    {
        exec_child(sh, cmd);    // Execute command
        exit(127);              // Should not reach here
    }
    else  // Parent process
    {
        // 3. Wait for child completion
        waitpid(pid, &status, 0);
        
        // 4. Set exit status
        if (WIFEXITED(status))
            sh->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            sh->exit_status = 128 + WTERMSIG(status);
    }
    return (sh->exit_status);
}
```

**Child Process Execution (`exec_child()`):**
1. Apply redirections (>, <, >>, <<)
2. Find command in PATH using `set_path()`
3. Execute with `execve(full_path, args, envp)`

---

## 🔍 Key Data Structures

### `t_minishell` - Shell State
**File:** `includes/shell.h:19`

```c
typedef struct s_minishell
{
    char    **envp;             // Environment variables
    int     exit_status;        // Last command exit status
    int     total_pipeln_cmd;   // Number of commands in pipeline
    int     original_stdin;     // Backup of original stdin
    int     original_stdout;    // Backup of original stdout
} t_minishell;
```

### `t_command` - Command Structure
**File:** `includes/command.h:22`

```c
typedef struct s_command
{
    char        **args;              // Command arguments ["ls", "-la", NULL]
    int         redirections_count;  // Number of redirections
    int         is_piped;           // 1 if part of pipeline, 0 otherwise
    t_redirect  *redirects;         // Array of redirection structures
    t_pipe_data *pipe;              // Pipe data for pipeline execution
} t_command;
```

### `t_redirect` - Redirection Structure
**File:** `includes/minishell.h:43`

```c
typedef struct s_redirect
{
    t_redir_type    type;       // R_IN, R_OUT, APPEND, HEREDOC
    char            *filename;  // Target filename
} t_redirect;
```

---

## 📚 Essential Files to Study (Reading Order)

### 1. Core Flow
1. **`src/main.c`** - Entry point and main loop
2. **`src/utils/prompt_utils.c`** - Input processing and execution decisions
3. **`src/command/command.c`** - Command parsing logic

### 2. Execution Engines
4. **`src/commands.c`** - External command execution
5. **`src/built-in/dispatch_builtin.c`** - Built-in command routing
6. **`src/pipe/pipe.c`** - Pipeline execution

### 3. Supporting Systems
7. **`src/tokenization/lexer/lexer.c`** - Input tokenization
8. **`src/redirects/`** - Redirection handling
9. **`src/env_variables/`** - Environment variable management
10. **`src/path.c`** - PATH resolution

---

## 🚨 Critical Missing Features (for 42 compliance)

### 1. Signal Handling (Not Implemented)
- **SIGINT (Ctrl+C)**: Should interrupt current command
- **SIGQUIT (Ctrl+\\)**: Should quit current command
- **EOF (Ctrl+D)**: Partially implemented (exit status 111)

### 2. Quote Parsing (Not Implemented)
- **Single quotes**: Literal strings (`'hello world'`)
- **Double quotes**: Variable expansion (`"hello $USER"`)
- **Current limitation**: Cannot handle spaces in arguments

### 3. Enhanced Tokenization
- Current lexer is too simple (space-based splitting only)
- No escape sequence handling
- No proper quote parsing

---

## 🎯 Debugging Tips

### Trace Execution
1. Add debug prints in `run_shell_loop()` to see each iteration
2. Monitor `shell->exit_status` changes
3. Check `cmd->is_piped` to understand execution path

### Common Issues
1. **Memory leaks**: Check `free_matrix()` and `free_cmd_struct()` calls
2. **File descriptor leaks**: Ensure all pipes are closed
3. **Exit status**: Verify proper exit code propagation

### Testing Commands
```bash
# Single command
echo hello

# Pipeline
echo hello | cat

# Redirections
echo hello > file.txt
cat < file.txt

# Built-ins
cd /tmp
export TEST=value
env | grep TEST
```

---

*This documentation provides a complete understanding of the minishell execution flow. Start with `src/main.c` and follow the path described above to understand how your shell processes commands from input to execution.*