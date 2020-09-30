#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/**
 * Including the header files of C
 */
int row,column,number; //global variables
char copy[9][9];// global array variable
int main()
{
         FILE *fp ;//creating file pointer
         char data[50],name[50];char solution[9][9],puzzel[9][9];int i=0,ch,counter=1;//local variables
         printf("**************************WELCOME TO 'The Sudoku Game'**************************\n\n");
         printf("PLEASE ENTER YOUR NAME : ");
         gets(name);//takes in the players name
         printf("\nHELLO , Mr./Mrs. %s ,\n\n",name);//greets the player
         printf("I am Sudokuto.I am basically the Sudoku Game Generator System.\n\n");//gives introduction of the system
         while(1)
         {
             /**
               *Choose the files based upon the number of turns
               */
             if(counter==1)
             fp = fopen( "numbers.txt", "r" ) ;
             else if(counter==2)
             fp = fopen( "numbers1.txt", "r" ) ;
             else if(counter==3)
             fp = fopen( "numbers2.txt", "r" ) ;
             else if(counter==4)
             {
             fp = fopen( "numbers3.txt", "r" ) ;
             counter=0;
             }
             counter++;
             if ( fp == NULL )
             {
                     printf("\n\n\nERROR!!!Cannot find the solution files!!!\n\n\n" ) ;//if the file is not found it displays the error message
                     return 1;
             }
             i=0;
             refreshGrid(solution);//creates a fresh sudoku puzzel free from elements
             while( fgets ( data, 50, fp ) != NULL )
             {
                  gridFormation(solution,data,i);//forms the solution of the sudoku puzzel
                  i++;

             }
             menu();//displays the menu
             printf("ENTER YOUR CHOICE FROM THE MENU : ");
             scanf("%d",&ch);//takes the choice from the player
             copyPuzzel(puzzel,solution);//makes up the copy of the solution
             sudokuGenerator(puzzel);//takes in the copy of the solution and randomly generates a sudoku puzzel
             switch(ch)
             {
             case 1:
                 /**
                  * displays the rules of the game and starts the sudoku game
                  */
                 printf("\n\nDESCRIPTION AND RULES : \n\n");
                 printf("The Classic Sudoku is a number placing puzzle based on a 9x9 grid with several given numbers. The object is to place the numbers 1 to 9 in the empty squares so that each row, each column and each 3x3 box contains the same number only once.\n\nSudoku puzzles come in endless number combinations and range from very easy to extremely difficult taking anything from five minutes to several hours to solve. Sudoku puzzles also come in many variants, each variant looking differently and each variant offering a unique twist of brain challenging logic.\n\nHowever, make one mistake and you’ll find yourself stuck later on as you get closer to the solution… Try these puzzles, and see if you can solve them too!\n\nEach puzzle consists of a 9x9 grid containing given clues in various places. The object is to fill all empty squares so that the numbers 1 to 9 appear exactly once in each row, column and 3x3 box.\n\n");
                 newPuzzel(puzzel,solution);
                 break;
             case 2:
                 /**
                  *terminates the game
                  */
                 fclose(fp) ;//closes the file
                 exit(0);//exits the game
                 break;
             default:
                 printf("ENTER VALID OPTION!!!");//display appropriate message for entering wrong option
             }
         }
         return 0;
}

void copyPuzzel(char puzSudoku[][9],char solSudoku[][9])
{
    /**
     * Copies the solution
     */
    int i,j;//local variables
    for(i=0;i<9;i++)
    {//outer loop
        for(j=0;j<9;j++)
        {//inner loop
            puzSudoku[i][j]=solSudoku[i][j];//copies element cell by cell
        }
    }
}

