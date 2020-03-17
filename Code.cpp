#include <iostream>
#include <dos.h>
#include <windows.h>

using namespace std;
char board[3][3]= {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
char turn ='X';
int row, column;
bool draw = false;

void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void display_board()
{
	system("cls");
	SetColor(1);
	cout<<"\n\n\t\t  TIC TAC TOE GAME\n\n"<< endl;
	
	SetColor(0);
	cout<<"\tPlayer 1 [X]  \n\tPlayer 2 [O]\n\n";
	
	cout<<"\t\t     |     |     \n";
	cout<<"\t\t  "<<board[0][0]<<"  |  "<<board[0][1]<<"  |  "<<board[0][2]<<"  \n";
	cout<<"\t\t_____|_____|_____\n";
	cout<<"\t\t     |     |     \n";
	cout<<"\t\t  "<<board[1][0]<<"  |  "<<board[1][1]<<"  |  "<<board[1][2]<<"  \n";
	cout<<"\t\t_____|_____|_____\n";
	cout<<"\t\t     |     |     \n";
	cout<<"\t\t  "<<board[2][0]<<"  |  "<<board[2][1]<<"  |  "<<board[2][2]<<"  \n";
	cout<<"\t\t     |     |     \n";
}

void player_turn()
{
	int choice;
	SetColor(4);		
	if(turn== 'X')
	cout <<"\n\tPlayer 1 [X] turn: ";
	if(turn== 'O')
	cout<<"\n\tPlayer 2 [O] turn: ";
	
	cin >> choice;
	
	switch(choice)
	{
		case 1: row=0; column=0; break;
		case 2: row=0; column=1; break;
		case 3: row=0; column=2; break;
		case 4: row=1; column=0; break;
		case 5: row=1; column=1; break;
		case 6: row=1; column=2; break;
		case 7: row=2; column=0; break;
		case 8: row=2; column=1; break;	
		case 9: row=2; column=2; break;	
		
		default:
		cout<<"Invalid choice\n";
		break;
	}
	if(turn=='X' && board[row][column]!='X' && board[row][column]!='O')
	{
		board[row][column]='X';
		turn='O';
	}
	else if(turn=='O' && board[row][column]!='X' && board[row][column]!='O')
	{
		board[row][column]='O';
		turn='X';
	}
	else
	{
			SetColor(5);
		cout<<"\n\tBox alreay filled !\n\tPlease try again !!\n";
		player_turn();
	}
	display_board();	
}

bool gameover()
{
	//check win
	for(int i=0; i<3; i++)
	if(board[i][0]== board[i][1] && board[i][0]== board[i][2] || board[0][i]== board[1][i] && board[0][i]== board[2][i])
	return false;	
	
	if(board[0][0]==board[1][1] && board[0][0] == board[2][2] || board[0][2]==board[1][1] && board[0][0]==board[2][0])
	return false;
	
	//if there is any box not filled
	for(int i=0; i<3; i++)
	for(int j=0; j<3; j++)
	if(board[i][j]!= 'X' && board[i][j] != 'O')
	return true;
	
	//draw
	draw = true;
	return false;
}

int main()
{
	system("color E1");	
	while(gameover())
	{
		display_board();
		player_turn();
		gameover();
	}
	SetColor(2);
	if(turn =='X' && draw == false)
	cout<< "\n\tPlayer 2 [O] Wins !! Congratulations\n";
	else if(turn =='O' && draw == false)
	cout<< "\n\tPlayer 1 [X] Wins !! Congratulations\n";
	else
	cout<<"\n\tGame Draw !! \n";

}
