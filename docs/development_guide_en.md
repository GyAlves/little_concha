# Minishell Offline Development Guide - Complete Step-by-Step

## 🚀 Quick Start for Offline Development

### Prerequisites Check
```bash
# Verify you have these tools installed:
cc --version          # GCC compiler
make --version        # Build system
valgrind --version    # Memory debugging (optional but recommended)
```

### Project Structure Overview
```
little_concha/
├── Makefile           # Main build configuration
├── minishell          # Executable (after build)
├── Libft/             # Custom C library
│   ├── Makefile
│   ├── libft.h
│   └── libft/*.c      # String/memory functions
├── includes/          # Header files
│   ├── minishell.h    # Main header
│   ├── shell.h        # Shell structures
│   ├── command.h      # Command structures
│   ├── built-in.h     # Built-in functions
│   ├── utils.h        # Utility functions
│   └── path.h         # Path handling
├── src/               # Source code
│   ├── main.c         # Entry point
│   ├── built-in/      # Built-in commands
│   ├── command/       # Command execution
│   ├── environment_variables/ # Environment handling
│   ├── path/          # Path resolution
│   └── utils/         # Utility functions
└── docs/              # Documentation
```

## 📋 Current Implementation Status

**✅ Completed Components:**
- Core shell loop with readline integration
- Data structures (`t_minishell`, `t_command`)
- 5/7 built-in commands: `echo`, `cd`, `pwd`, `env`, `exit`
- Basic command execution with fork/exec
- Environment variable handling
- Path resolution for external commands
- Libft integration

**❌ Missing Critical Components:**
- `export` and `unset` built-ins
- Complete parsing system (quotes, pipes, redirections)
- Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)
- Pipe execution between commands
- Input/Output redirection handling
- Variable expansion (`$VAR`, `$?`)
- Heredoc functionality (`<<`)

## 🛠️ Daily Development Workflow (Offline)

### Essential Build Commands
```bash
# Clean build everything
make fclean && make

# Quick rebuild after changes
make

# Test for memory leaks
valgrind --leak-check=full ./minishell

# Debug with GDB
gdb ./minishell
```

### Git Workflow for Offline Development
```bash
# Before starting work
git status
git add .
git commit -m "checkpoint: save current progress"

# Create feature branch
git checkout -b feature/export-builtin

# Regular commits while working
git add specific_file.c
git commit -m "implement: basic export functionality"

# When feature complete
git checkout dev
git merge feature/export-builtin
```

## 📅 Step-by-Step Development Plan

### **Week 1: Foundation Setup & Missing Built-ins**

#### Day 1: Environment Setup & Code Review
```bash
# 1. Build and test current state
make fclean && make
./minishell

# 2. Test existing built-ins
echo "hello world"
pwd
cd /tmp
env
exit
```

**Study these files:**
- `src/built-in/built_in.c` - Built-in dispatcher
- `src/built-in/bi_*.c` - Existing built-in implementations
- `src/environment_variables/envar.c` - Environment handling

#### Day 2-3: Implement `export` Built-in
**File to create:** `src/built-in/bi_export.c`

##### Step 2.1: Create the basic file structure (30 min)
```bash
# Create the file
touch src/built-in/bi_export.c

# Add the basic template
cat > src/built-in/bi_export.c << 'EOF'
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [your_name] <[your_email]>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [date] by [your_name]                   #+#    #+#             */
/*   Updated: [date] by [your_name]                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_export(t_minishell *shell, char **args)
{
	if (!args[1])
		return (display_exported_vars(shell->envp));
	return (export_variables(shell, args + 1));
}
EOF
```

##### Step 2.2: Implement display function (45 min)
```c
// Add this function to bi_export.c
static int	display_exported_vars(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
	return (0);
}
```

**Test this step:**
```bash
# Compile to check syntax
make
# Test display functionality
echo "export" | ./minishell
```

##### Step 2.3: Parse variable format (60 min)
```c
// Add helper function to validate and parse VAR=value format
static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]))
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static char	*extract_var_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	name = ft_substr(arg, 0, i);
	return (name);
}

static char	*extract_var_value(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		return (ft_strdup(arg + i + 1));
	return (NULL);
}
```

**Test parsing:**
```bash
# Test with various formats
echo "export TEST=hello" | ./minishell
echo "export INVALID-VAR=test" | ./minishell  # Should fail
echo "export 123VAR=test" | ./minishell       # Should fail
```

