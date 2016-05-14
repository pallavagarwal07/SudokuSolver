# Sudoku Solver

Recently, I have been having fun using SAT solvers for a variety of tasks. This time I
thought I would model sudoku problems as a boolean satisfiability problem. I'm surprised
it works so good. I tried it on the problem that comes up on googling `hardest sudoku
problem ever`. It solved it within miniseconds and without a hiccup.

The demo is [here on my blog](http://sudoku.varstack.com)

Note that the program runs completely on the client's browser as I converted the C
program `picosat` which is a SAT solver, into JS to run natively on the browser.
It's amazingly fast. Have fun playing with it :)

Credit: Picosat has been used for solving SAT equations in this program.
