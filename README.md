# rsh

rsh is a small Unix shell written in C. It supports basic command execution, I/O redirection, pipes, environment variable expansion, and a few built-in commands.

## Features

- Command execution using `execvp`
- Built-in commands:
  - `cd` — change directory
  - `exit` — exit the shell
  - `help` — print available built-ins
- Environment variable expansion (e.g., `echo $HOME`)
- Basic signal handling for `Ctrl+C`
- Output redirection: `command > file`
- Input redirection: `command < file`
- Piping between two commands: `command1 | command2`
- Quoted argument parsing: `echo "hello world"`
- Prompt displays current working directory

## Usage

Clone and compile:

```sh
git clone https://github.com/rayaanra/rsh
cd rsh
make
./rsh
```

Example commands:

```sh
echo "test" > test.txt
cat < test.txt
cd src
pwd
echo $HOME
```

## Notes and Limitations

- Maximum of 64 tokens, each up to 64 characters
- No background jobs (`&` not supported)
- No wildcard/glob expansion
- Only one pipe (`|`) allowed per command
- Double quotes supported; single quotes are not
- `cd` does not support `~`
- No config files or customization
- Unix-only (Linux/macOS); no Windows support

## Project Goals

- Understand fork/exec/wait
- Use raw system calls like `dup2`, `pipe`, `open`
- Handle process execution and I/O manually
- Practice modular C structure with low dependencies
