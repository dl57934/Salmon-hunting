
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#define true 1
#define false 0
int startgame1(int n);
void readyforstage(int n);
int get_collided(int n);
void clear_enemies();
void draw_enemies();
void move_enemies(int now);
void create_enemy();
void textcolor(int attr);
void hidecursor();
void process_key();
void gotoxy(int x, int y);
int starting();
void point();
int star();
void initi();
void exp();
void initialize();
void init();//�ʱ⿡ ����ü�� ������ ���·� �ʱ�ȭ ��Ű�� �Լ�
long EndTime = 0;
long nStart = 0;
long nEnd = 0;
clock_t st, et; //clock_t�� st clock�� �ð� ���°� ����, et�� �ð� ��°� ���ߴ� �Լ�
void file_input(); //���α׷� ����� ����� ��ŷ�� �ҷ��� rakingboard�� ü��� �Լ�
void file_output();//���α׷��� �����Ҷ� ������ ��ŷ�� �ٽ� ���Ͽ� �����ϴ� �Լ�
int check_score(int score);//���ο� ������ ��ŷ�� ���� �ִ��� �Ǵ��ϴ� �Լ�
void rank_sort(int score, char *name);//���ο� ������ �������� ��ŷ�� �����ϴ� �Լ�
void rank_print();//��ŷ ������ ����ϴ� �Լ�


typedef struct info
{
	char *name;
	int sscore;
}Info;//������� ��ŷ ������ �� ����ü
int num = 0;//���� ��ϵ� ��ŷ�� ����
Info rankboard[10];

typedef struct {
	int type;
	int alive;
	int x, y;
	int speed;
	int _tick;
} ENEMY;

ENEMY enemies[100];
int st_x = 30;
int st_y = 18;
int y = 12;
int nConsume = 800;
int score = 0, stage = 1;
int check = 1; int i = 0;

enum {
	FISH = 1,
	FISH2,
	FISH3,
	FISH4
};

/*�����Լ� ����*/
int main(void) {
	system("color 17");//�ܼ�â �� ����
	system("mode con: cols=80 lines=26");//�ܼ�â ũ�� ����
	hidecursor();//Ŀ�������
	srand(GetTickCount());//srand�� �����Լ�
	init();
	exp();
	for (;;) {
		system("cls");
		int tem = starting();
		int a;
		if (tem == 1) {
			initialize();
			a = star();
			st = clock();
			nStart = clock();
			if (a == 1) {
				getch();
				continue;
			}
			break;
		}
		else if (tem == 2) {
			system("cls");
			file_input();
			rank_print();
			file_output();
			getch();
			continue;
			break;
		}
		else if (tem == 3)
		{
			return 0;
			break;
		}
	}
	return 0;
}//�����Լ� ����


