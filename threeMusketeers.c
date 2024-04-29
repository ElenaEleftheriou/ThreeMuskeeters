/** @file threeMusketeers.c
 *  @brief The game three Musketeers 
 *  as first homework exercise for EPL232.
 *
 *  The game consists of a board 5x5, 
 *  which the players move up,down,right or left as either the enemy or the musketeer.
 *  It gets the grid from a given input file and at the end of the game,
 *  prints the final result at the out-input.txt.
 *
 *  @author Elena Eleftheriou
 *  @bug No know bugs.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

/**
 * The constand length of the 2d array. 
*/
#define N 5

/** @brief Reads the data of a given file.
 *
 *  Gets a file from the terminal and reads its data while 
 *  putting them in the board.
 *  If a value from the file is not '.' or 'M' or 'o', or if the file doesn't have a complete board,
 *  then it gives an error message.
 *
 *  @param board the board of the game
 *  @param fileName the name of the input file
 *  @return void
 */
void readBoard(char board[][N], char *fileName);

/**
 *  @brief Prints the board.
 * 
 *  Prints the board in the requested form.
 * 
 *  @param board the board of the game
 *  @return void
 * 
*/
void display_board(char board[][N]);

/**
 *  @brief Prints the board in the out-input.txt file.
 * 
 *  If the game is finished with a winner, then it is saved in 
 *  the file, or if the game was stopped by a player,
 *  the board is saved at a form that if the player
 *  wants to resume it, then he can.
 * 
 *  @see play()
 *  @param board the board of the game
 *  @param fileName the output file that is created in the function play()
 *  @return void
 *  
*/
void writeBoard(char board[][N], char *fileName);

/**
 *  @brief the function where the game runs.
 * 
 *  creates a board that reads its values using readBoard()
 *  and then counts how many enemies are in that board using countEnemy()
 *  and prints the requested messages.
 *  Then plays the game starting with the Musketeer and changing the character each time,
 *  until the user wants to stop the game or one of the players won.
 *  Also, if the musketeers don't have another move, but the sum of the enemies 
 *  is not equal to 0, then the enemy is allowed to play one more time.
 *  Lastly, using writeBoard(), it prints the final board in the output file.
 * 
 *  @param filename the input file that is given from the terminal
 *  @return void
*/
void play(char *filename);

/**
 *  @brief Checks whether the given input has the correct characters.
 * 
 *  Checks if the parameters contain the correct letters, for example if j is between 0 and 4,
 *  if not returns false.
 * 
 *  @param i i
 *  @param j j
 *  @param value value
 *  @return bool
*/
bool checkInput(char i, int j, char value);

/**
 *  @brief Stops the game.
 * 
 *  If the input is 0,0=E returns true and the game is stopped.
 * 
 *  @param i i
 *  @param j j
 *  @param value value
 *  @return bool
*/
bool stopGame(char i, int j, char value);

/**
 *  @brief Reads the given input from the user.
 * 
 *  It reads the input from the user and makes some checks to see if 
 *  everything is correct. If the input is not in a form i,j=value, 
 *  or if values are 0,0=E, using stopGame() or if the 
 *  input is not correct, using checkInput(), it prints a message and returns true
 *  If everything is correct it returns false;
 *  
 *  @param i i
 *  @param j j
 *  @param value value
 *  @return bool
*/
bool readInput(char *i, int *j, char *value);

/**
 *  @brief Moving position value.
 * 
 *  If the value is up or left it returns -1
 *  else it returns 1.
 * 
 *  @param value value
 *  @return int
*/
int movingPosition(char value);

/**
 *  @brief Checks if the given input places the player out of the board.
 * 
 *  Using movingPosition(), it checks if the player gets out of the board
 *  and returns true or false.
 * 
 *  @see movingPosition() 
 *  @param board the board of the game
 *  @param i i
 *  @param j j
 *  @param value value
 *  @return bool
*/
bool outOfBoard(char board[][N],char i, int j,char value);

/**
 *  @brief The function where the player moves in the board.
 * 
 *  It asks from the player (either enemy or musketeer based on the value of the character) 
 *  to give its desired move and makes the appropriate checks to see if the
 *  input is correct based on its values.If the game is stopped, if the player gets out of the board,
 *  or if the player wants to move somewhere in the board where he can't.
 *  If everything is correct then the player moves to that position, the board changes and its printed
 *  else if the game is stopped, it prints it and makes the value for the variable stop true.
 *  Also, if the player is the Musketeer it changes the sum to -1 to know how
 *  many enemies are left.
 * 
 *  @param board the board of the game
 *  @param character enemy or musketeer
 *  @param stop stop the game or not
 *  @param sum the sum of the enemies
 *  @return void
*/
void playCharacter(char board[][N], char *character, bool *stop, int *sum);

/**
 *  @brief Check if there are any left moves for the musketeer.
 * 
 *  Checks whether there is at least one 'o' in the position that musketeer can 
 *  move and returns true. Else if there are not any enemies left where the musketeer can reach them
 *  then the musketeers won and it returns false.
 * 
 *  @param board the board of the game
 *  @return bool
*/
bool winMusketeer(char board[][N]);

