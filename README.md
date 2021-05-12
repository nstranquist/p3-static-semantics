scope=LOCAL

# P3 - Static Semantics

This is a static semantics portion of the program translation project. It will check for syntax from the parse tree generated from the parser.

As discussed during office hours, I'll be including output of the program in the `output/` folder, since my local dev environment compiles but does not compile with `make` on Delmar without throwing errors.

Tests are included in the `tests/` folder, and their names correspond with the output names. `p3-[test-name]-output` is the format I used to name the output screenshots

### Steps to Run (skip if on Delmar)

1. Run `make` in the directory
2. Run `./staticSemantics [filename]` where filename is the file you want to test. It should be written according to he specified programming language BNF grammar

Thank you very much!