##### Step 2.4: Implement environment variable addition (90 min)
```c
// Add to src/environment_variables/envar.c
char	**add_or_update_env_var(char **envp, char *var_name, char *var_value)
{
	char	**new_envp;
	char	*new_var;
	int		env_size;
	int		var_index;

	// Create new variable string "VAR=value"
	new_var = create_env_string(var_name, var_value);
	if (!new_var)
		return (NULL);
	
	// Check if variable already exists
	var_index = find_env_var_index(envp, var_name);
	env_size = count_env_vars(envp);
	
	if (var_index >= 0)
	{
		// Update existing variable
		free(envp[var_index]);
		envp[var_index] = new_var;
		return (envp);
	}
	else
	{
		// Add new variable
		new_envp = resize_env_array(envp, env_size + 1);
		if (!new_envp)
		{
			free(new_var);
			return (NULL);
		}
		new_envp[env_size] = new_var;
		new_envp[env_size + 1] = NULL;
		return (new_envp);
	}
}

// Helper functions you need to implement
static char	*create_env_string(char *name, char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

static int	find_env_var_index(char **envp, char *var_name)
{
	int		i;
	int		name_len;

	name_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, name_len) == 0 
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static char	**resize_env_array(char **old_envp, int new_size)
{
	char	**new_envp;
	int		i;

	new_envp = malloc(sizeof(char *) * (new_size + 1));
	if (!new_envp)
		return (NULL);
	
	i = 0;
	while (old_envp[i])
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	new_envp[new_size] = NULL;
	free(old_envp);  // Free the old array (not the strings)
	return (new_envp);
}
```

##### Step 2.5: Complete the export_variables function (45 min)
```c
// Complete implementation in bi_export.c
static int	export_variables(t_minishell *shell, char **vars)
{
	int		i;
	char	*var_name;
	char	*var_value;

	i = 0;
	while (vars[i])
	{
		if (!is_valid_identifier(vars[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", vars[i]);
			return (1);
		}
		
		if (ft_strchr(vars[i], '='))
		{
			var_name = extract_var_name(vars[i]);
			var_value = extract_var_value(vars[i]);
			
			shell->envp = add_or_update_env_var(shell->envp, var_name, var_value);
			
			free(var_name);
			free(var_value);
			
			if (!shell->envp)
			{
				printf("minishell: export: memory allocation failed\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}
```

##### Step 2.6: Update built-in dispatcher (30 min)
```c
// In src/built-in/built_in.c, add to is_builtin function:
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)  // ADD THIS LINE
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

// Add to dispatch_builtin function:
int	dispatch_builtin(t_minishell *shell, t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (bi_echo(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (bi_cd(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (bi_pwd(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)  // ADD THIS LINE
		return (bi_export(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (bi_env(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (bi_exit(shell, cmd->args));
	return (-1);
}
```

##### Step 2.7: Update header file (15 min)
```c
// In includes/built-in.h, add:
int	bi_export(t_minishell *shell, char **args);

// In includes/utils.h or minishell.h, add:
char	**add_or_update_env_var(char **envp, char *var_name, char *var_value);
```

##### Step 2.8: Test thoroughly (45 min)
```bash
# Build and test
make

# Basic tests
echo "export" | ./minishell                    # Should show all variables
echo "export TEST=hello" | ./minishell        # Should add variable
echo "env | grep TEST" | ./minishell          # Should show TEST=hello
echo "export TEST=world" | ./minishell        # Should update variable
echo "env | grep TEST" | ./minishell          # Should show TEST=world

# Error cases
echo "export 123=invalid" | ./minishell       # Should show error
echo "export INVALID-VAR=test" | ./minishell  # Should show error

# Multiple variables
echo "export VAR1=val1 VAR2=val2" | ./minishell
echo "env | grep VAR" | ./minishell
```

**Expected time for Day 2-3: ~5.5 hours**
- File creation and structure: 30 min
- Display function: 45 min  
- Variable parsing: 60 min
- Environment management: 90 min
- Export function completion: 45 min
- Dispatcher updates: 30 min
- Header updates: 15 min
- Testing: 45 min

#### Day 4-5: Implement `unset` Built-in
**File to create:** `src/built-in/bi_unset.c`

