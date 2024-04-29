/**

@mainpage EPL232 hw1 

@author Elena Eleftheriou

The game is played on a 5x5 grid where the Musketeer ('M') must capture the enemy soldiers
('o') by moving either up, down, left, or right, the same as the enemy soldiers.
The game ends when all enemies are captured by the Musketeer or
when there are no more moves left for the Musketeers, or
when the Musketeers are in the same row or column.

The game starts from the main function and calls the function play() with the argv[1]
argument so that it gets the input from the user, from the terminal.
Then the function play starts the game, by asking the Musketeer to give a move.
It checks if the move is valid and then either stops the game, if thats what is asked,
or moves the musketeer in the given position and prints the board.
This procedure continues with the enemy's move, and continues until somebody stopped
the game or somebody won the game.
Lastly, it prints the board in the out-input.txt file.





Bugs: No known bugs.

*/