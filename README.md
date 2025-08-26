# 🐚 little_concha

A comprehensive **minishell** implementation developed as part of the 42 School curriculum. Little_concha is a simple yet functional shell that replicates many features of traditional Unix shells like bash.

## 📋 Table of Contents

- [Features](#-features)
- [Prerequisites](#-prerequisites)
- [Installation](#-installation)
- [Usage](#-usage)
- [Built-in Commands](#-built-in-commands)
- [Project Structure](#-project-structure)
- [Examples](#-examples)
- [Technical Details](#-technical-details)
- [Authors](#-authors)
- [License](#-license)

## ✨ Features

### Core Shell Functionality
- **Interactive command line interface** with custom prompt (`shell>>`)
- **Command execution** with PATH resolution
- **Process management** with proper fork/wait implementation
- **Exit status handling** and propagation

### Input/Output Management
- **Pipes** (`|`) - Connect multiple commands
- **Input redirection** (`<`) - Redirect input from files
- **Output redirection** (`>`) - Redirect output to files
- **Append redirection** (`>>`) - Append output to files
- **Heredoc** (`<<`) - Multi-line input with delimiter

### Environment & Variables
- **Environment variable expansion** (`$VAR`, `$?`)
- **Environment variable management** (export, unset)
- **Exit status tracking** (`$?`)

### Advanced Features
- **Signal handling** (Ctrl+C, Ctrl+\\, Ctrl+D)
- **Command history** with readline integration
- **Memory management** with comprehensive cleanup
- **Error handling** with proper exit codes

## 📦 Prerequisites

- **GCC** or compatible C compiler
- **Make** build system
- **readline library** development headers
- **Unix-like operating system** (Linux, macOS)

### Installing Prerequisites

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential libreadline-dev
```

**macOS:**
```bash
# Using Homebrew
brew install readline
```

## 🚀 Installation

1. **Clone the repository:**
```bash
git clone https://github.com/GyAlves/little_concha.git
cd little_concha
```

2. **Build the project:**
```bash
make
```

3. **Run the minishell:**
```bash
./minishell
```

## 💡 Usage

### Basic Usage
```bash
./minishell
shell>> echo "Hello, World!"
Hello, World!
shell>> pwd
/path/to/current/directory
shell>> exit
```

### Memory Testing
```bash
# Run with Valgrind for memory leak detection
make v

# Monitor file descriptors
make fd
```

## 🛠 Built-in Commands

| Command | Description | Example |
|---------|-------------|---------|
| `echo` | Display text with optional `-n` flag | `echo "Hello World"` |
| `cd` | Change directory | `cd /path/to/directory` |
| `pwd` | Print working directory | `pwd` |
| `export` | Set environment variables | `export VAR=value` |
| `unset` | Remove environment variables | `unset VAR` |
| `env` | Display environment variables | `env` |
| `exit` | Exit the shell | `exit [status]` |

## 📁 Project Structure

```
little_concha/
├── 📂 src/                    # Source code
│   ├── 📂 built-in/           # Built-in commands implementation
│   ├── 📂 command/            # Command parsing and execution
│   ├── 📂 env_variables/      # Environment variable management
│   ├── 📂 input/              # Input handling and processing
│   ├── 📂 pipe/               # Pipe implementation
│   ├── 📂 redirects/          # Redirection and heredoc handling
│   ├── 📂 signal/             # Signal handling
│   ├── 📂 tokenization/       # Input parsing and tokenization
│   ├── 📂 utils/              # Utility functions
│   └── 📄 main.c              # Entry point
├── 📂 includes/               # Header files
├── 📂 Libft/                  # Custom C library
├── 📄 Makefile                # Build configuration
└── 📄 README.md               # This file
```

## 🎯 Examples

### Pipes and Redirections
```bash
shell>> ls -l | grep "README"
shell>> echo "Hello" > output.txt
shell>> cat < output.txt
shell>> echo "World" >> output.txt
```

### Environment Variables
```bash
shell>> export MY_VAR="Hello"
shell>> echo $MY_VAR
Hello
shell>> echo "Exit status: $?"
```

### Heredoc Usage
```bash
shell>> cat << EOF
This is a heredoc
Multiple lines supported
EOF
```

## 🔧 Technical Details

### Architecture
- **Modular design** with clear separation of concerns
- **Memory-safe** implementation with comprehensive cleanup
- **Error handling** throughout the codebase
- **Signal management** for interactive shell behavior

### Key Components
- **Lexer/Parser**: Tokenizes and parses user input
- **Command Executor**: Handles both built-in and external commands
- **Process Manager**: Manages child processes and pipe communication
- **Environment Manager**: Handles variable expansion and environment

### Compliance
- **42 School Standards**: Follows coding standards and project requirements
- **Memory Management**: No memory leaks (Valgrind tested)
- **Error Handling**: Robust error management and status codes

## 👥 Authors

- **galves-a** - *Main development and implementation*
- **fleite-j** - *Contributor and development*

*This project was developed as part of the 42 School curriculum.*

## 📄 License

This project is part of the 42 School curriculum and is intended for educational purposes.

---

## 🔍 Additional Information

### Build Targets
- `make` - Build the minishell
- `make clean` - Remove object files
- `make fclean` - Remove all generated files
- `make re` - Rebuild everything
- `make v` - Run with Valgrind (memory testing)
- `make fd` - Monitor file descriptors

### Development Notes
- Uses **readline** library for command line editing and history
- Implements custom **libft** library for additional utility functions
- Comprehensive **error handling** and **memory management**
- **Signal handling** for proper shell behavior

### Testing
The shell has been tested with:
- Basic command execution
- Complex pipe combinations
- Various redirection scenarios
- Memory leak detection
- Signal handling behavior

---

*Happy shell scripting! 🐚*