void newPuzzel(char puzSudoku[][9],char solSudoku[][9])
{
    /**
     * Here the solving of puzzel,deletion of element
     * or solution of the puzzel's operations are done
     */
    int flag=1,option,i,j,value,c,r;//local variables
    display(puzSudoku,9);//displays the puzzel
    while(flag!=0)
   {
   loop:
    printf("1. SOLVE \n");
    printf("2. SOLUTION\n");
    printf("3. DELETE\n");
    printf("ENTER OPTION : ");
    scanf("%d",&option);
    if(option==1)
    {
     solve(puzSudoku);//to solve the puzzel
    }
    else if(option==2)
    {
     solutionMethod(solSudoku);//to get the solution of the puzzel
     break;
    }
    else if(option==3)
    {
        printf("\n\nENTER THE CELL TO DELETE : \n");
        printf("THE ROW : ");
        scanf("%d",&r);//enter the row
        printf("THE COLUMN : ");
        scanf("%d",&c);//enter the column
        deleteNumber(puzSudoku,r,c);//delete a number from cell
    }
    else
    {
        printf("WRONG OPTION!!!\n\n");//displays appropiate message
        goto loop;//goes back to the staring of loop
    }
    /**
     * Checks whether the puzzel is solved or not
     */
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(puzSudoku[i][j]==' ')
            {
                flag=1;//if it finds a blank cell it will stop checking and go back to the start of loop
                break;
            }
            else
                flag=0;//if its complete then it will check with correct solution
        }
       if(flag==1)
       {
           break;//comes out of while loop
       }
     }
    }
    if (option!=2)
    {
    value=sudokuChecker(puzSudoku,solSudoku);//returns whether the solved sudoku is correct or not
    if(value==0)
    {//for incorrect sudoku
        printf("\n\nTHE SUDOKU YOU HAVE SOLVED IS WRONG\n\n");
        printf("THE CORRECT SOLVED SUDOKU : \n");
        solutionSudoku(solSudoku);//displays the solution
    }
    else
    {//for correct sudoku
        printf("\n\nCONGRATULATION!!!YOU HAVE SOLVED THE SUDOKU CORRECTLY\n\n");
        solutionSudoku(solSudoku);//displays the solution
    }
    }
}


void deleteNumber(char puz[][9],int r,int c)
{
    /**
     * Delete a number from a particular cell
     */
    if(copy[r-1][c-1]==' '&&puz[r-1][c-1]==' ')
    {
        printf("\n\nTHE CELL IS ALREADY EMPTY!!!\n\n");//cannot delete an empty cell
    }
   else if(copy[r-1][c-1]==' ')
   {
       puz[r-1][c-1]=' ';
       printf("\nUPDATED SUDOKU : \n\n");//deletes a number from the cell
       display(puz,9);
   }
   else
   {
       printf("\n\nERROR!!!CANNOT DELETE PREDEFINED VALUE.\n\n");//cannot delete a predefined value
   }
}

int sudokuChecker(char puz[][9],char sol[][9])
{
    /**
     * Checks whether the solved sudoku is correct or not
     */
    int i,j;//local variables
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            if(puz[i][j]!=sol[i][j])//checks the elements cell by cell
            {
                return 0;//means the solved sudoku is incorrect
            }
        }
    }
    return 1;//means the solved sudoku is correct
}

void solve(char puzSudoku[][9])
{
    /**
     * Takes a number and put it in a cell
     */
    inputNumber();//inputs the number and the cell position from user
    if(puzSudoku[row-1][column-1]==' ')
    {
        puzSudoku[row-1][column-1]=number+'0';//puts the number in the cell
        printf("\nUPDATED SUDOKU : \n\n");
        display(puzSudoku,9);//displays the updated sudoku
    }
    else
    {
        printf("\n\nTHE PLACE IS ALREADY FILLED BY A NUMBER!!!\n\n");//it displays appropriate message if cell is blocked
    }
}

void solutionSudoku(char matrix[][9])
{
    /**
     * Displays the solution of the sudoku
     */
    printf("THE SOLUTION OF THE ABOVE SUDOKU IS AS FOLLOWS : \n\n\n");
    display(matrix,9);//displays the solution
}

