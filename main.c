#include"base.h"
/*
贪吃蛇：
一条蛇（身体由多个节点组成，吃到食物，长度增加
每隔一段时间移动一步

实现思路：
使用一个数组存储蛇身体节点数据（坐标），
同时记录蛇身的长度，还要知道速度，朝向
开启循环：
蛇始终保持移动，根据速度，每隔一段时间朝当前的朝向一步
（从尾巴开始每个节点赋值为前一个节点的位置，头单独计算）
在移动中要检测有没有按键动作，如果有，根据按键来修改朝向
同时要检测是否结束（撞墙，撞自己）
*/


/*
按键交互_getch()
*/
#define KEY_FLAG  224  //标记触发了方向键
#define KEY_UP    72   //上
#define KEY_RIGHT 77   //右
#define KEY_DOWN  80   //下
#define KEY_LEFT  75   //左


/*
方向向量
0上1右2下3左
*/
#define TO_UP      0
#define TO_RIGHT   1
#define TO_DOWN    2
#define TO_LEFT    3


/*
蛇结构
*/
typedef struct _SNAKE
{
	COORD body[100];//身体结构数组
	int length;     //当前蛇的长度
	int speed;      //当前蛇的速度
	int direct;     //当前蛇的朝向
}SNAKE;



/*
配置游戏界面
*/
void printf_table()
{
	set_color(0x01);
	printf("┏");
	for (int i = 0; i < 100 ;i++)
	{
		printf("━");
	}
	printf("┓\n");
	for (int i = 0; i < 30; i++)
	{
		printf("┃");
		for (int j = 0; j < 100; j++)
		{
			printf(" ");
		}
		printf("┃\n");
	}
	printf("┗");
	for (int i = 0; i < 100; i++)
	{
		printf("━");
	}
	printf("┛\n");
	set_color(0x07);
}

/*
对蛇进行初始化，将蛇的朝向，长度，速度，都进行配置
*/
void init_snake( SNAKE* p,int len,int speed) 
{
	p->direct = TO_RIGHT;//默认总是朝向右边运动
	p->length = len;//默认长度为5，由主函数中传入
	p->speed = speed;//默认速度为300，由主函数中传入
	for (int i = 0; i < len; i++)
	{
		p->body[i].X = (len - i)*2;
		p->body[i].Y = 1;
	}
}

/*
蛇的移动设置
*/
void move_once(SNAKE* p)
{
	//除了头之外，剩下的身体节点是前一个节点坐标
	for (int i = p->length - 1; i > 0; i--)
	{
		p->body[i] = p->body[i - 1];
	}
	switch (p->direct)
	{
	case TO_UP :
		p->body[0].Y--;
		break;
	case TO_RIGHT :
		p->body[0].X+=2;
		break;
	case TO_DOWN:
		p->body[0].Y++;
		break;
	case TO_LEFT:
		p->body[0].X -= 2;
		break;

	}
}


/*
在屏幕上打印出蛇的身体
*/
void printf_snake(SNAKE* p)
{
	for (int i = 0; i < p->length; i++)
	{
		if (i == 0)
		{
			set_color(0x0c);//设置蛇头为红色
     	}
		else if (i ==p->length - 1)
		{
			set_color(0x0d);//设置蛇尾为紫色
		}
		gotoxy(p->body[i].X, p->body[i].Y);
		printf("█");//生成蛇身
		set_color(0x07);//设置除蛇头，蛇尾外其他颜色为白色
	}
}


/*
在每一次绘制蛇前，将蛇之前的身体擦除
*/
void clear_snake(SNAKE* p)
{
	for (int i = 0; i < p->length; i++)
	{
		gotoxy(p->body[i].X, p->body[i].Y);
		printf("  ");
	}
}


/*
检测是否撞墙，游戏结束
*/
int check_game(SNAKE* p)
{
	if (p->body[0].X == 0 || p->body[0].Y == 0 || p->body[0].X == 102 || p->body[0].Y == 31)
	{
		return 1;
	}
}
/*
蛇始终移动，当按键触发时返回0，当游戏结束（撞墙，撞自己）时返回1
*/
int snake_moving(SNAKE* p)
{
	while (1)
	{
		if (_kbhit())//有按键
		{
			break;
		}
		//移动前擦除旧数据
		clear_snake(p);
		//移动一次。
		move_once(p);
		//绘制一次。
		printf_snake(p);
		//立刻检测是否撞墙
		if (check_game(p)==1)
		{
			return 1;

		}
		//休息一会。
		Sleep(p->speed);
		}
	return 0;
}

int main()
{
	SNAKE snake = { 0 };
	//隐藏光标
	show_cursor(0);
	modify_wnd(103, 33);//宽度上，一个身体节点占两个输出位置
	printf_table();//绘制边框
	init_snake(&snake,25,300);//初始化蛇的数据
	printf_snake(&snake);
	

	while (1)
	{
		//始终进行蛇的移动，当撞墙/自己时结束游戏
		if (snake_moving(&snake) == 1) 
		{
			break;
		}
		//在此进行按键检测
		int key = _getch();
		if (key == KEY_FLAG)
		{
			key = _getch();
		}


		switch (key)//根据按键对方向键进行调整
		{
		case KEY_UP:
			if (snake.direct == TO_LEFT ||snake.direct==TO_RIGHT)
			{
				snake.direct = TO_UP;
			}
			break;
		case KEY_RIGHT:
			if (snake.direct == TO_UP || snake.direct == TO_DOWN)
			{
				snake.direct = TO_RIGHT;
			}
			break;
		case KEY_DOWN:
			if (snake.direct == TO_LEFT || snake.direct == TO_RIGHT)
			{
				snake.direct = TO_DOWN;
			}
			break;
		case KEY_LEFT:
			if (snake.direct == TO_UP || snake.direct == TO_DOWN)
			{
				snake.direct = TO_LEFT;
			}
			break;

		}
	}
	return 0;
	
}