#!/bin/bash

# Minishell Comprehensive Test Suite
# Run with: bash test_minishell.sh

echo "🧪 ===== MINISHELL COMPREHENSIVE TEST SUITE ===== 🧪"
echo ""

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

print_test_header() {
    echo -e "${BLUE}📋 $1${NC}"
    echo "----------------------------------------"
}

print_command() {
    echo -e "${YELLOW}> $1${NC}"
}

print_test_header "BASIC FUNCTIONALITY TESTS"

echo "Copy and paste these commands one by one into your minishell:"
echo ""

print_command "echo hello"
print_command "pwd"
print_command "env | head -5"
print_command "cd /tmp"
print_command "pwd"
print_command "cd -"

echo ""
print_test_header "QUOTE PARSING TESTS (CRITICAL)"

print_command "echo 'hello world'"
print_command "echo 'Hello \$USER'"
print_command "echo '\$PWD is current directory'"
print_command "echo \"hello world\""
print_command "echo \"Hello \$USER\""
print_command "echo \"\$PWD is current directory\""
print_command "echo \"double\" 'single'"
print_command "echo 'single' \"double\""
print_command "echo \"\""
print_command "echo ''"

echo ""
print_test_header "VARIABLE EXPANSION TESTS"

print_command "export MY_VAR=hello"
print_command "echo \$MY_VAR"
print_command "echo \"\$MY_VAR world\""
print_command "echo '\$MY_VAR world'"
print_command "ls nonexistent 2>/dev/null"
print_command "echo \$?"
print_command "ls"
print_command "echo \$?"

echo ""
print_test_header "PIPE TESTS"

print_command "echo hello | cat"
print_command "ls | grep mini"
print_command "env | grep USER"
print_command "echo \"hello world\" | tr ' ' '\n' | sort"
print_command "export | grep HOME"

echo ""
print_test_header "REDIRECTION TESTS"

print_command "echo \"test content\" > output.txt"
print_command "cat output.txt"
print_command "echo \"line2\" >> output.txt"
print_command "cat output.txt"
print_command "cat < output.txt"
print_command "rm output.txt"

echo ""
print_test_header "HEREDOC TESTS"

echo "Test heredoc (type the following, then type EOF and press Enter):"
print_command "cat << EOF"
echo "This is a heredoc test"
echo "Multiple lines"
echo "With \$USER expansion"
echo "EOF"

echo ""
print_test_header "BUILT-IN COMMANDS TESTS"

print_command "export TEST_VAR=hello"
print_command "echo \$TEST_VAR"
print_command "export | grep TEST_VAR"
print_command "unset TEST_VAR"
print_command "echo \$TEST_VAR"
print_command "cd ~"
print_command "pwd"
print_command "cd /tmp"
print_command "pwd"
print_command "cd"
print_command "pwd"

echo ""
print_test_header "ERROR HANDLING TESTS"

print_command "nonexistent_command"
print_command "cat < nonexistent.txt"
print_command "export 123VAR=invalid"
print_command "export =invalid"

echo ""
print_test_header "COMPLEX INTEGRATION TESTS"

print_command "echo \"hello world\" | grep \"world\""
print_command "export FILENAME=test.txt"
print_command "echo \"content\" > \$FILENAME"
print_command "cat \$FILENAME"
print_command "rm \$FILENAME"

echo ""
print_test_header "EDGE CASES"

print_command "echo \"   multiple   spaces   \""
print_command "echo 'literal   spaces'"
print_command "echo \"\$\""
print_command "echo \"\$\$\""
print_command "echo \"\$NONEXISTENT\""

echo ""
print_test_header "SIGNAL TESTS"

echo -e "${YELLOW}Manual tests (run these manually):${NC}"
echo "1. Run: sleep 10, then press Ctrl+C (should interrupt)"
echo "2. Run: sleep 10, then press Ctrl+\\ (should be ignored)"
echo "3. Press Ctrl+D on empty prompt (should exit shell)"

echo ""
print_test_header "AUTOMATED QUICK TEST"

echo "Creating quick_test.txt with test commands..."

cat > quick_test.txt << 'EOF'
echo "=== Quick Minishell Test ==="
echo 'Single quotes work'
echo "Double quotes with $USER"
export TEST=value
echo $TEST
echo "test" | cat
echo "output" > temp.txt
cat temp.txt
rm temp.txt
echo "Test completed!"
EOF

echo "File created: quick_test.txt"
echo ""
echo -e "${GREEN}✅ Test suite ready!${NC}"
echo ""
echo -e "${BLUE}📖 USAGE INSTRUCTIONS:${NC}"
echo "1. Start your minishell: ./minishell"
echo "2. Copy and paste commands from above sections"
echo "3. For quick test, run each line from quick_test.txt manually"
echo "4. Pay special attention to quote parsing tests!"
echo ""
echo -e "${RED}🎯 CRITICAL: Your parser implementation should handle all quote tests correctly!${NC}"