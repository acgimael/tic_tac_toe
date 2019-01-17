# Tic-Tac-Toe

A simple terminal implementation of the classic tic-tac-toe game.

## Build

Run `make` on the root project directory.

### Extra

If you'd like to build the game with a
bigger board you can do it by adding `-DBOARD_SIZE=4` to the `CFLAGS` variable
in the `Makefile` file. You can also set the board size to 5. Due to how the
game was coded you may only set these variables to 3, 4 or 5.

## Run

After you build, run the game by typing `bin/tic_tac_toe` in the
terminal. You'll be presented with a board labeled with letters. There are two
players, one that plays with the letter `X` and one that plays with the letter
`O`. On your turn type the letter of the slot in which to place your tile.

## To-Do

Add tests.

## Author

André Couto Gimael
