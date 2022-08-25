#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score,foodSpecx,foodSpecy;
int tailX[100], tailY[100];
int nTail;
enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir,prevDir;
void Init()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    foodSpecx = rand() % width;
    foodSpecy = rand() % height;
    score = 0;
}
void Update()
{
    system("cls"); //system("clear");
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
 
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "0";
            else if (i == fruitY && j == fruitX)
                cout << "*";
            else if(nTail%4==0 && nTail>0 && i==foodSpecy && j==foodSpecx)
 			{
               	cout << "$";
			 }
            else
            {
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }
 
    for (int i = 0; i < width+2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}
void Input()
{
    if (_kbhit())
    {
        switch (getch())
        {
        	case -32:
        		break;
	        case 75:
	        	if(dir!=RIGHT)
	            	dir = LEFT;
	            break;
	        case 77:
	        	if(dir!=LEFT)
	            	dir = RIGHT;
	            break;
	        case 72:
	        	if(dir!=DOWN)
	            	dir = UP;
	            break;
	        case 80:
	        	if(dir!=UP)
	            	dir = DOWN;
	            break;
	        case 'x':
	            gameOver = true;
	            break;
	        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
 
    if (x == fruitX && y == fruitY)
    {
        score += 5;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
    else if (x == foodSpecx && y == foodSpecy)
    {
        score += 15;
        foodSpecx = rand() % width;
        foodSpecy = rand() % height;
        nTail++;
    }
}
int main()
{
    Init();
    while (!gameOver)
    {
    	Input();
    	Logic();
        Update();
        Sleep(75); //sleep(10);
    }
    return 0;
}