##### Step 4.1: Create basic unset file structure (20 min)
```bash
# Create the file
touch src/built-in/bi_unset.c

# Add basic template
cat > src/built-in/bi_unset.c << 'EOF'
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [your_name] <[your_email]>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [date] by [your_name]                   #+#    #+#             */
/*   Updated: [date] by [your_name]                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_unset(t_minishell *shell, char **args)
{
	int	i;

	if (!args[1])
		return (0);  // No arguments - do nothing (bash behavior)
	
	i = 1;
	while (args[i])
	{
		if (is_valid_unset_identifier(args[i]))
			shell->envp = remove_env_var(shell->envp, args[i]);
		else
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			return (1);
		}
		i++;
	}
	return (0);
}
EOF
```

##### Step 4.2: Implement identifier validation (30 min)
```c
// Add to bi_unset.c
static int	is_valid_unset_identifier(char *str)
{
	int	i;

	if (!str || !str[0] || ft_isdigit(str[0]))
		return (0);
	
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
```

**Test validation:**
```bash
# Test cases
echo "unset VALID_VAR" | ./minishell     # Should work
echo "unset 123VAR" | ./minishell       # Should fail
echo "unset INVALID-VAR" | ./minishell  # Should fail  
echo "unset VAR@NAME" | ./minishell     # Should fail
```

##### Step 4.3: Implement remove_env_var function (75 min)
```c
// Add to src/environment_variables/envar.c
char	**remove_env_var(char **envp, char *var_name)
{
	int		var_index;
	int		env_size;
	char	**new_envp;

	var_index = find_env_var_index(envp, var_name);
	if (var_index == -1)
		return (envp);  // Variable not found - nothing to remove
	
	env_size = count_env_vars(envp);
	
	// Free the variable string
	free(envp[var_index]);
	
	// Shift remaining variables down
	shift_env_vars_down(envp, var_index, env_size);
	
	// Resize array to be smaller
	new_envp = resize_env_array_down(envp, env_size - 1);
	if (!new_envp)
		return (envp);  // On failure, return original (already modified)
	
	return (new_envp);
}

// Helper function to shift array elements
static void	shift_env_vars_down(char **envp, int removed_index, int env_size)
{
	int	i;

	i = removed_index;
	while (i < env_size - 1)
	{
		envp[i] = envp[i + 1];
		i++;
	}
	envp[env_size - 1] = NULL;
}

// Helper function to resize array smaller
static char	**resize_env_array_down(char **old_envp, int new_size)
{
	char	**new_envp;
	int		i;

	if (new_size == 0)
	{
		new_envp = malloc(sizeof(char *));
		if (!new_envp)
			return (NULL);
		new_envp[0] = NULL;
		free(old_envp);
		return (new_envp);
	}

	new_envp = malloc(sizeof(char *) * (new_size + 1));
	if (!new_envp)
		return (NULL);
	
	i = 0;
	while (i < new_size)
	{
		new_envp[i] = old_envp[i];
		i++;
	}
	new_envp[new_size] = NULL;
	
	free(old_envp);
	return (new_envp);
}
```

##### Step 4.4: Test remove functionality (30 min)
```bash
# Build and test step by step
make

# Create test variable
echo "export TEST_UNSET=hello" | ./minishell
echo "env | grep TEST_UNSET" | ./minishell  # Should show TEST_UNSET=hello

# Remove the variable
echo "unset TEST_UNSET" | ./minishell
echo "env | grep TEST_UNSET" | ./minishell  # Should show nothing

# Test multiple variables
echo "export VAR1=val1 VAR2=val2 VAR3=val3" | ./minishell
echo "env | grep VAR" | ./minishell         # Should show all 3
echo "unset VAR1 VAR3" | ./minishell        # Remove VAR1 and VAR3
echo "env | grep VAR" | ./minishell         # Should show only VAR2
```

##### Step 4.5: Handle edge cases (45 min)
```c
// Add to bi_unset.c - enhanced version
int	bi_unset(t_minishell *shell, char **args)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_unset_identifier(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			exit_status = 1;  // Set error but continue processing
		}
		else
		{
			shell->envp = remove_env_var(shell->envp, args[i]);
			if (!shell->envp)
			{
				printf("minishell: unset: memory allocation failed\n");
				return (1);
			}
		}
		i++;
	}
	return (exit_status);
}
```