/**
 *  @brief checks if the enemies won.
 * 
 *  Checks if all the musketeers are in the same row or column, and if they are,
 *  it returns true because the enemies won.
 * 
 *  @param board the board of the game
 *  @return bool
*/
bool winEnemy(char board[][N]);

/**
 *  @brief Counts the enemies.
 * 
 *  Counts how many enemies are in the 
 *  given board, and returns that number.
 * 
 *  @param board the board of the game
 *  @return int
*/
int countEnemy(char board[][N]);

/**
 *  @brief Checks if the player is allowed to move in that position.
 * 
 *  Checks if the player is allowed to move in the given position,
 *  based on the enemy, for example if the enemy is 'o' and the player
 *  moves to '.' or 'M', then it returns false
 * 
 *  @param board the board of the game
 *  @param i i
 *  @param j j 
 *  @param value value
 *  @param enemy enemy
 *  @return bool
*/
bool checkMovingPosition(char board[][N], char i, int j, char value, char enemy);

/** @brief Program entrypoint.
 *  
 *  It calls the function play() with the argument argv[1]
 *  to start the game with the given file from the terminal.
 *
 * @return 0
 */
int main(int argc, char *argv[]){
    play(argv[1]);
       
    return 0;
}

void readBoard(char board[][N], char *fileName){
    FILE *fp;
    fp = fopen(fileName,"r");

    if(fp == NULL){
        perror("Problem in file open");
        exit(-1);
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int temp = fgetc(fp);
            if(temp == EOF){
                perror("File not complete");
                exit(-1);
            }
            if((char)temp == ' '){
                temp = fgetc(fp);
            }
            if((char)temp != 'o' && (char)temp != 'M' && (char)temp != '.'){
                perror("Wrong input");
                exit(-1);
            }
            board[i][j] = (char)temp;
        }
        if(fgetc(fp) != '\n'){
            perror("File not complete");
            exit(-1);
        }
    }    
    fclose(fp);  
}

void writeBoard(char board[][N], char *fileName){
    FILE *fp;
    
    fp = fopen(fileName,"w");

    if(fp == NULL){
        perror("Problem in file open");
        exit(-1);
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            fprintf(fp,"%c", board[i][j]);
            if(j!=4)
                fprintf(fp, " ");
        }
        fprintf(fp,"\n");
    }
    printf("Saving %s...Done\nAu revoir!\n", fileName);
    fclose(fp);
}

void display_board(char board[][N]){
    printf("    1   2   3   4   5   \n");    
    printf("  +---+---+---+---+---+\n");
    for(int i=0;i<5;i++){
        printf("%c |", ('A'+i));
        for(int j=0;j<5;j++){
            printf(" %c |", board[i][j]);
        }
        printf("\n");
        printf("  +---+---+---+---+---+\n");    
    }
    printf("\n");
}

bool checkInput(char i, int j, char value){
    if(i!='A' && i!='B' &&  i!='C' && i!='D' && i!='E'){
        return false;
    }
    if(j!=1 && j!=0 && j!=2 && j!=3 && j!=4){
        return false;
    }
    if(value!= 'L' && value!='R' && value!='U' && value!='D'){
        return false;
    }
    
    return true;
}

bool stopGame(char i, int j, char value){
    if(i == '0' && (j + 1) == 0 && value == 'E'){
        return true;
    }
    return false;
}

bool readInput(char *i, int *j, char *value){
    int input = getc(stdin);
    if((char)input == '\n' || (char)input == ' ')
        input = getc(stdin);
    int e=0;
    do{
        if(e == 0)
            *i = toupper((char)input); //makes the characters uppercase
        else if(e == 1 && (char)input != ',') 
            e=7;
        else if(e == 2)
            *j = input - '0' -1; //makes j based on the values of an array
        else if(e == 3 && (char)input!='=')
            e=7;
        else if(e==4)
            *value = toupper((char)input);
        e++;
        input = getc(stdin);
    }while(input != (char)' ' && input != (char)'\n' && e!=5);
    if(e>5){
        printf("\nWrong input form.\n\n");
        return true;
    }   
    else if(stopGame(*i,*j,*value)){
        return true;
    }
    else if(!checkInput(*i, *j, *value)){
        printf("\nWrong input form.\n\n");
        return true;
    }
    else{
        return false;
    }
    return true;
}

int movingPosition(char value){
    if(value == 'L' || value == 'U')
        return -1;
    if(value == 'R' || value == 'D')
        return 1;
}

bool checkMovingPosition(char board[][N], char i, int j, char value, char enemy){
    if(value == 'L' || value == 'R')
        if(board[i- 'A'][j + movingPosition(value)] != enemy)
            return false;
    if(value == 'D' || value == 'U')
        if(board[i- 'A'+ movingPosition(value) ][j] != enemy)
            return false;
    return true;
}