void solutionMethod(char matrix[][9])
{
    /**
     * Checks the solution of the sudoku
     */
    printf("\n\nNEVERMIND,TRY AGAIN NEXT TIME.\n\n");
    solutionSudoku(matrix);//gets the solution of the sudoku puzzel
}

void menu()
{
    /**
     * Displays the menu
     */
    printf("\n\n***********************MENU************************\n");
    printf("* 1. NEW       (To create a new 9x9 Sudoku puzzel)*\n");
    printf("* 2. QUIT      (To terminate the Sudoku Game)     *\n");
    printf("***************************************************\n\n");
}

void inputNumber()
{
    /**
     * Inputs the number and cell position
     */
    loop:
    printf("\n\nENTER THE CELL : \n");
    printf("THE ROW : ");
    scanf("%d",&row);//inputs the row position of the cell
    printf("THE COLUMN : ");
    scanf("%d",&column);//inputs the column position of the cell
    while(1)
    {
    printf("ENTER THE NUMBER : ");
    scanf("%d",&number);//inputs the number in the cell
    if(!(number>0&&number<10))
    {
        printf("ENTER THE NUMBER BETWEEN 1 AND 9\n\n");
        continue;
    }
    else
        break;
    }
    if((!(row>0&&row<10))||(!(column>0&&column<10)))
    {
        printf("\n\nNO SUCH CELL IS PRESENT!!!\n\n");//it displays appropriate message if cell is blocked
        goto loop;//goes back to the starting of this method
    }
}

void sudokuGenerator(char matrix[][9])
{
    /**
     * Inputs the number and cell position
     */
    int i,j,r;char c;//local variables
    srand(time(NULL));//sets the seed of the random number generator algorithm with different sequence
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
          r=rand()%2;//gets 1 for odd and 0 for even number generated
          c=matrix[i][j];//gets the current value of the cell
          c=r==1?c:' ';//chnages the value of the cell depending on 1 and 0 creating a random blank space
          matrix[i][j]=c;//changes the value of the cell
          copy[i][j]=c;//creates a copy
        }
    }
}

void refreshGrid(char ar[][9])
{
    /**
     * Refreshes the grid
     */
    int i,j;//local variables
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            ar[i][j]='\0';//cleans the cells of the puzzel and creates a clean grid
        }
    }
}

void gridFormation(char ar[][9],char s[],int i)
{
    /**
     * Forms the grid from the array of numbers extracted from the file
     */
     int j,k=0;//local variables
     for(j=0;j<9;)
     {
         if(s[k]!=',')
         {
         ar[i][j]=s[k];//extracts the value from the array of numbers and places in the grid cells one by one
         j++;
         }
         k++;
     }
}

void display(char matrix[][9],int size)
{
    /**
     * Displays the sudoku puzzel
     */
    int i,j,counter,contr=0;char c=' ';//local variables
    printf("   ");
    for(j=0;j<size;j++)//loop for designing
    {
    printf("  C%d",j+1);//creates the C1,C2,C3 and so on
    }
    printf("\n   ");
    for(j=0;j<size;j++)//loop for designing
    {
    printf("----");
    }
    printf("\n");
    for(i=0;i<size;i++)
    {
        printf("R%d",i+1);//creates the R1,R2,R3 and so on
        counter=0;
        for(j=0;j<size;j++)
        {

        c=matrix[i][j];//takes the value of the current cell
        if(counter==3)
        {
            if(j>0&&j<size-1)
            {
            printf(" | %c",c);//prints the character number or blank
            }
            counter=0;
        }
        else
        printf("   %c",c);//prints the character number or blank
        counter++;
        }
        printf("   \n");
        printf("   ");
        if(contr==2)
        {
        for(j=0;j<size;j++)//loop for designing
        {
        printf("----");
        contr=-1;
        }
        }
        contr++;
        printf("\n");
    }
}