**Test edge cases:**
```bash
# Test with non-existent variables
echo "unset NONEXISTENT" | ./minishell     # Should work silently

# Test with mixed valid/invalid identifiers
echo "unset VALID 123INVALID VALID2" | ./minishell  # Should show error for 123INVALID

# Test unsetting critical variables
echo "unset PATH" | ./minishell            # Should work but may break external commands
echo "unset HOME" | ./minishell            # Should work

# Test unsetting empty environment
echo "env | wc -l" | ./minishell           # Count variables
echo "unset \$(env | cut -d= -f1)" | ./minishell  # Remove all (advanced test)
```

##### Step 4.6: Update dispatcher and headers (25 min)
```c
// In src/built-in/built_in.c, add to is_builtin:
int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)  // ADD THIS LINE
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

// Add to dispatch_builtin:
int	dispatch_builtin(t_minishell *shell, t_command *cmd)
{
	if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		return (bi_echo(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		return (bi_cd(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		return (bi_pwd(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		return (bi_export(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "unset", 6) == 0)  // ADD THIS LINE
		return (bi_unset(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		return (bi_env(shell, cmd->args));
	if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		return (bi_exit(shell, cmd->args));
	return (-1);
}
```

```c
// In includes/built-in.h, add:
int		bi_unset(t_minishell *shell, char **args);

// In includes/utils.h or appropriate header:
char	**remove_env_var(char **envp, char *var_name);
```

##### Step 4.7: Integration testing (35 min)
```bash
# Build everything
make fclean && make

# Integration test: export and unset together
echo "export TEST1=value1 TEST2=value2" | ./minishell
echo "env | grep TEST" | ./minishell
echo "unset TEST1" | ./minishell  
echo "env | grep TEST" | ./minishell    # Should show only TEST2
echo "export TEST1=newvalue" | ./minishell
echo "env | grep TEST" | ./minishell    # Should show TEST1=newvalue and TEST2=value2
echo "unset TEST1 TEST2" | ./minishell
echo "env | grep TEST" | ./minishell    # Should show nothing

# Memory leak test
valgrind --leak-check=full ./minishell
# Then in minishell:
# export TEST=value
# unset TEST
# exit
```

**Expected time for Day 4-5: ~4.5 hours**
- File structure: 20 min
- Identifier validation: 30 min
- Remove function implementation: 75 min
- Testing remove functionality: 30 min
- Edge case handling: 45 min
- Dispatcher/header updates: 25 min
- Integration testing: 35 min

##### Step 4.8: Final built-ins verification (20 min)
```bash
# Complete built-in test suite
echo "=== Testing all built-ins ==="

# Test echo
echo "echo hello world" | ./minishell

# Test pwd
echo "pwd" | ./minishell

# Test cd
echo "cd /tmp && pwd" | ./minishell
echo "cd && pwd" | ./minishell

# Test export
echo "export TEST=hello" | ./minishell
echo "export" | ./minishell | head -5

# Test unset  
echo "unset TEST" | ./minishell

# Test env
echo "env" | ./minishell | head -5

# Test exit
echo "exit 42" | ./minishell
echo "echo \$?" | bash  # Should show 42

echo "=== All built-ins complete! ==="
```

### **Week 2: Basic Parsing System**

#### Day 6-7: Tokenizer Foundation
**Directory to create:** `src/parsing/`
**File to create:** `src/parsing/tokenizer.c`

##### Step 6.1: Create parsing directory and tokenizer structure (45 min)
```bash
# Create parsing directory
mkdir -p src/parsing

# Create tokenizer header definitions
cat >> includes/minishell.h << 'EOF'

// Token types for parsing
typedef enum e_token_type
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIR_IN,      // <
    TOKEN_REDIR_OUT,     // >
    TOKEN_REDIR_APPEND,  // >>
    TOKEN_HEREDOC        // <<
} t_token_type;

typedef struct s_token
{
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

// Function prototypes
t_token *tokenize_input(char *input);
void    free_tokens(t_token *tokens);
void    print_tokens(t_token *tokens);  // For debugging

EOF
```

##### Step 6.2: Create basic tokenizer file structure (30 min)
```bash
# Create the tokenizer file
cat > src/parsing/tokenizer.c << 'EOF'
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: [your_name] <[your_email]>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: [date] by [your_name]                   #+#    #+#             */
/*   Updated: [date] by [your_name]                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize_input(char *input)
{
	t_token	*tokens;
	int		i;

	if (!input || !*input)
		return (NULL);
	
	tokens = NULL;
	i = 0;
	
	while (input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break;
		
		if (is_operator(input, i))
			handle_operator(&tokens, input, &i);
		else
			handle_word(&tokens, input, &i);
	}
	
	return (tokens);
}
EOF
```