bool outOfBoard(char board[][N], char i, int j, char value){
    if((value == 'D' || value == 'U'))
        return ((i- 'A'+ movingPosition(value))>4 || (i- 'A'+ movingPosition(value))<0);
    else if((value == 'L' || value == 'R'))
        return ((j + movingPosition(value))>4 || (j + movingPosition(value))<0);

}

int countEnemy(char board[][N]){
    int sum = 0;
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            if(board[i][j]=='o')
                sum++;
    return sum;
}

void playCharacter(char board[][N], char *character, bool *stop, int *sum){
    char i , value;    
    int j;
    bool flag = false;
    char player, enemy;
    do{
        printf("Give the %s's move\n>", character);
        flag = readInput(&i, &j, &value);        
    }while(flag && !stopGame(i, j, value));
    if(strcmp(character, "Musketeer")==0){
        player = (char)'M';
        enemy = (char)'o';
    }
    else{
        player = (char)'o';
        enemy = (char)'.';
    }
    while((board[i - 'A'][j] != player || outOfBoard(board,i,j,value) || !checkMovingPosition(board, i, j, value, enemy)) && !stopGame(i, j, value)){ 
        if(player == (char)'o' && board[i - 'A'][j] == 'M')
            printf("\nYou can't move there!\n\n");
        else
            printf("\nThis move gets out of the board or it's a wrong move.\n\n");
        do{
            printf("Give the %s's move\n>", character);
            flag = readInput(&i, &j, &value);        
        }while(flag && !stopGame(i, j, value));
    }
    if((value == 'D' || value == 'U')){
        if(player == 'M')
                *sum = *sum -1;
        board[i - 'A'][j] = '.';
        board[i- 'A' + movingPosition(value)][j] = player;
        display_board(board); 
    }
    else if(value == 'L' || value == 'R'){
        if(player == 'M')
                *sum = *sum -1;
        board[i - 'A'][j] = '.';
        board[i  - 'A'][j + movingPosition(value)] = player;
        display_board(board);
    }       
    else{
        printf("\nGame stopped.\n");
        *stop = true;
    }
}
 
bool winMusketeer(char board[][N]){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(board[i][j] == 'M'){
                if(i+1<N)
                    if(board[i+1][j]=='o')
                        return true;
                if(i-1>=0)
                    if(board[i-1][j] == 'o')
                        return true;
                if(j+1<N)
                    if(board[i][j+1]=='o')
                        return true;
                if(j-1>=0)
                    if(board[i][j-1]=='o')
                        return true;
            }
        }
    }
    return false;
}

bool winEnemy(char board[][N]){
    for(int i=0; i<N; i++){
        int flag = 0;
        int flag2 = 0;
        for(int j=0; j<N; j++){
            if(board[i][j]=='M')
                flag++;
            if(board[j][i]=='M')
                flag2++;
        }
        if(flag==3 || flag2==3)
            return true;
    }
    return false;    
}

void play(char *filename){
    char board[N][N];
    bool stop = false;
    readBoard(board, filename);
    int sum = countEnemy(board);
    printf("*** The Three Musketeers Game ***\nTo make a move, enter the location of the piece you want to move,\n");
    printf("and the direction you want it to move. Locations are indicated as\na letter (A, B, C, D, E) followed by a nnumber (1, 2, 3, 4, or 5).\n");
    printf("Directions are indicated as left, right, up, down (L/l, R/r, U/u, D/d).\nFor example, to move the Musketeer from the top right-hand corner\n");
    printf("to the row below, enter 'A,5 = L' or 'a,5=l'(without quotes).\nFor convenience in typing, use lowercase letters.\n\n\n");
    display_board(board);
    
    char *character = (char *)malloc(20 * sizeof(char));
    if (character == NULL) {
        perror("Memory allocation failed.\n");
        exit(-1); 
    }
    int l=0;
    int temp=0;
    while(!stop && !winEnemy(board)){
        if(!winMusketeer(board) && sum!=0 && temp<1 && l%2!=0){
            temp++;
            l++;
            playCharacter(board, "enemy", &stop, &sum);
        }
        else if(temp>=1 && !winMusketeer(board)){
            stop = true;
        }
        else if(!winMusketeer(board))
            stop=true;
        else{
            temp=0;
            if(l%2==0){
                strcpy(character, "Musketeer");
            }
            else{
                strcpy(character, "enemy");
            }
            playCharacter(board, character, &stop, &sum);
            l++;
        }
    }
    if(!winMusketeer(board)){
        printf("The Musketeers win!\n");
    }
    if(winEnemy(board)){
        printf("Cardinal Richelieu's men win!\n\n");
    }
    char *str1 = "out-";
    char *file = malloc(strlen(str1) + strlen(filename) + 1);
    if (file == NULL) { // Check if memory allocation was successful
        perror( "Memory allocation failed.\n");
        exit(-1);
    }
    strcpy(file, str1);
    strcat(file, filename);
    writeBoard(board, file);
}