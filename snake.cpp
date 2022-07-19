#include<iostream>
#include<Windows.h>
#include"config.h"
#include<conio.h>
#include<fstream>



using namespace std;
typedef enum Direction{UP, DOWN, LEFT, RIGHT}direction;

typedef struct coordinate {
	uint32_t x;
	uint32_t y;
}coord;
struct food {
	coord coord_food;
};
struct Snake {
	coord body[20];
	uint32_t length;
	direction status_dir;
};
Snake snake_obj;
food food_obj;
int time_sleep = 300;
void showStartGame();
void play();
void help();
void initGame(Snake& snake_obj, food& food_obj);
int collision(Snake& snake_obj, food& food_obj,int &time_sleep);
void display(Snake snake_obj, food food_obj);
void move(Snake& snake_obj);
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
	//int check;
	
	
	while (1)
	{
		
		move(snake_obj);
		system("cls");
		display(snake_obj, food_obj);
		
	    collision(snake_obj, food_obj,time_sleep);
	// chưa check va chạm nha
		
		Sleep(time_sleep);

	}
	gotoXY(0, 40);
	
}
void initGame(Snake& snake_obj, food& food_obj)
{
	snake_obj.body[0].x = 0;
	snake_obj.body[0].y = 0;
	snake_obj.length = 1;

	food_obj.coord_food.x = 5;
	food_obj.coord_food.y = 5;
	snake_obj.status_dir = RIGHT;
	
	

}

void display(Snake snake_obj, food food_obj)
{
	//system("cls");
	//SetColor(10);
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
	
	SetColor(4);
	gotoXY(food_obj.coord_food.x, food_obj.coord_food.y);
	putchar('o');

	SetColor(10);
	gotoXY(snake_obj.body[0].x, snake_obj.body[0].y);
	putchar(2);
	for (i = 0; i < snake_obj.length; ++i)
	{
		gotoXY(snake_obj.body[i].x, snake_obj.body[i].y);
		putchar(254);

	}


}
void move(Snake& snake_obj)
{
	ShowCur(false);
	uint16_t i;
	for (i=snake_obj.length - 1; i > 0; --i) // cái ni quan trọng nha, cái ni giống đầu răn di chuyển thì thân di chuyển thôi
	{
		snake_obj.body[i] = snake_obj.body[i - 1];
	}
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'A' || key == 'a')
			snake_obj.status_dir = LEFT;
		else if (key == 'D' || key == 'd')
			snake_obj.status_dir= RIGHT;
		else if (key == 'W' || key == 'w')
			snake_obj.status_dir = UP;
		else if (key == 'S' || key == 's')
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

}
int collision(Snake& snake_obj, food& food_obj,int &time_sleep)
{
	ShowCur(false);
	if (snake_obj.body[0].x < 0 || snake_obj.body[0].y >= 50 ||
		snake_obj.body[0].y < 0 || snake_obj.body[0].y >= 29)
		return -1;

	for (int i = 1; i < snake_obj.length; ++i)
		if (snake_obj.body[0].x == snake_obj.body[i].x &&
			snake_obj.body[0].y == snake_obj.body[i].y)
			return -1;

	if (snake_obj.body[0].x == food_obj.coord_food.x && snake_obj.body[0].y == food_obj.coord_food.y)
	{
		for (int i = snake_obj.length; i > 0; --i)
			snake_obj.body[i] = snake_obj.body[i - 1];
		snake_obj.length++;
	

		food_obj.coord_food.x = rand() % 50;
		food_obj.coord_food.y = rand() % 30;
		if (time_sleep > 50)
			time_sleep -= 20;
		
	}

}