##### Step 6.3: Implement helper functions (60 min)
```c
// Add these functions to tokenizer.c

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && (input[*i] == ' ' || input[*i] == '\t'))
		(*i)++;
}

static int	is_operator(char *input, int i)
{
	if (input[i] == '|')
		return (1);
	if (input[i] == '<')
		return (1);
	if (input[i] == '>')
		return (1);
	return (0);
}

static void	handle_operator(t_token **tokens, char *input, int *i)
{
	t_token_type	type;
	char			*value;

	if (input[*i] == '|')
	{
		type = TOKEN_PIPE;
		value = ft_strdup("|");
		(*i)++;
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			type = TOKEN_HEREDOC;
			value = ft_strdup("<<");
			(*i) += 2;
		}
		else
		{
			type = TOKEN_REDIR_IN;
			value = ft_strdup("<");
			(*i)++;
		}
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			type = TOKEN_REDIR_APPEND;
			value = ft_strdup(">>");
			(*i) += 2;
		}
		else
		{
			type = TOKEN_REDIR_OUT;
			value = ft_strdup(">");
			(*i)++;
		}
	}
	else
		return;
	
	add_token(tokens, create_token(value, type));
}

static void	handle_word(t_token **tokens, char *input, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	
	// Simple word extraction (no quotes yet)
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input, *i))
		(*i)++;
	
	len = *i - start;
	word = ft_substr(input, start, len);
	
	add_token(tokens, create_token(word, TOKEN_WORD));
}
```

##### Step 6.4: Implement token management functions (45 min)
```c
// Add to tokenizer.c

static t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(value);
		return (NULL);
	}
	
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	
	return (new_token);
}

static void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return;
	
	if (!*tokens)
	{
		*tokens = new_token;
		return;
	}
	
	current = *tokens;
	while (current->next)
		current = current->next;
	
	current->next = new_token;
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	char	*type_names[] = {"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "REDIR_APPEND", "HEREDOC"};

	current = tokens;
	printf("=== TOKENS ===\n");
	while (current)
	{
		printf("Type: %s, Value: '%s'\n", type_names[current->type], current->value);
		current = current->next;
	}
	printf("=== END TOKENS ===\n");
}
```

##### Step 6.5: Create simple test program (30 min)
```bash
# Create a simple test for tokenizer
cat > test_tokenizer.c << 'EOF'
#include "minishell.h"

int main(int argc, char **argv)
{
    t_token *tokens;
    
    if (argc != 2)
    {
        printf("Usage: %s \"command line\"\n", argv[0]);
        return (1);
    }
    
    tokens = tokenize_input(argv[1]);
    print_tokens(tokens);
    free_tokens(tokens);
    
    return (0);
}
EOF

# Compile test
cc -Wall -Wextra -Werror -Iincludes test_tokenizer.c src/parsing/tokenizer.c Libft/libft.a -o test_tokenizer

# Test basic tokenization
./test_tokenizer "ls -la"
./test_tokenizer "cat file.txt | grep hello"
./test_tokenizer "echo hello > output.txt"
./test_tokenizer "cat < input.txt >> output.txt"
```

**Expected output examples:**
```
$ ./test_tokenizer "ls -la"
=== TOKENS ===
Type: WORD, Value: 'ls'
Type: WORD, Value: '-la'
=== END TOKENS ===

$ ./test_tokenizer "cat file.txt | grep hello"
=== TOKENS ===
Type: WORD, Value: 'cat'
Type: WORD, Value: 'file.txt'
Type: PIPE, Value: '|'
Type: WORD, Value: 'grep'
Type: WORD, Value: 'hello'
=== END TOKENS ===
```

##### Step 6.6: Integrate tokenizer with main shell (40 min)
```c
// Modify src/main.c to use tokenizer (optional for now)
// Add a simple parsing test mode

#include "minishell.h"

// Add this function to test tokenizer integration
void	test_tokenizer_mode(char *input)
{
	t_token	*tokens;

	printf("Input: %s\n", input);
	tokens = tokenize_input(input);
	print_tokens(tokens);
	free_tokens(tokens);
}

// In main function, add debugging mode
int	main(int argc, char **argv, char **envp)
{
	// ... existing code ...
	
	// Add tokenizer test mode
	if (argc == 3 && ft_strncmp(argv[1], "--test-tokenizer", 16) == 0)
	{
		test_tokenizer_mode(argv[2]);
		return (0);
	}
	
	// ... rest of existing main function ...
}
```