void gotoxy(int x, int y) {
	COORD pos = { x, y };//��ǥ�� ������ ���� ����ü
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void process_key()
{
	if (_kbhit())
		/*�Է¹��ۿ� ���� ���� ���*/
	{
		gotoxy(0, y);
		printf("       ");
		switch (_getch())
			/*getch�Լ��� �����Է��� �о �ش��ϴ� �������� ��ȯ�ϴ� �Լ�*/
		{
		case'W':
		case 'w'://caps lock�� �������� ��(���� �̵�)
		//caps lock�� �������� ��(���� �̵�)
			if (--y < 0)
			{
				++y;//�����̵�
			}
			break;
		case 's'://caps lock�� �������� ��(�Ʒ��� �̵�)
		case 'S'://caps lock�� �������� ��(�Ʒ��� �̵�)
			if (++y > 23)
			{
				--y;//�Ʒ����̵�
			}
			break;
		}
	}
}

void hidecursor() {
	CONSOLE_CURSOR_INFO curInfo;

	curInfo.dwSize = 10;
	curInfo.bVisible = FALSE;

	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}//Ŀ�������

void textcolor(int attr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}//���ڻ�

void create_enemy() {
	/*ENEMY[100]������ ���� �������� ������*/
	for (int i = 0; i < 100; ++i) {
		if (!enemies[i].alive) {//enmies[i].alive=1(true)>���� ������ ��
			enemies[i].type = rand() % 4 + 1;
			enemies[i].alive = 1;
			enemies[i].x = 74;
			enemies[i].y = rand() % 24;
			enemies[i].speed = 50;
			enemies[i]._tick = 0;
			break;
		}
	}
}//���� ó�� ��ġ �� �ӵ� ����

void move_enemies(int now) {
	for (int i = 0; i < 100; ++i) {
		if (enemies[i].alive && now - enemies[i]._tick >= enemies[i].speed) {
			if (--enemies[i].x < 0) {
				gotoxy(0, enemies[i].y);
				printf("        ");
				enemies[i].alive = 0;//����
			}//���̰� x = 0�� �����Ͽ��� �� ��������� ����
			else {
				enemies[i]._tick = now;
			}
		}
	}
}//���̰� �����̴� ���� �Լ�

void draw_enemies()
{
	for (int i = 0; i < 100; ++i)
	{
		if (enemies[i].alive)//���� ��
		{
			gotoxy(enemies[i].x + 1, enemies[i].y);
			printf("       ");
			gotoxy(enemies[i].x, enemies[i].y);
			switch (enemies[i].type)
			{
			case FISH:
				textcolor(0x1b);
				printf("��+<");
				break;
			case FISH2:
				textcolor(0x1b);
				printf("��++<");
				break;
			case FISH3:
				textcolor(0x1b);
				printf("��+++<");
				break;
			case FISH4:
				textcolor(0x1b);
				printf("��++++<");
				break;
			}//���� ��� �� ������
		}
	}
}
void clear_enemies() {
	for (int i = 0; i < 100; ++i) {
		if (enemies[i].alive) {
			gotoxy(enemies[i].x, enemies[i].y);
			printf("           ");
			enemies[i].alive = 0;
		}
	}
}//���� ��� �����

int get_collided(int n) {
	for (int i = 0; i < 100; ++i) {
		if (enemies[i].alive && enemies[i].x == 2 + n && enemies[i].y == y) {
			gotoxy(enemies[i].x, enemies[i].y);
			printf("        ");
			enemies[i].alive = 0;
			return enemies[i].type;
		}
	}
	return 0;
}

void readyforstage(int n)
{
	system("cls");
	switch (n) {
	case 1:
		textcolor(0x1F);
		gotoxy(30, 6); printf("��� �¾���ϴ�.");
		gotoxy(14, 8); printf("�ʱ⿡�� ��Ȳ�� �־� ������ ������ �ʿ䰡 �����ϴ�.");
		gotoxy(10, 10); printf("��Ȳ�� �� �����ϰ� ���� ���� �ٴٷ� ���� �õ��� �ɰ� �ֳ׿�.");
		gotoxy(19, 12); printf("�� �ñ��� ����� 6��Ƽ�� ���� �Ʊ��Դϴ�.");
		gotoxy(20, 14); printf("���� ��������(���氳)���� �԰� ��ϴ�.");
		gotoxy(22, 16); printf("ps. ��Ȳ : �˿� �پ��ִ� ���� ����");
		Sleep(4000);
		point();
		break;
	case 2:
		textcolor(0x1F);
		gotoxy(30, 6); printf("��� �ڶ����ϴ�.");
		gotoxy(12, 8); printf(" ����õ���� ���� �˷���ī�� ������ �����ϰ� �ִ� ����.");
		gotoxy(9, 10); printf("���� ��ü ��� �ƴ϶� ���� ����⳪ �ö�ũ���� �԰� ��ϴ�.");
		gotoxy(15, 12); printf("�� �ñ��� ����� ��� �����, ���� ȸ���� ��ϴ�.");
		Sleep(4000);
		point();
		break;
	case 3:
		textcolor(0x1F);
		gotoxy(30, 8); printf("��� �� �ڶ�����!");
		gotoxy(20, 10); printf("���� ������ 70cm���� 1m���� �����߾��!");
		gotoxy(11, 12); printf("�� �ڶ� ����� �ڱ⺸�� ������ ���� ����⸦ �԰� ��ϴ�.");
		gotoxy(25, 14); printf("��Ȥ ��¡� �Դ´ٰ� �ϳ׿�.");
		gotoxy(26, 16); printf("�׷� �������� ���ư������?");
		Sleep(4000);
		point();
		break;
	case 4:
		textcolor(0x1F);
		gotoxy(19, 6); printf("�׸��� ����, ����õ���� ��� ���ƿԾ��!");
		gotoxy(18, 8); printf("������ ������� �ٴٿ������ �繵 �ٸ��ϴ�.");
		gotoxy(18, 10); printf("���� ����� ���� �Ƹ��ٿ� ���� ��� �ֳ׿�!");
		gotoxy(15, 12); printf("���� ����� �ֵ��̰� ��ī�Ӱ� ���Ѱ� ���� ��ϴ�.");
		gotoxy(25, 14); printf("�� �ñ⿣ �ƹ��͵� ���� �ʰ�");
		gotoxy(17, 16); printf("������ ���� ���� ���� ����� �Ž��� �����ϴ�.");
		gotoxy(22, 18); printf("������ �¾ ������ ���ư������?");
		Sleep(4000);
		point();
	}
	Sleep(1000);
}

int startgame1(int n) {
	int running = 1, started = GetTickCount(), timelimited = 40000;
	int now = 0, create_enemy_tick = 0;
	int collided;
	int prev_score = -1, score_tick = 0;
	clear_enemies();
	while (1) {
		if (n == 1) {
			textcolor(0x1A);
			gotoxy(0, y);
			printf(">+��");
		}
		else if (n == 2) {
			textcolor(0x18);
			gotoxy(0, y);
			printf(">++��");
		}
		else if (n == 3) {
			textcolor(0x18);
			gotoxy(0, y);
			printf(">+++��");
		}
		else {
			textcolor(0x1c);
			gotoxy(0, y);
			printf(">++++��");
		}
		process_key();
		now = GetTickCount();

		gotoxy(30, 24);
		textcolor(0x1f);
		printf("���ѽð�: %5.2f", (timelimited + started - now) / 1000.);


		if (stage != 4)
			if (now - started >= timelimited) {
				system("cls");
				gotoxy(3, 10);
				printf("=====================================================================");
				gotoxy(35, 12);
				printf("TIME OVER");
				gotoxy(3, 14);
				printf("=====================================================================");
				gotoxy(65, 20);
				textcolor(0x18);
				printf("press any key");
				getch();//�ƹ��ų� Ŭ���� �������� �� ���̹��� Ȯ��
				system("cls");
				initi();
				file_input();
				if (check_score(score))
				{
					char testname[20];
					textcolor(0x1B);
					gotoxy(5, 10);
					printf(">+�� >+�� >+�� >+�� >+�� >+�� >+�� >+�� >+�� >+�� >+�� >+�� >+�� >+��");
					gotoxy(15, 12);
					textcolor(0x1F);
					printf("���� ����� ���� �̸��� �Է��� �ּ���: ");
					scanf("%s", testname);
					rank_sort(score, testname);
					file_output();
				}
				return 2;
			}


		if (stage == 4) {
			et = clock();
		}//clock ����
		if (now - started >= timelimited) {
			system("cls");
			textcolor(0x1F);
			gotoxy(27, 6); printf("��� ����� ���ƽ��ϴ�.");
			gotoxy(12, 8); printf("����� ���� ����� ���� ����� �� �ڸ����� �װ� �˴ϴ�.");
			gotoxy(15, 10); printf("���� ����� ���°��� ���� �������� ���̰� �˴ϴ�.");
			gotoxy(25, 12); printf("�� �� ��� �¾�� ��ó��");
			gotoxy(12, 14); printf("������ ������� �¾ ����õ ������ �����ϰ� �ٴϰ���?");
			textcolor(0x18);
			gotoxy(65, 15); printf("press any key");
			textcolor(0x1F);
			getch();//�ƹ��ų� Ŭ���� �������� �� ���̹��� Ȯ��
			gotoxy(30, 18); printf("�׷� �׶� �ٽ� �ƿ�!");
			score = score + 2000 - ((et - st) / 100) + 400; //���� = (1~4������ �� ��� *10)+Ŭ�������� 400
			initi();
			file_input();
			if (check_score(score))
			{
				char testname[20];
				gotoxy(10, 22);
				textcolor(0x1E);
				printf("��������� ���� �̸��� �Է��� �ּ���: ");
				scanf("%s", testname);
				rank_sort(score, testname);
				file_output();
			}
			return 2;
		}


		if (score >= 100 * stage) {
			return 1;
		}

		if (now - create_enemy_tick >= 300) {
			create_enemy();

			create_enemy_tick = now;
		}

		move_enemies(now);
		draw_enemies();

		if (collided = get_collided(n)) {
			if (stage != 4 && stage == collided)
				score += 10;
			else {

				//textcolor(0x1c);
				system("cls");
				gotoxy(3, 3);
				printf("=======================================================================\n");
				gotoxy(35, 5);
				printf("GAME OVER\n");
				gotoxy(3, 7);
				printf("=======================================================================\n");
				initi();
				file_input();
				if (check_score(score))
				{
					gotoxy(10, 15);
					printf("��������� ���� �̸��� �Է��� �ּ���: ");
					char testname[20];
					scanf("%s", testname);
					rank_sort(score, testname);
					file_output();
				}
				return 2;
			}
		}
		if (score != prev_score && now - score_tick >= 50) {
			gotoxy(50, 24);
			textcolor(0x1f);
			printf("stage : %4d  score:%4d ", stage, ++prev_score);
			score_tick = now;
		}
		Sleep(5);
	}
}

int starting() {
	while (1) {
		gotoxy(st_x, st_y);
		printf(">+��");
		textcolor(0x1F);
		gotoxy(1, 1);          printf(" ============================================================================ \n");
		gotoxy(1, 2);          printf("��     >                                    ��                              ��\n");
		gotoxy(1, 3);          printf("��       >                                  ����                            ��\n");
		gotoxy(1, 4);          printf("��        >>                                ��������                        ��\n");
		gotoxy(1, 5);          printf("��          >>    ��      ��       ��       ������������                    ��\n");
		gotoxy(1, 6);          printf("��             >>=��======��====== ��====== ����������������                ��\n");
		gotoxy(1, 7);          printf("��          >>    ��      ��       ��       ������������   ��    ����       ��\n");
		gotoxy(1, 8);          printf("��        >>     ��=��  ==��              ����������       ��====����==     ��\n");
		gotoxy(1, 9);          printf("��      >       ��   �� ==��     ��=��    ������           ��    ����       ��\n");
		gotoxy(1, 10);         printf("��    >          ��=��    ��    ��   �� ==������====��  �� ��====����       ��\n");
		gotoxy(1, 11);         printf("��                      ��       ��=��    ��  ��    ��==��    �� = ��       ��\n");
		gotoxy(1, 12);         printf("��                      ��====            ��  ��====��  ��   �� >+����      ��\n");
		gotoxy(1, 13);         printf("��                                        ��      ==== ��     �� = ��       ��\n");
		gotoxy(1, 14);         printf("��                                                     ��                   ��\n");
		gotoxy(1, 15);         printf("��                                                     ��                   ��\n");
		gotoxy(1, 16);         printf("��                         ��======================��                       ��\n");
		gotoxy(1, 17);         printf("��                         ��                      ��                       ��\n");
		gotoxy(1, 18);         printf("��                         ��     1. ���� ����     ��                       ��\n");
		gotoxy(1, 19);         printf("��                         ��     2. ��ŷâ        ��                       ��\n");
		gotoxy(1, 20);         printf("��                         ��     3. ����          ��                       ��\n");
		gotoxy(1, 21);         printf("��                         ��                      ��                       ��\n");
		gotoxy(1, 22);         printf("��                         ��======================��                       ��\n");
		gotoxy(1, 23);         printf("��                    Ű���� W(w) : ���� /  S(s) : �Ʒ���                   ��\n");
		gotoxy(1, 24);         printf(" ============================================================================ \n");

		if (_kbhit()) {
			gotoxy(st_x, st_y);
			printf("      ");

			switch (_getch())
			{
			case 'w':
			case 'W':
				if (--st_y < 18)
				{
					++st_y;
				}
				break;
			case 's':
			case 'S':
				if (++st_y > 20)
				{
					--st_y;

				}
				break;
			case 13:
				if (st_y == 18)
					return 1;
				else if (st_y == 19)
					return 2;
				else if (st_y == 20)
					return 3;
			}
		}

	}
}

void point() {
	textcolor(0x1E);
	gotoxy(27, 20);
	printf("�����������0%%");
	Sleep(500);          //0.5�� ���
	gotoxy(27, 20);
	printf("�����������10%%");
	Sleep(1000);//1�ʴ��
	gotoxy(27, 20);
	printf("�����������20%%");
	Sleep(100); //0.1�ʴ��
	gotoxy(27, 20);
	printf("�����������30%%");
	Sleep(100);//0.1�ʴ��
	gotoxy(27, 20);
	printf("�����������40%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("�����������50%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("�����������60%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("�����������70%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("�����������80%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("�����������90%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("�����������100%%");
	Sleep(500);
	gotoxy(27, 20);
	printf("�����������100%%");
}

int star() {
	int run;
	i = 0;
	stage = 1;
	do {
		readyforstage(stage);
		system("cls");
		run = startgame1(stage);
		stage++;
		i++;
		if (run == 2)
			return 1;//���α׷� �������� �ƴ�
	} while (run && stage <= 4);
}
void init()
{
	printf("\n"
		" =================================================================>+��======= \n"
		"��                                                                          ��\n"
		"��");
	textcolor(0x1F);
	printf("                          ÷����(Chum Salmon)                           ");
	textcolor(0x17);
	printf("  ��\n"
		"��                                                                          ��\n"
		"��              ���ؾ����� ȸ���� ���� ������� ��ǥ���� ������             ��\n"
		"��     ��� ����õ, ��ô ����õ, ������, ������ ������ ���ȸ���ϴ� ���̴�. ��\n"
		"��                                                                          ��\n"
		"��                                                                          ��\n"
		"��                             ����Ⱑ �Ǹ�,                               ��\n"
		"��               ���� ���� ȥ�λ��� ��Ÿ���� ���� Ư¡�̴�.                 ��\n"
		"��                                                                          ��\n"
		"��                  �ڽ��� �¾�� ��õ���� �ٽ� ���ƿ�                    ��\n"
		"��           �ƹ� �͵� ���� ���� ä ������ �Ž��� ����� �ö��             ��\n"
		"��                    ���� ����, ����� ���� �״´�.                        ��\n"
		"��                                                                          ��\n"
		"��                 ����, ��� ����õ���� ��� �¾��.                   ��\n"
		"��                 ��� �ٽ� �������� ���ƿ� �� �ֵ���                    ��\n"
		"��               ������ �츮�� ��� �ٸ� ��� �̲��� ����.                ��\n"
		"��                                                                          ��\n"
		"��                                                                          ��\n"
		"��                ������ �� �˰� �����ø�?   Press any key!                 ��\n"
		"��                                                                          ��\n"
		"��                                                                          ��\n"
		" ===============>+��=========================================================\n");
	_getch();
	system("cls"); //����-���ص� ���� / ���ص� ���� - �˷���ī�� ������ / ������-���� / ���� - ����õ
}
void exp() {
	printf("\n"
		" ===============================================================>++��======== \n"

		"��");
	textcolor(0x1F);
	printf("                              < ���� ��� >                               ");
	textcolor(0x17);
	printf("��\n"
		"��                                                                          ��\n"
		"��                  Ű���� W(w) : ��� ���� �����Դϴ�.                   ��\n"
		"��                 Ű���� S(s) : ��� �Ʒ��� �����Դϴ�.                  ��\n"
		"��                                                                          ��\n"
		"��");
	textcolor(0x1F);
	printf("                             < ���� ��Ģ >                                ");
	textcolor(0x17);
	printf("��\n"
		"��                                                                          ��\n"
		"��         - ����� �ݴ������� ���� ����Ⱑ �浹�� ���̸� �Ծ��!!         ��\n"
		"��                                                                          ��\n"
		"��            - �ڱ⺸�� ū ����⸦ ������ ��Ƹ����� �׾��!!             ��\n"
		"��                                                                          ��\n"
		"��         - �ڱ⺸�� ���� ����⸦ ������ �谡 �� ������ �׾��!!          ��\n"
		"��                                                                          ��\n"
		"��                         - ���� �ð��� 40��!                              ��\n"
		"��         �� �ȿ� ��� ������ �̻��� ���̸� �� �������� �׾��!!         ��\n"
		"��                                                                          ��\n"
		"��           - ������ 4����� ��� ������ �ö���� �ñ�!                ��\n"
		"��      �� �� ����� �ƹ��͵� ���� �����Ƿ� ���̸� �԰ԵǸ� �׾��!!        ��\n"
		"��                                                                          ��\n"
		"��                                                                          ��\n"
		"��                   �޴� ȭ������ ���÷���~    Press any key!              ��\n"
		"��                                                                          ��\n"
		" =====>+��===================================================================\n");
	_getch();
	system("cls");
}
void initialize() {
	stage = 1;
	score = 0;
	clear_enemies();
	system("color 17");
}
void initi()
{
	for (int i = 0; i < 10; i++)
	{
		rankboard[i].name = "";
		rankboard[i].sscore = 0;
	}
}
void file_input()
{
	FILE * input = fopen("ranking.txt", "r");//Input �̶�� FILE ��ü�� = ranking�̶�� txt������ �б� ���� �о� ���� �� �ʱ�ȭ �Ѵ�.
	fscanf(input, "%d\n", &num);//ranking���Ͽ��� ����� ��ŷ�� ������ �ҷ��´�.
	for (int i = 0; i < num; i++)
	{
		char buff[1000];//�ؽ�Ʈ ���Ͽ��� �� ���� �ҷ��� ���ڿ��� ����, ũ��� �˳��ϰ�
		fgets(buff, 1000, input);//������ ����
		char *tok = strtok(buff, "#");//strtok �Լ��� �����ϰ� ����� ranking ������ �м��غ���
		rankboard[i].name = strdup(tok);
		tok = strtok(NULL, "#");
		rankboard[i].sscore = atoi(tok);
	}
	fclose(input);//�޸� ������ ���� ���ϰ�ü�� �Ҹ������
}
void file_output()
{
	FILE * output = fopen("ranking.txt", "w");
	//output �̶�� FILE ��ü�� = ranking�̶�� txt������ ���� ���� �о� ���� �� �ʱ�ȭ �Ѵ�.
	fprintf(output, "%d\n", num);//��ŷ������ ������ �켱 ���Ͽ� �������.
	for (int i = 0; i < num; i++)
	{
		char buff[100] = "";//���Ͽ� ������ ���ڿ��� ���� ����
		char scorebuff[100];//������ ����� ������ ���ڿ��� ��ȯ�� ����
		strcat(buff, rankboard[i].name);//strcat�Լ��� �����غ��� �ڵ� �м��غ���
		strcat(buff, "#");
		itoa(rankboard[i].sscore, scorebuff, 10);
		strcat(buff, scorebuff);
		strcat(buff, "\n");
		fputs(buff, output);//������� ���ڿ��� ���Ͽ� �����.
	}
	fclose(output);//�޸� ������ ���� ���ϰ�ü�� �Ҹ������
}
int check_score(int score)
{
	if (num == 0)
		return true;
	for (int i = 0; i <= num; i++)
	{
		if (rankboard[i].sscore < score)
			return true;
	}
	return false;
}
void rank_sort(int score, char *name)
{
	//�ΰ��� ��� ����, 10���� ��� ü���� �ִ� ���� 10���� ���� �� ������ ���� �ʾ��� ���
	//�ΰ��� ��� ������ 10���� ���� ���ο� ������ ü����� ������ ���ָ� ��.
	rankboard[9].sscore = score;
	rankboard[9].name = strdup(name);
	//���Ĺ���� ������ ������ �������ķ� ������. �ٸ��� �����غ�
	for (int i = 9; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (rankboard[i].sscore > rankboard[j].sscore)
			{
				Info tmp = rankboard[i];
				rankboard[i] = rankboard[j];
				rankboard[j] = tmp;
			}
		}
	}
	if (num < 10)
	{
		num++;
	}
	//10���� �� ���� ���� ��� ��ŷ�� ������ �Ѱ� �÷��ش�.
}
void rank_print()
{
	printf("***************************���� ����*****************************\n");
	printf("=================================================================\n");
	printf("       ����                   �̸�                   ����\n");
	printf("=================================================================\n");
	for (int i = 0; i < num; i++) {
		printf("%8d��              �̸�: %8s           ����: %5d\n", i + 1, rankboard[i].name, rankboard[i].sscore);
	}
	printf("=================================================================\n");
	printf("�޴�ȭ������ ���ư�����~ Press any key");
}
