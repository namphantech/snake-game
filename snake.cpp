#include<iostream>
#include<Windows.h>
#include"config.h"
#include<conio.h>
#include<fstream>

using namespace std;
typedef enum Direction{LEFT, RIGHT, UP, DOWN}direction;

typedef struct coordinate {
	uint32_t x;
	uint32_t y;
}coord;
struct food {
	coord coord_food;
};
struct Snake {
	coord body[40];
	int32_t length;
	direction status_dir;
	coord tail;
};
Snake snake_obj;
food food_obj;
int32_t score = 0;

void showStartGame();
void play();
void help();
void initGame(Snake& snake_obj, food& food_obj);
int  collision(Snake& snake_obj, food& food_obj, int32_t& score);
void draw_wall(void);
void move(Snake& snake_obj);
void snake(Snake &snake_obj,food &food_obj);


int main()
{
	
	ShowCur(false);
	//srand(time(NULL));
	showStartGame();
	switch (_getch())
	{
	case 'z':
		system("cls");
		// ham chinh
		
		play();
		break;
	case 'h':
		system("cls");
		help();
		system("cls");
		main();

		
		break;
	case 'q':
		system("cls");
		break;
	default:
		system("cls");
		main();

	}
	
	
}

void showStartGame()
{
	char word;
	ifstream iFile("menu.txt");
	word = iFile.get();
	while (iFile)
	{

		cout << word;
		word = iFile.get();
	}
	iFile.close();
}
void help()
{
	char word;
	ifstream iFile("help.txt");
	word = iFile.get();
	while (iFile)
	{

		cout << word;
		word = iFile.get();
	}
	iFile.close();

	_getch();

}
void play()
{
	srand(time(NULL));
	initGame(snake_obj, food_obj);
	draw_wall();
	//int check;
	int time_sleep = 180;
	
	
	while (1)
	{ 
		move(snake_obj);

		snake(snake_obj, food_obj);
		if (collision(snake_obj, food_obj, score) == 2)
		{
			gotoXY(40, 31);
			cout << "YOUR SCORE:";
			cout << score;

			break;

		}
	    
	
		
		Sleep(time_sleep);

	}
	
	
}
void initGame(Snake& snake_obj, food& food_obj)
{
	snake_obj.body[0].x = 1;
	snake_obj.body[0].y = 1;
	snake_obj.length = 1;

	food_obj.coord_food.x = 5;
	food_obj.coord_food.y = 5;
	snake_obj.status_dir = RIGHT;
	
	

}

void draw_wall()
{
	//system("cls");
	SetColor(10);
	uint16_t i;
	
	for (i = 1; i < 50; ++i)
	{
		gotoXY(i, 0); printf("%c", 196);
		gotoXY(i, 30); printf("%c", 196);
	}
	for (i = 0; i < 30; ++i)
	{
		gotoXY(0, i); printf("%c", 179);
		gotoXY(50, i); printf("%c", 179);

	}
	gotoXY(0, 0); printf("%c", 218);
	gotoXY(50, 0); printf("%c", 191);
	gotoXY(0, 30); printf("%c", 192);
	gotoXY(50, 30); printf("%c", 217);
	gotoXY(0, 31); cout << "Developed by Nam Phan";
	
	
}

void move(Snake& snake_obj)
{
	ShowCur(false);
	snake_obj.tail.x = snake_obj.body[snake_obj.length - 1].x;
	snake_obj.tail.y = snake_obj.body[snake_obj.length - 1].y;
	
	uint16_t i;
	for (i=snake_obj.length - 1; i > 0; --i) // cái ni quan trọng nha, cái ni giống đầu răn di chuyển thì thân di chuyển thôi
	{
		snake_obj.body[i] = snake_obj.body[i - 1];
	}
	if (_kbhit())
	{
		    char  key = _getch();
		
			if (key == 'a')
				snake_obj.status_dir = LEFT;
			else if (key == 'd')
				snake_obj.status_dir = RIGHT;
			else if (key == 'w')
				snake_obj.status_dir = UP;
			else if (key == 's')
				snake_obj.status_dir = DOWN;
		
	}

	if (snake_obj.status_dir == UP)
		snake_obj.body[0].y--;
	else if (snake_obj.status_dir == DOWN)
		snake_obj.body[0].y++;
	else if (snake_obj.status_dir == LEFT)
		snake_obj.body[0].x--;
	else if (snake_obj.status_dir == RIGHT)
		snake_obj.body[0].x++;

//	return snake_obj.body[snake_obj.length - 1];
}
int collision(Snake& snake_obj, food& food_obj,int32_t &score)
{
	ShowCur(false);
	
	if (snake_obj.body[0].x < 0 || snake_obj.body[0].x >= 49 ||
		snake_obj.body[0].y < 0 || snake_obj.body[0].y >= 30)
		return 2;

	for (int i = 1; i < snake_obj.length; ++i)
		if (snake_obj.body[0].x == snake_obj.body[i].x &&
			snake_obj.body[0].y == snake_obj.body[i].y)
			return 2;

		
	if (snake_obj.body[0].x == food_obj.coord_food.x && snake_obj.body[0].y == food_obj.coord_food.y)
	{
		++score;
		snake_obj.length++;
		
		food_obj.coord_food.x = rand() % 49 +1;
		food_obj.coord_food.y = rand() % 29 +1;
		
	}
	
	return 0;
}
void snake(Snake &snake_obj,food &food_obj)
{
	//system("cls");
	uint16_t i;
	SetColor(4);
	gotoXY(food_obj.coord_food.x, food_obj.coord_food.y);
	putchar('o');

	SetColor(10);
	
	for (i = 0; i < snake_obj.length; ++i)
	{
		gotoXY(snake_obj.body[i].x, snake_obj.body[i].y);
		putchar(254);
		
	}
	gotoXY(snake_obj.tail.x, snake_obj.tail.y);
	cout << " ";
	
}