**Test integration:**
```bash
# Build with tokenizer
make

# Test tokenizer mode
./minishell --test-tokenizer "echo hello | cat"
./minishell --test-tokenizer "ls > file.txt"
```

##### Step 6.7: Handle tokenizer edge cases (50 min)
```c
// Enhance handle_word function to handle edge cases
static void	handle_word(t_token **tokens, char *input, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	
	// Handle empty words
	if (is_operator(input, *i) || ft_isspace(input[*i]))
		return;
	
	// Extract word until whitespace or operator
	while (input[*i] && !ft_isspace(input[*i]) && !is_operator(input, *i))
	{
		// Skip quoted sections for now (basic handling)
		if (input[*i] == '\'' || input[*i] == '"')
		{
			char quote = input[*i];
			(*i)++;  // Skip opening quote
			while (input[*i] && input[*i] != quote)
				(*i)++;
			if (input[*i] == quote)
				(*i)++;  // Skip closing quote
		}
		else
			(*i)++;
	}
	
	len = *i - start;
	if (len == 0)
		return;
	
	word = ft_substr(input, start, len);
	if (!word)
		return;
	
	add_token(tokens, create_token(word, TOKEN_WORD));
}
```

**Test edge cases:**
```bash
# Test with quotes
./test_tokenizer "echo 'hello world'"
./test_tokenizer "echo \"hello world\""

# Test with multiple operators
./test_tokenizer "cat < file1.txt > file2.txt"
./test_tokenizer "echo hello >> log.txt"

# Test with complex command
./test_tokenizer "cat file.txt | grep pattern >> result.txt"
```

**Expected time for Day 6-7: ~5 hours**
- Directory and structure setup: 45 min
- Basic file creation: 30 min
- Helper functions: 60 min
- Token management: 45 min
- Test program: 30 min
- Integration: 40 min
- Edge cases: 50 min

##### Step 6.8: Tokenizer debugging and validation (30 min)
```bash
# Create comprehensive test suite
cat > tokenizer_tests.sh << 'EOF'
#!/bin/bash

echo "=== Tokenizer Test Suite ==="

# Basic commands
echo "Test 1: Basic command"
./test_tokenizer "ls"

echo -e "\nTest 2: Command with arguments"  
./test_tokenizer "ls -la /tmp"

echo -e "\nTest 3: Pipe commands"
./test_tokenizer "cat file.txt | grep hello"

echo -e "\nTest 4: Input redirection"
./test_tokenizer "cat < input.txt"

echo -e "\nTest 5: Output redirection"
./test_tokenizer "echo hello > output.txt"

echo -e "\nTest 6: Append redirection"
./test_tokenizer "echo world >> output.txt"

echo -e "\nTest 7: Heredoc"
./test_tokenizer "cat << EOF"

echo -e "\nTest 8: Complex command"
./test_tokenizer "cat file1.txt | grep pattern > result.txt"

echo -e "\nTest 9: Multiple pipes"
./test_tokenizer "cat file.txt | grep hello | wc -l"

echo -e "\nTest 10: Quoted strings"
./test_tokenizer "echo 'hello world' | cat"

echo "=== Tests Complete ==="
EOF

chmod +x tokenizer_tests.sh
./tokenizer_tests.sh
```

#### Day 8-9: Quote Handling
**Focus areas:**
- Single quotes: No expansion, preserve literal content
- Double quotes: Allow variable expansion
- Escape sequences in double quotes
- Nested quote handling

#### Day 10: Variable Expansion Basics
**File to create:** `src/parsing/expander.c`
- Handle `$VAR` and `${VAR}` syntax
- Implement `$?` for exit status
- Handle edge cases (empty variables, undefined variables)

### **Week 3: Signal Handling & Redirection**

#### Day 11-12: Signal System
**File to create:** `src/signals/signal_handler.c`

```c
#include "minishell.h"

void setup_signals(void)
{
    signal(SIGINT, handle_sigint);    // Ctrl-C
    signal(SIGQUIT, handle_sigquit);  // Ctrl-\ (ignore)
}

void handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
```

