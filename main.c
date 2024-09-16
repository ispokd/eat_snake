#include"base.h"
/*
̰���ߣ�
һ���ߣ������ɶ���ڵ���ɣ��Ե�ʳ���������
ÿ��һ��ʱ���ƶ�һ��

ʵ��˼·��
ʹ��һ������洢������ڵ����ݣ����꣩��
ͬʱ��¼����ĳ��ȣ���Ҫ֪���ٶȣ�����
����ѭ����
��ʼ�ձ����ƶ��������ٶȣ�ÿ��һ��ʱ�䳯��ǰ�ĳ���һ��
����β�Ϳ�ʼÿ���ڵ㸳ֵΪǰһ���ڵ��λ�ã�ͷ�������㣩
���ƶ���Ҫ�����û�а�������������У����ݰ������޸ĳ���
ͬʱҪ����Ƿ������ײǽ��ײ�Լ���
*/


/*
��������_getch()
*/
#define KEY_FLAG  224  //��Ǵ����˷����
#define KEY_UP    72   //��
#define KEY_RIGHT 77   //��
#define KEY_DOWN  80   //��
#define KEY_LEFT  75   //��


/*
��������
0��1��2��3��
*/
#define TO_UP      0
#define TO_RIGHT   1
#define TO_DOWN    2
#define TO_LEFT    3


/*
�߽ṹ
*/
typedef struct _SNAKE
{
	COORD body[100];//����ṹ����
	int length;     //��ǰ�ߵĳ���
	int speed;      //��ǰ�ߵ��ٶ�
	int direct;     //��ǰ�ߵĳ���
}SNAKE;



/*
������Ϸ����
*/
void printf_table()
{
	set_color(0x01);
	printf("��");
	for (int i = 0; i < 100 ;i++)
	{
		printf("��");
	}
	printf("��\n");
	for (int i = 0; i < 30; i++)
	{
		printf("��");
		for (int j = 0; j < 100; j++)
		{
			printf(" ");
		}
		printf("��\n");
	}
	printf("��");
	for (int i = 0; i < 100; i++)
	{
		printf("��");
	}
	printf("��\n");
	set_color(0x07);
}

/*
���߽��г�ʼ�������ߵĳ��򣬳��ȣ��ٶȣ�����������
*/
void init_snake( SNAKE* p,int len,int speed) 
{
	p->direct = TO_RIGHT;//Ĭ�����ǳ����ұ��˶�
	p->length = len;//Ĭ�ϳ���Ϊ5�����������д���
	p->speed = speed;//Ĭ���ٶ�Ϊ300�����������д���
	for (int i = 0; i < len; i++)
	{
		p->body[i].X = (len - i)*2;
		p->body[i].Y = 1;
	}
}

/*
�ߵ��ƶ�����
*/
void move_once(SNAKE* p)
{
	//����ͷ֮�⣬ʣ�µ�����ڵ���ǰһ���ڵ�����
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
����Ļ�ϴ�ӡ���ߵ�����
*/
void printf_snake(SNAKE* p)
{
	for (int i = 0; i < p->length; i++)
	{
		if (i == 0)
		{
			set_color(0x0c);//������ͷΪ��ɫ
     	}
		else if (i ==p->length - 1)
		{
			set_color(0x0d);//������βΪ��ɫ
		}
		gotoxy(p->body[i].X, p->body[i].Y);
		printf("��");//��������
		set_color(0x07);//���ó���ͷ����β��������ɫΪ��ɫ
	}
}


/*
��ÿһ�λ�����ǰ������֮ǰ���������
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
����Ƿ�ײǽ����Ϸ����
*/
int check_game(SNAKE* p)
{
	if (p->body[0].X == 0 || p->body[0].Y == 0 || p->body[0].X == 102 || p->body[0].Y == 31)
	{
		return 1;
	}
}
/*
��ʼ���ƶ�������������ʱ����0������Ϸ������ײǽ��ײ�Լ���ʱ����1
*/
int snake_moving(SNAKE* p)
{
	while (1)
	{
		if (_kbhit())//�а���
		{
			break;
		}
		//�ƶ�ǰ����������
		clear_snake(p);
		//�ƶ�һ�Ρ�
		move_once(p);
		//����һ�Ρ�
		printf_snake(p);
		//���̼���Ƿ�ײǽ
		if (check_game(p)==1)
		{
			return 1;

		}
		//��Ϣһ�ᡣ
		Sleep(p->speed);
		}
	return 0;
}

int main()
{
	SNAKE snake = { 0 };
	//���ع��
	show_cursor(0);
	modify_wnd(103, 33);//����ϣ�һ������ڵ�ռ�������λ��
	printf_table();//���Ʊ߿�
	init_snake(&snake,25,300);//��ʼ���ߵ�����
	printf_snake(&snake);
	

	while (1)
	{
		//ʼ�ս����ߵ��ƶ�����ײǽ/�Լ�ʱ������Ϸ
		if (snake_moving(&snake) == 1) 
		{
			break;
		}
		//�ڴ˽��а������
		int key = _getch();
		if (key == KEY_FLAG)
		{
			key = _getch();
		}


		switch (key)//���ݰ����Է�������е���
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