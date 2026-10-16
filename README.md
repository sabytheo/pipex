*This project has been created as part of the 42 curriculum by tsaby.*

# pipex

## Description

**pipex** reproduces the behaviour of a shell pipeline in C, built as part of the 42 curriculum.

```bash
./pipex infile "cmd1" "cmd2" outfile
```

behaves like

```bash
< infile cmd1 | cmd2 > outfile
```

The project is an introduction to UNIX processes and inter-process communication:

- `pipe()` creates the channel between the two commands;
- `fork()` creates one child process per command;
- `dup2()` plugs each child's standard input and output into the input file, the pipe or the output file;
- the command is looked up in the directories of the `PATH` environment variable and run with `execve()`;
- the parent closes every unused file descriptor and waits for its children with `waitpid()`.

The **bonus** version accepts any number of commands, chaining them with as many pipes as needed:

```bash
./pipex_bonus infile "cmd1" "cmd2" "cmd3" ... "cmdn" outfile
# same as: < infile cmd1 | cmd2 | cmd3 ... | cmdn > outfile
```

## Instructions

### Compilation

```bash
make          # builds ./pipex
make bonus    # builds ./pipex_bonus
```

The project is compiled with `-Wall -Wextra -Werror` and uses my own [libft](https://github.com/sabytheo/libft) (in `Libft/`).

### Examples

```bash
./pipex infile.txt "grep a" "wc -l" outfile.txt
./pipex infile.txt "ls -l" "cat -e" outfile.txt
./pipex_bonus infile.txt "cat" "tr a-z A-Z" "sort" "uniq" outfile.txt
```

Errors (missing input file, unknown command, permission denied...) are reported on standard error like a shell would.

## Project structure

```
.
├── Makefile
├── include/          # pipex.h, pipex_bonus.h
├── sources/
│   ├── pipex.c           # mandatory part: two commands
│   ├── child_process.c
│   ├── pipex_utils.c     # PATH lookup, errors, cleanup
│   └── bonus/            # any number of commands
└── Libft/
```

## Resources

- `man 2 pipe`, `man 2 fork`, `man 2 dup2`, `man 2 execve`, `man 2 waitpid`
- [Pipe, Fork, Exec and Related Topics](https://www.cs.uleth.ca/~holzmann/C/system/pipeforkexec.html)