#### Day 13-15: Input/Output Redirection
**File to create:** `src/execution/redirections.c`

**Implementation order:**
1. Input redirection (`< file`)
2. Output redirection (`> file`)
3. Append redirection (`>> file`)
4. Heredoc (`<< delimiter`)

### **Week 4: Pipes & Advanced Features**

#### Day 16-18: Pipe Implementation
**File to create:** `src/execution/pipes.c`

**Key concepts:**
- Create pipe file descriptors
- Fork processes for each command
- Connect stdout of process N to stdin of process N+1
- Wait for all processes to complete

#### Day 19-21: Error Handling & Edge Cases
**Focus areas:**
- Memory leak prevention
- Invalid command handling
- Malformed input recovery
- Signal safety in child processes

## 🧪 Testing Strategy (Offline Development)

### Unit Testing Approach
Create simple test scripts for each component:

```bash
# test_export.sh
#!/bin/bash
echo "Testing export built-in..."
echo "export TEST_VAR=hello" | ./minishell
echo "env | grep TEST_VAR" | ./minishell
```

### Manual Testing Checklist
```bash
# Built-ins test
echo "Test 1: Built-ins"
pwd; cd /tmp; pwd; cd -
echo hello world
env | head -5
export TEST=value
unset TEST

# Parsing test  
echo "Test 2: Parsing"
echo 'single quotes preserve $USER'
echo "double quotes expand $USER"
echo $USER

# Redirection test
echo "Test 3: Redirection"
echo hello > test.txt
cat < test.txt
echo world >> test.txt
cat test.txt

# Pipe test
echo "Test 4: Pipes"
ls | grep minishell
cat /etc/passwd | head -3 | tail -1
```

### Memory Testing
```bash
# Check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./minishell

# Stress test
for i in {1..100}; do echo "echo test $i"; done | ./minishell
```

## 🔧 Technical Implementation Details

### Current Data Structures (Study These!)
```c
// From includes/shell.h
typedef struct s_minishell
{
    char    **envp;        // Environment variables
    int     exit_status;   // Last command exit status
} t_minishell;

// From includes/command.h  
typedef struct s_command
{
    char    **args;        // Command arguments
    // TODO: Add redirection fields
    // TODO: Add pipe support
} t_command;
```

### Data Structure Extensions Needed
```c
// Add to includes/command.h
typedef struct s_token
{
    char            *value;
    int             type;    // WORD, PIPE, REDIR_IN, etc.
    struct s_token  *next;
} t_token;

// Enhanced t_command structure
typedef struct s_command
{
    char    **args;
    char    *input_file;    // < file
    char    *output_file;   // > file
    char    *heredoc_delim; // << delimiter
    int     append_mode;    // >> flag
    int     is_piped;       // | flag
    struct s_command *next; // for pipe chains
} t_command;
```

### Function Templates for New Files

#### `src/built-in/bi_export.c`
```c
#include "minishell.h"

int bi_export(t_minishell *shell, char **args)
{
    if (!args[1])
        return (print_export_vars(shell->envp));
    return (add_env_vars(shell, args + 1));
}

static int print_export_vars(char **envp)
{
    int i = 0;
    while (envp[i])
    {
        printf("declare -x %s\n", envp[i]);
        i++;
    }
    return (0);
}

static int add_env_vars(t_minishell *shell, char **vars)
{
    int i = 0;
    while (vars[i])
    {
        if (ft_strchr(vars[i], '='))
            update_env_var(&shell->envp, vars[i]);
        i++;
    }
    return (0);
}
```

#### `src/parsing/tokenizer.c`
```c
#include "minishell.h"

t_token *tokenize_input(char *input)
{
    t_token *tokens = NULL;
    t_token *current = NULL;
    char *word;
    int i = 0;
    
    while (input[i])
    {
        skip_whitespace(input, &i);
        if (is_operator(input[i]))
            add_operator_token(&tokens, &current, input, &i);
        else if (input[i])
        {
            word = extract_word(input, &i);
            add_word_token(&tokens, &current, word);
        }
    }
    return (tokens);
}
```

#### `src/signals/signal_handler.c`
```c
#include "minishell.h"

void setup_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa_int, NULL);

    sa_quit.sa_handler = SIG_IGN;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);
}

void handle_sigint(int sig)
{
    (void)sig;
    g_signal_received = SIGINT;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
```

