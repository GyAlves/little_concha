# Minishell Development Guide - Two-Person Team

## Current Project Status ✅

**Well-implemented foundation:**
- Core shell structure with proper data types (`t_minishell`, `t_command`)
- 5/7 built-in commands implemented: `echo`, `cd`, `pwd`, `env`, `exit`
- Basic command execution with fork/exec pattern
- Environment variable handling infrastructure
- Libft integration with essential string functions
- Path resolution system for external commands

**Missing critical components:**
- `export` and `unset` built-ins (2/7 missing)
- Complete parsing system (quotes, pipes, redirections)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Pipe execution between commands
- Input/Output redirection handling
- Variable expansion (`$VAR`, `$?`)
- Heredoc functionality (`<<`)

## Development Phases for Two-Person Team

### **Phase 1: Foundation Completion (Week 1-2)**

**Person A: Parsing & Tokenization**
- Create `src/parsing/tokenizer.c` - Complete command line tokenizer
- Handle single quotes (`'`) - no expansion inside
- Handle double quotes (`"`) - allow variable expansion inside
- Parse redirection operators (`<`, `>`, `>>`, `<<`)
- Parse pipe operators (`|`)
- Implement variable expansion (`$VAR`, `$?`)
- Create parsing data structures

**Person B: Missing Built-ins**
- Implement `src/built-in/bi_export.c`
  - Export variables to environment
  - Handle `export VAR=value` format
  - Display all exported variables when no args
- Implement `src/built-in/bi_unset.c`
  - Remove variables from environment
  - Handle multiple variable names
- Add environment variable removal functionality to `envar.c`
- Update `built_in.c` and `main_utils.c` dispatcher

### **Phase 2: Core Functionality (Week 3-4)**

**Person A: Redirection System**
- Create `src/execution/redirections.c`
- Implement input redirection (`< file`)
- Implement output redirection (`> file`)
- Implement append redirection (`>> file`)
- Implement heredoc (`<< delimiter`)
- Proper file descriptor management and cleanup

**Person B: Signal Handling**
- Create `src/signals/signal_handler.c`
- Implement Ctrl-C: display new prompt on new line
- Implement Ctrl-D: exit the shell cleanly
- Implement Ctrl-\: do nothing (ignore signal)
- Handle signals properly in parent and child processes
- Maintain signal handling during command execution

### **Phase 3: Advanced Features (Week 5-6)**

**Person A: Pipe Implementation**
- Create `src/execution/pipes.c`
- Implement multi-command pipeline execution
- Proper pipe creation and file descriptor handling
- Child process management for pipe chains
- Handle complex pipelines: `cmd1 | cmd2 | cmd3`

**Person B: Error Handling & Edge Cases**
- Comprehensive error management without shell crashes
- Memory leak prevention and proper cleanup
- Handle invalid commands gracefully
- Quote parsing edge cases
- Proper exit status propagation
- Handle empty commands and malformed input

### **Phase 4: Testing & Refinement (Week 7)**

**Both: Collaborative Testing**
- Test against bash behavior for compatibility
- Memory leak testing with `valgrind`
- Edge case validation and stress testing
- Performance optimization
- Code review and refactoring
- Documentation completion

## Technical Implementation Details

### Data Structure Extensions Needed

```c
// Add to t_command structure
typedef struct s_token
{
    char    *value;
    int     type;  // WORD, PIPE, REDIR_IN, REDIR_OUT, etc.
    struct s_token *next;
} t_token;

// Consider extending t_command for complex parsing
typedef struct s_command
{
    char    **args;
    char    *input_file;
    char    *output_file;
    char    *delimiter;    // for heredoc
    int     append;        // >> flag
    int     piped;         // | flag
    struct s_command *next; // for pipe chains
} t_command;
```

### Key Files to Create

**New files needed:**
- `src/parsing/tokenizer.c` - Command line tokenization
- `src/parsing/parser.c` - Parse tokens into command structures
- `src/parsing/expander.c` - Variable expansion logic
- `src/built-in/bi_export.c` - Export built-in implementation
- `src/built-in/bi_unset.c` - Unset built-in implementation
- `src/signals/signal_handler.c` - Signal management
- `src/execution/pipes.c` - Pipeline execution
- `src/execution/redirections.c` - I/O redirection handling

**Files to modify:**
- `src/built-in/built_in.c` - Add export/unset to is_builtin()
- `src/utils/main_utils.c` - Update dispatch_builtin()
- `minishell.h` - Add new function prototypes and structures
- `src/environment_variables/envar.c` - Add unset functionality

### Testing Strategy

1. **Unit Testing**: Test each component individually
2. **Integration Testing**: Test component interactions
3. **Bash Compatibility**: Compare outputs with bash
4. **Memory Testing**: Use valgrind to check leaks
5. **Edge Cases**: Test error conditions and malformed input

### Common Pitfalls to Avoid

- **Memory leaks**: Always free allocated memory
- **Signal handling**: Don't ignore signal safety
- **File descriptors**: Close all opened file descriptors
- **Process management**: Properly wait for child processes
- **Quote handling**: Respect bash quote semantics
- **Variable expansion**: Handle edge cases like `$` at end of string

## Priority Implementation Order

1. **High Priority**: export, unset built-ins
2. **High Priority**: Basic parsing (quotes, basic tokenization)
3. **Medium Priority**: Signal handling
4. **Medium Priority**: Redirections
5. **Medium Priority**: Variable expansion
6. **Low Priority**: Pipes (most complex)
7. **Low Priority**: Advanced edge cases

Your project has an excellent foundation with proper architecture. Focus on systematic implementation of missing components while maintaining code quality and bash compatibility!