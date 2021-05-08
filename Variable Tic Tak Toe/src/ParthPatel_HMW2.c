#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// size of board changes as user wants
#define SIZE 5

// Function declaration
void print_table(char board[SIZE][SIZE]);
void clear_table(char board[SIZE][SIZE]);
bool check_full(char board[SIZE][SIZE]);
bool check_options(char board[SIZE][SIZE], int row, int col);
void playerX_Move(char board[SIZE][SIZE], int row, int col);
void playerO_Move(char board[SIZE][SIZE], int row, int col);
int check_ends(char board[SIZE][SIZE]);
void update(char board[SIZE][SIZE], int row, int col, char player);
bool check_game_over(char board[SIZE][SIZE]);
void winner(char board[SIZE][SIZE]);

// start main
int main(void)
{
srand(time(NULL));
clock_t begin = clock();
//declare empty board
char board[SIZE][SIZE];
//The row and column start at top left of board
int row=0, col=0;
char choice;
do {
  //make sure table is empty at start if ran multiple times
  clear_table(board);
  //print empty table
  print_table(board);

   //start the game
   playerX_Move(board, row, col);

  //print the winning board
  winner(board);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC; //execution time
  printf("\n Execution time: %f seconds",time_spent);
  printf("\nRUN AGAIN (y/n) ");
  fflush(stdout);
  scanf(" %c", &choice);
} while (choice == 'Y' || choice == 'y'); //I added this for testing the random turns but then changed the way the game runs
return EXIT_SUCCESS;
}

// shows the table at the beginning of the game and after every turn
void print_table(char board[SIZE][SIZE])
{
printf("\nThe board currently looks like this:");
fflush(stdout);
for (int i = 0; i < SIZE; i++)
{
  printf("\n");
  for (int j = 0; j < SIZE; j++)
  {
   if (board[i][j] == ' ')
    printf("* ");
   else
    printf("%c ", board[i][j]);
  }
}
printf("\n");
}

// Makes sure the board is clear when running again
void clear_table(char board[SIZE][SIZE])
{
for (int i = 0; i < SIZE; i++)
{
  for (int j = 0; j < SIZE; j++)
  {
   board[i][j] = ' ';
  }
}
}

// Makes sure table is not full before a turn starts
bool check_full(char board[SIZE][SIZE])
{
for (int i = 0; i < SIZE; i++)
{
  for (int j = 0; j < SIZE; j++)
   if (board[i][j] == ' ')
    return false;
}
return true;
}

// makes sure that the spot chosen by the computer is a valid spot on the board
bool check_options(char board[SIZE][SIZE], int row, int col)
{

if (row < 0 || row > SIZE - 1 || col < 0 || col >SIZE - 1)
  return false;
if (board[row][col] != ' ')
  return false;
return true;
}


// Checks the board and makes player X move before calling Player O until there is a winner
void playerX_Move(char board[SIZE][SIZE], int row, int col)
{
	for (int row = 0; row < SIZE; row++) //runs through the board
		{
		  for (int col = 0; col < SIZE; col++)
		  {
			  if (check_options(board, row, col)) //finds first open spot
			  	  {
				  if (!check_game_over(board)) //as long as the game is not over the next player makes a move
				  	{
			  	  update(board, row, col, 'X');
			 	  printf("\nPlayer X has entered [row, col]: %d,%d ", (row + 1), (col + 1));
			 	  fflush(stdout);
			 	  print_table(board);
			 	  playerO_Move(board, row, col);
			 	  break;
			  	  }

		  }

		}
		}
	}


	/*  while (!check_options(board, row, col)) //random turns for original version
	  {

	   row = rand() % SIZE;
	   col = rand() % SIZE;
	  }
	  update(board, row, col, 'X');
	  printf("\nPlayer X has entered [row, col]: %d,%d ", (row + 1), (col + 1));
	  fflush(stdout);
	  print_table(board);
	  playerO_Move(board, row, col);
	*/

// Same as X but for O
void playerO_Move(char board[SIZE][SIZE], int row, int col)
{


			for (int row = 0; row < SIZE; row++)
			{
			  for (int col = 0; col < SIZE; col++)
			  {
				  if (check_options(board, row, col))
				  	  {
					  if (!check_game_over(board))
					  		{
					  	  update(board, row, col, 'O');
					 	  printf("\nPlayer O has entered [row, col]: %d,%d ", (row + 1), (col + 1));
					 	  fflush(stdout);
					 	  print_table(board);
					 	 playerX_Move(board, row, col);
					 	 break;
				  	  }

			  }

			}

		}
}


/*if (!check_game_over(board)) //random turns for original version
{
  row = rand() % SIZE;
  col = rand() % SIZE;
  while (!check_options(board, row, col))
  {
   row = rand() % SIZE;
   col = rand() % SIZE;
  }
  update(board, row, col, 'O');
  printf("\nPlayer O  has entered [row, col]: %d,%d ", (row + 1), (col + 1));
  fflush(stdout);
  print_table(board);
  playerX_Move(board, row, col);
  }*/


// Checks the win conditions
int check_ends(char board[SIZE][SIZE])
{
// checks through rows and columns
for (int i = 0; i < SIZE; i++)
{
  // run through the rows checking first 2 values and seeing if they match the last value in row

  if ((board[i][0] == board[i][1]) && (board[i][0] == board[i][SIZE-1]))
  {
   if (board[i][0] == 'X')
    return 2 ;
   else if (board[i][0] == 'O')
    return 1;
  }
  // same check as rows but for columns
  if ((board[0][i] == board[1][i]) && (board[0][i] == board[SIZE-1][i]))
  {
   if (board[0][i] =='X')
    return 2 ;
   else if (board[0][i] == 'O')
    return 1;
  }
 if ((board[0][0] == board[i+1][i+1]) && (board[0][0] == board[SIZE-1][SIZE-1])) // diagonal checking first,second, and last
  {
   if (board[0][0] == 'X')
    return 2 ;
   else if (board[0][0] == 'O')
    return 1;
  }
}
return 0;
}


void update(char board[SIZE][SIZE], int row, int col, char player) //if the move was valid then gets the move and adds it to the board
{
board[row][col] = player;
}


//function that checks for a winner or a full board to end the game
bool check_game_over(char board[SIZE][SIZE])
{
int winner = check_ends(board);

if (winner != 0)
{
  return true;
}

if (check_full(board))
{
  return true;
}

return false;
}


// After game is over the winner or end screen is displayed
void winner(char board[SIZE][SIZE])
{
int winner = check_ends(board);
if (winner == 1)
{
  printf("\nO Player wins");
}

else if (winner == 2)
{
  printf("\nX Player wins");
}
else
{
  printf("\nGame over because board is full");
}
}