### Files You Need to Create
**Priority 1 (Week 1):**
- [ ] `src/built-in/bi_export.c`
- [ ] `src/built-in/bi_unset.c`

**Priority 2 (Week 2):**  
- [ ] `src/parsing/tokenizer.c`
- [ ] `src/parsing/expander.c`

**Priority 3 (Week 3):**
- [ ] `src/signals/signal_handler.c`
- [ ] `src/execution/redirections.c`

**Priority 4 (Week 4):**
- [ ] `src/execution/pipes.c`

### Files You Need to Modify
- [ ] `src/built-in/built_in.c` - Add export/unset support
- [ ] `src/environment_variables/envar.c` - Add unset functionality  
- [ ] `includes/built-in.h` - Add new function prototypes
- [ ] `includes/minishell.h` - Add global signal variable
- [ ] `src/main.c` - Add signal setup call

### Debugging Commands for Offline Development
```bash
# Check current symbols in executable
nm ./minishell | grep bi_

# Check which functions are undefined
nm -u ./minishell

# Simple debugging without GDB
cc -g -DDEBUG -Wall -Wextra -Werror -Iincludes src/*.c Libft/libft.a -lreadline -o minishell_debug

# Add debug prints in code:
#ifdef DEBUG
    printf("DEBUG: entered function %s\n", __func__);
#endif
```

### Bash Compatibility Testing
```bash
# Create comparison script
#!/bin/bash
echo "=== Testing: $1 ==="
echo "BASH:"
bash -c "$1"
echo "Exit: $?"
echo "MINISHELL:"  
echo "$1" | ./minishell
echo "==="
```

### Memory Management Rules
1. **Every malloc needs a free**
2. **Free in reverse order of allocation**
3. **Set pointers to NULL after freeing**
4. **Check return values of malloc/calloc**
5. **Use valgrind before each commit**

### Performance Tips for Large Codebases
```bash
# Use ccache for faster compilation
export CC="ccache cc"

# Parallel make (use number of CPU cores)
make -j4

# Only rebuild changed files
make

# Quick syntax check without linking
cc -fsyntax-only -Iincludes src/new_file.c
```

## 🎯 Daily Progress Tracking

Create a simple progress file: `PROGRESS.md`
```markdown
## Week 1 Progress
- [x] Day 1: Environment setup ✅
- [x] Day 2: bi_export.c structure ✅  
- [ ] Day 3: bi_export.c complete
- [ ] Day 4: bi_unset.c structure
- [ ] Day 5: bi_unset.c complete

## Current Blockers
- None

## Next Session Goals  
- Complete export variable parsing
- Test export with simple cases
```

## 🚨 Common Offline Development Issues

### Issue: "readline not found"
```bash
# On macOS with Homebrew
brew install readline
export LDFLAGS="-L/opt/homebrew/opt/readline/lib"
export CPPFLAGS="-I/opt/homebrew/opt/readline/include"

# On Linux (Ubuntu/Debian)
sudo apt-get install libreadline-dev
```

### Issue: "Segmentation fault"
```bash
# Quick debug without GDB
cc -g -fsanitize=address -Iincludes src/*.c Libft/libft.a -lreadline -o minishell_debug

# Run with better error info
./minishell_debug
```

### Issue: Memory leaks
```bash
# Check specific function
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./minishell

# Suppress known readline leaks
valgrind --suppressions=readline.supp ./minishell
```

## 🏁 Final Project Checklist

**Mandatory Features:**
- [ ] All 7 built-ins: echo, cd, pwd, export, unset, env, exit
- [ ] Command execution with PATH resolution
- [ ] Quote handling (' and ")
- [ ] Redirections (<, >, >>)
- [ ] Pipes (|)
- [ ] Environment variables ($VAR)
- [ ] Exit status ($?)
- [ ] Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)

**Code Quality:**
- [ ] No memory leaks (valgrind clean)
- [ ] No global variables (except signal handling)
- [ ] Proper error handling
- [ ] Clean compilation (no warnings)
- [ ] Follows 42 coding standard

**Testing:**
- [ ] Bash compatibility verified
- [ ] Edge cases handled
- [ ] Stress testing passed
- [ ] Manual testing complete

This guide should give you everything needed for productive offline development. Focus on one component at a time, test frequently, and commit your progress regularly!