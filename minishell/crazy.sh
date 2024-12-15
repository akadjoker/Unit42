#!/bin/bash

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
YELLOW='\033[1;33m'
NC='\033[0m'

# Função para imprimir cabeçalhos
print_header() {
    echo -e "\n${BLUE}=== $1 ===${NC}\n"
}

# Função para imprimir subseções
print_section() {
    echo -e "\n${YELLOW}--- $1 ---${NC}\n"
}

# Função para testar e comparar output
test_cmd() {
    echo -e "${GREEN}Testing:${NC} $1"
    echo "$ $1"
    eval "$1"
    echo -e "Exit Status: $?\n"
}

# Salvando SHLVL original
ORIGINAL_SHLVL=$SHLVL

print_header "BASIC COMMAND TESTS"
test_cmd "echo Hello World"
test_cmd "pwd"
test_cmd "ls -la"
test_cmd "/bin/ls"
#test_cmd "./minishell"

print_header "BUILTIN TESTS"
print_section "Echo Tests"
test_cmd "echo -n test"
test_cmd "echo -nnnn test"
test_cmd "echo"
test_cmd "echo ''"
test_cmd 'echo "$HOME"'
test_cmd "echo '$HOME'"

print_section "CD Tests"
test_cmd "cd .."
test_cmd "pwd"
test_cmd "cd -"
test_cmd "cd"
test_cmd "cd ."
test_cmd "cd /tmp"
test_cmd "cd ~"

print_section "Export Tests"
test_cmd "export A=test"
test_cmd "echo \$A"
test_cmd "export A+=test"
test_cmd "echo \$A"
test_cmd "export"

print_section "Unset Tests"
test_cmd "unset A"
test_cmd "echo \$A"

print_header "CRAZY ENVIRONMENT TESTS"
print_section "SHLVL Madness"
test_cmd "echo \$SHLVL"
test_cmd "export SHLVL="
test_cmd "export SHLVL=99999"
test_cmd "export SHLVL=-999"
test_cmd "export SHLVL=abc"
test_cmd "export SHLVL=1.2"

print_section "PATH Chaos"
test_cmd "export PATH="
test_cmd "ls"
test_cmd "export PATH=."
test_cmd "ls"
test_cmd "export PATH=:::::::::"
test_cmd "ls"
test_cmd 'export PATH="/usr/bin:/bin"'

print_section "Crazy Variables"
test_cmd "export ''"
test_cmd "export \"=\""
test_cmd "export +=+"
test_cmd "export \"  \"=space"
test_cmd "export !@#$%^&*=symbols"
test_cmd "export A=B=C=D=E"
test_cmd "echo \$A"

print_header "PIPE AND REDIRECT TESTS"
print_section "Basic Pipes"
test_cmd "ls | grep a"
test_cmd "ls | grep a | wc -l"
test_cmd "cat /etc/passwd | grep root"

print_section "Crazy Pipes"
test_cmd "ls ||| grep a"
test_cmd "ls | | grep a"
test_cmd "| ls"
test_cmd "ls |"

print_section "Redirections"
test_cmd "echo hello > testfile"
test_cmd "cat < testfile"
test_cmd "echo world >> testfile"
test_cmd "cat < testfile"
test_cmd "cat < nonexistentfile"
test_cmd "echo test > /dev/null"

print_header "QUOTE AND EXPANSION TESTS"
print_section "Quote Combinations"
test_cmd "echo \"\'\"\'\""
test_cmd "echo \"'$HOME'\""
test_cmd "echo '\"\$HOME\"'"
test_cmd "echo \"\\\'\\\"\\$HOME\\\"\\\'\""

print_section "Variable Expansions"
test_cmd "echo \$"
test_cmd "echo \$?"
test_cmd "echo \$HOME\$PATH\$USER"
test_cmd "echo \"\$HOME\"\'\$HOME\'"
test_cmd "echo \$NONEXISTENT"

print_header "ERROR HANDLING TESTS"
test_cmd "nonexistentcommand"
test_cmd "./nonexistentfile"
test_cmd "cd nonexistentdirectory"
test_cmd "< nonexistentfile cat"
test_cmd "> /dev/null/invalid echo test"

print_header "SIGNAL TESTS"
print_section "Instructions for Signal Testing"
echo "1. Test Ctrl+C with: sleep 5"
echo "2. Test Ctrl+D with empty input"
echo "3. Test Ctrl+\\ with: sleep 5"

print_header "MULTIPLE COMMAND TESTS"
test_cmd "echo hello; echo world"
test_cmd "cd ..; pwd; cd -"
test_cmd "export A=hello; echo \$A; unset A; echo \$A"

print_header "CLEANUP"
test_cmd "rm -f testfile"

# Restaurar SHLVL original
export SHLVL=$ORIGINAL_SHLVL

echo -e "\n${GREEN}=== Tests Complete ===${NC}"
echo "Remember to compare outputs with original bash!"
