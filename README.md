# Julia Compiler

### Objective
Implement a subset of the Julia programming language (http://learnxinyminutes.com/docs/julia/ | http://julialang.org/) to MIPS.
The subset should include:
- Integers              ✓
- Floats	            ✓
- Booleans	            ✓
- Aritmetic Expressions	✓
- Booleam Expressions	✓
- println               X
- Attributions          ✓
- If then else          X
- Ciclos While          X

The compiler should:
1. Analyze the syntex of a Julia program or language use case and build an accurate representation of the Syntax Tree.
1. Translate the Syntax Tree into 3 Address intermediate code.
1. Translate the 3 Address intermediate code into corresponding MIPS code and output it to a file.

### How to
You can test the compiler by running:
`$ a.out < input.jl`