/*
  tic_tac_toe.c

  Basic terminal implementation of Tic-Tac-Toe

  Author: André Couto Gimael <acgimael at hotmail dot com>
  Date: January 2019
  License: MPL 2.0
*/
#include <stdlib.h>
#include <stdio.h>

/* The default size of the board is 3, but it may be changed to 4 or 5 */
#ifndef BOARD_SIZE
#define BOARD_SIZE 3
#endif

#if BOARD_SIZE < 3 || BOARD_SIZE > 5
#error "Board size is less than 3 or greater than 5"
#endif

#define SQ(x) ((x)*(x))

void board_init(unsigned char board[SQ(BOARD_SIZE)]);
int place_tile(unsigned char board[SQ(BOARD_SIZE)], char player, int index);
int check_game(unsigned char board[SQ(BOARD_SIZE)], int index);
void print_board(unsigned char board[SQ(BOARD_SIZE)]);

void board_init(unsigned char board[SQ(BOARD_SIZE)])
{
	for (int i = 0; i < (SQ(BOARD_SIZE)); ++i) {
		board[i] = 'a' + i;
	}
}

int place_tile(unsigned char board[SQ(BOARD_SIZE)], char player, int index)
{
	if ((board[index] >= 'a') && (board[index] <= (SQ(BOARD_SIZE) + 'a'))) {
		board[index] = player;
		return 0; /* SUCCESS */
	}
	return 1; /* FAILURE */
}

int check_game(unsigned char board[SQ(BOARD_SIZE)], int index)
{
	char current = board[index];
	int
		x = index % BOARD_SIZE,
		y = index / BOARD_SIZE;
/*rows:*/
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board[BOARD_SIZE*y + i] != current) { /* ROWS */
			goto columns;
		}
	}
	return 1; /* GAME IS OVER */

columns:
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (board[BOARD_SIZE*i + x] != current) { /* COLUMNS */
			goto diag;
		}
	}
	return 1; /* GAME IS OVER */

diag:
	if (x == y) { /* \ diagonal */
		for (int i = 0; i < BOARD_SIZE; ++i) {
			if (board[(BOARD_SIZE + 1)*i] != current) {
				goto rev;
			}
		}
		return 1; /* GAME IS OVER */
	}

rev:
	if ((x + y) == (BOARD_SIZE - 1)) { /* / diagonal */
		for (int i = 0; i < BOARD_SIZE; ++i) {
			if (board[(BOARD_SIZE - 1)*(i + 1)] != current) {
				goto ret;
			}
		}
		return 1; /* GAME IS OVER */
	}

ret:
	return 0; /* GAME IS NOT OVER */
}

void print_board(unsigned char board[SQ(BOARD_SIZE)])
{
	putchar('\n');
	for (int y = 0; y < BOARD_SIZE; ++y) {
		if (y > 0) {
			for (int x = 0; x < BOARD_SIZE; ++x) {
				if (x > 0) {
					putchar('+');
				}
				fputs("---", stdout);
			}
			putchar('\n');
		}
		for (int x = 0; x < BOARD_SIZE; ++x) {
			if (x > 0) {
				putchar('|');
			}
			fprintf(stdout, " %c ", board[BOARD_SIZE*y + x]);
		}
		putchar('\n');
	}
}

int main()
{
	int turn = 0;
	unsigned char board[SQ(BOARD_SIZE)];
	char player[] = {'X', 'O'};
	char free_tiles = SQ(BOARD_SIZE);

	board_init(board);

	while (1) {
		char choice[8];
		unsigned char c = '\0';
		print_board(board);
		fprintf(stdout, "Player %c: ", player[turn]);
		if (fgets(choice, sizeof(choice), stdin) == NULL) {
			fputs("Bye!\n", stdout);
			break;
		}
		int ret = sscanf(choice, " %c", &c);
		if (ret == EOF) {
			continue;
		}
		if (ret == 1) {
			if (c >= 'a' && c <= (SQ(BOARD_SIZE) + 'a')) {
				c -= 'a';
				if (place_tile(board, player[turn], c)) {
					fprintf(stdout, "Could not place the tile. Try again.\n");
				} else {
					if (check_game(board, c) == 1) {
						fprintf(stdout, "Game over. Player %c wins.\n", player[turn]);
						print_board(board);
						break;
					}
					turn = 1 - turn;
					--free_tiles;
					if (free_tiles == 0) {
						fprintf(stdout, "Game over. It was a draw.\n");
						print_board(board);
						break;
					}
				}
			} else {
				fprintf(stdout, "Input %c is out of range\n", c);
			}
		} else {
			fputs("What was that?\n", stdout);
		}
	}

	return EXIT_SUCCESS;
}
