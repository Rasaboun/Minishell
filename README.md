<h1 align="center">
	💻Minishell
 42cursus project💻
</h1>



<p align="center">
<img align="center" alt="Minishell-Screenshot" src="https://user-images.githubusercontent.com/40967731/227051424-76741d01-f6d1-44ee-b574-bc6daff62ba0.png" width="600" height="400">
</p>

<h3 align="center">
	<a href="#about">About</a>
	<span> · </span>
	<a href="#projetstructure"> Project Structure </a>
	<span> · </span>
	<a href="#features">Features</a>
	<span> · </span>
	<a href="#usage">Usage</a>
</h3>

<h2 id="about">
About
</h2>

> The objective of this project is to create a ***minimalist*** **shell**.

<h2 id="usage">
🔨 Usage
</h2>

```shell
Make && ./minishell
```

https://user-images.githubusercontent.com/40967731/227058420-84218245-735b-49f0-ac10-de637e7a093f.mov

<h2 id="projetstructure">
Project Structure
</h2>

```
.
├── 📁includes/
│   └── minishell.h
├── 📁libft/
│   └── libft.a
├── 📁srcs/
│   ├── 📁builtins/
│   │   └── *.c
│   ├── 📁execution/
│   │   └── *.c
│   ├── 📁parsing/
│   │   └── *.c
│   └── 📁utils/
│       └── *.c
└── Makefile
```


* [**📂 libft:**](libft/) My implementation of some of the Standard C Library functions compiled into a library
* [**📂 src:**](src/) Source file
* [**📂 buildtins:**](src/buildtins/) buildtins functions
* [**📂 parsing:**](src/parsing/) parsing functions
* [**📂 execution:**](src/execution/) execution functions
* [**📂 utils:**](src/utils/) utils functions

<h2 id="features">
📖 Features
</h2>

<h3>
Buildtins
</h3>

| Command           | Option        |
| ------------- |:-------------:|
| `echo`         | -n     |
| `cd`           | only with a relative or absolute path     |
| `pwd`           | none    |
| `export`           | none  |
| `unset`           | none |
| `env`           | none    |
| `exit`           | none    |

<h3>
Redirections
</h3>

- `<` must redirect the input.
- `>` must redirect the output.
- `<<` must receive a delimiter and read the given input until a line
containing the delimiter. However, the history does not have to be updated!
- `>>` must redirect the output to append mode.

<h3>
Signals
</h3>

`ctrl-C`, `ctrl-D` and `ctrl-\` should work as in bash.

**In interactive mode:**
- `ctrl-C` displays a new prompt on a new line.
- `ctrl-D` exits the shell.
- `ctrl-\` does nothing

<h3>
Pipe
</h3>

`|` The output of each command in the pipeline is connected to the input of the next command by a pipe.

<h3>
Quotes
</h3>

- Do not interpret unclosed quotation marks or special characters, such as `\` (the backslash) or `;` (the semicolon).
- `'` (single quote) which should prevent the shell from interpreting the metacharacters characters present in the sequence between quotes.
- `"` (double quote) which should prevent the shell from interpreting the metacharacters characters present in the sequence between quotes except the $ (dollar sign).

