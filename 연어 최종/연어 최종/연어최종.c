
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
void init();//초기에 구조체를 최초의 상태로 초기화 시키는 함수
long EndTime = 0;
long nStart = 0;
long nEnd = 0;
clock_t st, et; //clock_t는 st clock시 시간 세는거 시작, et시 시간 재는거 멈추는 함수
void file_input(); //프로그램 실행시 저장된 랭킹을 불러와 rakingboard를 체우는 함수
void file_output();//프로그램을 종료할때 연산한 랭킹을 다시 파일에 저장하는 함수
int check_score(int score);//새로운 점수가 랭킹에 들어갈수 있는지 판단하는 함수
void rank_sort(int score, char *name);//새로운 점수가 들어왔을때 랭킹을 정렬하는 함수
void rank_print();//랭킹 정보를 출력하는 함수


typedef struct info
{
	char *name;
	int sscore;
}Info;//사용자의 랭킹 정보가 될 구조체
int num = 0;//현재 등록된 랭킹의 갯수
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

/*메인함수 시작*/
int main(void) {
	system("color 17");//콘솔창 색 설정
	system("mode con: cols=80 lines=26");//콘솔창 크기 설정
	hidecursor();//커서숨기기
	srand(GetTickCount());//srand는 랜덤함수
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
}//메인함수 종료


void gotoxy(int x, int y) {
	COORD pos = { x, y };//좌표값 저장을 위한 구조체
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void process_key()
{
	if (_kbhit())
		/*입력버퍼에 값이 있을 경우*/
	{
		gotoxy(0, y);
		printf("       ");
		switch (_getch())
			/*getch함수는 문자입력을 읽어서 해당하는 정수값을 반환하는 함수*/
		{
		case'W':
		case 'w'://caps lock이 꺼져있을 때(위로 이동)
		//caps lock이 켜져있을 때(위로 이동)
			if (--y < 0)
			{
				++y;//위로이동
			}
			break;
		case 's'://caps lock이 꺼져있을 때(아래로 이동)
		case 'S'://caps lock이 켜져있을 때(아래로 이동)
			if (++y > 23)
			{
				--y;//아래로이동
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
}//커서숨기기

void textcolor(int attr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attr);
}//글자색

void create_enemy() {
	/*ENEMY[100]선언한 먹이 랜덤으로 보내기*/
	for (int i = 0; i < 100; ++i) {
		if (!enemies[i].alive) {//enmies[i].alive=1(true)>따라서 거짓일 때
			enemies[i].type = rand() % 4 + 1;
			enemies[i].alive = 1;
			enemies[i].x = 74;
			enemies[i].y = rand() % 24;
			enemies[i].speed = 50;
			enemies[i]._tick = 0;
			break;
		}
	}
}//먹이 처음 위치 및 속도 설정

void move_enemies(int now) {
	for (int i = 0; i < 100; ++i) {
		if (enemies[i].alive && now - enemies[i]._tick >= enemies[i].speed) {
			if (--enemies[i].x < 0) {
				gotoxy(0, enemies[i].y);
				printf("        ");
				enemies[i].alive = 0;//거짓
			}//먹이가 x = 0에 도달하였을 때 사라지도록 만듬
			else {
				enemies[i]._tick = now;
			}
		}
	}
}//먹이가 움직이는 과정 함수

void draw_enemies()
{
	for (int i = 0; i < 100; ++i)
	{
		if (enemies[i].alive)//참일 때
		{
			gotoxy(enemies[i].x + 1, enemies[i].y);
			printf("       ");
			gotoxy(enemies[i].x, enemies[i].y);
			switch (enemies[i].type)
			{
			case FISH:
				textcolor(0x1b);
				printf("◀+<");
				break;
			case FISH2:
				textcolor(0x1b);
				printf("◀++<");
				break;
			case FISH3:
				textcolor(0x1b);
				printf("◀+++<");
				break;
			case FISH4:
				textcolor(0x1b);
				printf("◀++++<");
				break;
			}//먹이 모양 및 색설정
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
}//먹이 모두 지우기

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
		gotoxy(30, 6); printf("연어가 태어났습니다.");
		gotoxy(14, 8); printf("초기에는 난황이 있어 음식을 섭취할 필요가 없습니다.");
		gotoxy(10, 10); printf("난황을 다 섭취하고 이제 슬슬 바다로 나갈 시동을 걸고 있네요.");
		gotoxy(19, 12); printf("이 시기의 연어는 6센티의 작은 아기입니다.");
		gotoxy(20, 14); printf("강의 수서곤충(물방개)등을 먹고 삽니다.");
		gotoxy(22, 16); printf("ps. 난황 : 알에 붙어있는 영양 물질");
		Sleep(4000);
		point();
		break;
	case 2:
		textcolor(0x1F);
		gotoxy(30, 6); printf("연어가 자랐습니다.");
		gotoxy(12, 8); printf(" 남대천에서 나와 알래스카로 열심히 유영하고 있는 연어.");
		gotoxy(9, 10); printf("아직 성체 연어가 아니라 작은 물고기나 플랑크톤을 먹고 삽니다.");
		gotoxy(15, 12); printf("이 시기의 연어는 배는 흰색을, 등은 회색을 띕니다.");
		Sleep(4000);
		point();
		break;
	case 3:
		textcolor(0x1F);
		gotoxy(30, 8); printf("연어가 다 자랐군요!");
		gotoxy(20, 10); printf("이제 몸집은 70cm에서 1m가량 성장했어요!");
		gotoxy(11, 12); printf("다 자란 연어는 자기보다 몸집이 작은 물고기를 먹고 삽니다.");
		gotoxy(25, 14); printf("간혹 오징어도 먹는다고 하네요.");
		gotoxy(26, 16); printf("그럼 고향으로 돌아가볼까요?");
		Sleep(4000);
		point();
		break;
	case 4:
		textcolor(0x1F);
		gotoxy(19, 6); printf("그리운 고향, 남대천으로 연어가 돌아왔어요!");
		gotoxy(18, 8); printf("연어의 생김새가 바다연어랑은 사뭇 다릅니다.");
		gotoxy(18, 10); printf("구름 모양의 빨간 아름다운 색을 띄고 있네요!");
		gotoxy(15, 12); printf("수컷 연어는 주둥이가 날카롭게 변한게 눈에 띕니다.");
		gotoxy(25, 14); printf("이 시기엔 아무것도 먹지 않고");
		gotoxy(17, 16); printf("오로지 알을 낳기 위해 상류로 거슬러 오릅니다.");
		gotoxy(22, 18); printf("열심히 태어난 곳으로 돌아가볼까요?");
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
			printf(">+▶");
		}
		else if (n == 2) {
			textcolor(0x18);
			gotoxy(0, y);
			printf(">++▶");
		}
		else if (n == 3) {
			textcolor(0x18);
			gotoxy(0, y);
			printf(">+++▶");
		}
		else {
			textcolor(0x1c);
			gotoxy(0, y);
			printf(">++++▶");
		}
		process_key();
		now = GetTickCount();

		gotoxy(30, 24);
		textcolor(0x1f);
		printf("제한시간: %5.2f", (timelimited + started - now) / 1000.);


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
				getch();//아무거나 클릭시 최종점수 및 바이바이 확인
				system("cls");
				initi();
				file_input();
				if (check_score(score))
				{
					char testname[20];
					textcolor(0x1B);
					gotoxy(5, 10);
					printf(">+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶ >+▶");
					gotoxy(15, 12);
					textcolor(0x1F);
					printf("순위 등록을 위해 이름을 입력해 주세요: ");
					scanf("%s", testname);
					rank_sort(score, testname);
					file_output();
				}
				return 2;
			}


		if (stage == 4) {
			et = clock();
		}//clock 종료
		if (now - started >= timelimited) {
			system("cls");
			textcolor(0x1F);
			gotoxy(27, 6); printf("연어가 산란을 마쳤습니다.");
			gotoxy(12, 8); printf("산란을 마쳐 기력이 다해 연어는 그 자리에서 죽게 됩니다.");
			gotoxy(15, 10); printf("죽은 연어는 생태계의 많은 생물들의 먹이가 됩니다.");
			gotoxy(25, 12); printf("곧 이 연어가 태어났던 것처럼");
			gotoxy(12, 14); printf("수많은 연어들이 태어나 남대천 주위를 유영하고 다니겠죠?");
			textcolor(0x18);
			gotoxy(65, 15); printf("press any key");
			textcolor(0x1F);
			getch();//아무거나 클릭시 최종점수 및 바이바이 확인
			gotoxy(30, 18); printf("그럼 그때 다시 뵈요!");
			score = score + 2000 - ((et - st) / 100) + 400; //점수 = (1~4차까지 초 계산 *10)+클리어점수 400
			initi();
			file_input();
			if (check_score(score))
			{
				char testname[20];
				gotoxy(10, 22);
				textcolor(0x1E);
				printf("순위등록을 위해 이름을 입력해 주세요: ");
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
					printf("순위등록을 위해 이름을 입력해 주세요: ");
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
		printf(">+▶");
		textcolor(0x1F);
		gotoxy(1, 1);          printf(" ============================================================================ \n");
		gotoxy(1, 2);          printf("│     >                                    ▶                              │\n");
		gotoxy(1, 3);          printf("│       >                                  ▶▶                            │\n");
		gotoxy(1, 4);          printf("│        >>                                ▶▶▶▶                        │\n");
		gotoxy(1, 5);          printf("│          >>    │      │       │       ▶▶▶▶▶▶                    │\n");
		gotoxy(1, 6);          printf("│             >>=│======│====== │====== ▶▶▶▶▶▶▶▶                │\n");
		gotoxy(1, 7);          printf("│          >>    │      │       │       ▶▶▶▶▶▶   ∥    ∥∥       │\n");
		gotoxy(1, 8);          printf("│        >>     ↗=↖  ==∥              ∥▶▶▶▶       ∥====∥∥==     │\n");
		gotoxy(1, 9);          printf("│      >       │   │ ==∥     ↗=↖    ∥▶▶           ∥    ∥∥       │\n");
		gotoxy(1, 10);         printf("│    >          ↘=↙    ∥    │   │ ==∥▶┌====┐  ∥ └====┘∥       │\n");
		gotoxy(1, 11);         printf("│                      ∥       ↘=↙    ∥  ∥    ∥==∥    ↗ = ↖       │\n");
		gotoxy(1, 12);         printf("│                      └====            ∥  └====┘  ∥   │ >+▶│      │\n");
		gotoxy(1, 13);         printf("│                                        ∥      ==== ┐     ↘ = ↙       │\n");
		gotoxy(1, 14);         printf("│                                                     │                   │\n");
		gotoxy(1, 15);         printf("│                                                     │                   │\n");
		gotoxy(1, 16);         printf("│                         ┌======================┐                       │\n");
		gotoxy(1, 17);         printf("│                         │                      │                       │\n");
		gotoxy(1, 18);         printf("│                         │     1. 게임 시작     │                       │\n");
		gotoxy(1, 19);         printf("│                         │     2. 랭킹창        │                       │\n");
		gotoxy(1, 20);         printf("│                         │     3. 종료          │                       │\n");
		gotoxy(1, 21);         printf("│                         │                      │                       │\n");
		gotoxy(1, 22);         printf("│                         └======================┘                       │\n");
		gotoxy(1, 23);         printf("│                    키보드 W(w) : 위로 /  S(s) : 아래로                   │\n");
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
	printf("□□□□□□□□□□0%%");
	Sleep(500);          //0.5초 대기
	gotoxy(27, 20);
	printf("■□□□□□□□□□10%%");
	Sleep(1000);//1초대기
	gotoxy(27, 20);
	printf("■■□□□□□□□□20%%");
	Sleep(100); //0.1초대기
	gotoxy(27, 20);
	printf("■■■□□□□□□□30%%");
	Sleep(100);//0.1초대기
	gotoxy(27, 20);
	printf("■■■■□□□□□□40%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("■■■■■□□□□□50%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("■■■■■■□□□□60%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("■■■■■■■□□□70%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("■■■■■■■■□□80%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("■■■■■■■■■□90%%");
	Sleep(100);
	gotoxy(27, 20);
	printf("■■■■■■■■■■100%%");
	Sleep(500);
	gotoxy(27, 20);
	printf("■■■■■■■■■■100%%");
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
			return 1;//프로그램 정상종료 아님
	} while (run && stage <= 4);
}
void init()
{
	printf("\n"
		" =================================================================>+▶======= \n"
		"│                                                                          │\n"
		"│");
	textcolor(0x1F);
	printf("                          첨연어(Chum Salmon)                           ");
	textcolor(0x17);
	printf("  │\n"
		"│                                                                          │\n"
		"│              동해안으로 회귀해 오는 연어류의 대표적인 종으로             │\n"
		"│     양양 남대천, 삼척 오십천, 낙동강, 섬진강 등지로 산란회유하는 종이다. │\n"
		"│                                                                          │\n"
		"│                                                                          │\n"
		"│                             산란기가 되면,                               │\n"
		"│               몸에 붉은 혼인색이 나타나는 것이 특징이다.                 │\n"
		"│                                                                          │\n"
		"│                  자신이 태어났던 하천으로 다시 돌아와                    │\n"
		"│           아무 것도 먹지 않은 채 물살을 거슬러 상류로 올라와             │\n"
		"│                    알을 낳고, 기력이 쇠해 죽는다.                        │\n"
		"│                                                                          │\n"
		"│                 지금, 양양 남대천에서 연어가 태어난다.                   │\n"
		"│                 연어가 다시 고향으로 돌아올 수 있도록                    │\n"
		"│               열심히 우리가 연어를 바른 길로 이끌어 보자.                │\n"
		"│                                                                          │\n"
		"│                                                                          │\n"
		"│                게임을 더 알고 싶으시면?   Press any key!                 │\n"
		"│                                                                          │\n"
		"│                                                                          │\n"
		" ===============>+▶=========================================================\n");
	_getch();
	system("cls"); //동해-북해도 연안 / 북해도 연안 - 알래스카만 베링해 / 베링해-동해 / 동해 - 남대천
}
void exp() {
	printf("\n"
		" ===============================================================>++▶======== \n"

		"│");
	textcolor(0x1F);
	printf("                              < 조작 방법 >                               ");
	textcolor(0x17);
	printf("│\n"
		"│                                                                          │\n"
		"│                  키보드 W(w) : 연어가 위로 움직입니다.                   │\n"
		"│                 키보드 S(s) : 연어가 아래로 움직입니다.                  │\n"
		"│                                                                          │\n"
		"│");
	textcolor(0x1F);
	printf("                             < 게임 규칙 >                                ");
	textcolor(0x17);
	printf("│\n"
		"│                                                                          │\n"
		"│         - 연어와 반대쪽으로 오는 물고기가 충돌시 먹이를 먹어요!!         │\n"
		"│                                                                          │\n"
		"│            - 자기보다 큰 물고기를 먹으면 잡아먹혀서 죽어요!!             │\n"
		"│                                                                          │\n"
		"│         - 자기보다 작은 물고기를 먹으면 배가 다 안차서 죽어요!!          │\n"
		"│                                                                          │\n"
		"│                         - 제한 시간은 40초!                              │\n"
		"│         그 안에 연어가 일정량 이상의 먹이를 다 못먹으면 죽어요!!         │\n"
		"│                                                                          │\n"
		"│           - 마지막 4라운드는 연어가 강물로 올라오는 시기!                │\n"
		"│      이 때 연어는 아무것도 먹지 않으므로 먹이를 먹게되면 죽어요!!        │\n"
		"│                                                                          │\n"
		"│                                                                          │\n"
		"│                   메뉴 화면으로 가시려면~    Press any key!              │\n"
		"│                                                                          │\n"
		" =====>+▶===================================================================\n");
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
	FILE * input = fopen("ranking.txt", "r");//Input 이라는 FILE 객체를 = ranking이라는 txt파일을 읽기 모드로 읽어 선언 및 초기화 한다.
	fscanf(input, "%d\n", &num);//ranking파일에서 저장된 랭킹의 갯수를 불러온다.
	for (int i = 0; i < num; i++)
	{
		char buff[1000];//텍스트 파일에서 한 줄을 불러올 문자열을 선언, 크기는 넉넉하게
		fgets(buff, 1000, input);//한줄을 읽음
		char *tok = strtok(buff, "#");//strtok 함수를 공부하고 저장된 ranking 파일을 분석해볼것
		rankboard[i].name = strdup(tok);
		tok = strtok(NULL, "#");
		rankboard[i].sscore = atoi(tok);
	}
	fclose(input);//메모리 관리를 위해 파일객체를 소멸시켜줌
}
void file_output()
{
	FILE * output = fopen("ranking.txt", "w");
	//output 이라는 FILE 객체를 = ranking이라는 txt파일을 쓰기 모드로 읽어 선언 및 초기화 한다.
	fprintf(output, "%d\n", num);//랭킹정보의 갯수를 우선 파일에 기록해줌.
	for (int i = 0; i < num; i++)
	{
		char buff[100] = "";//파일에 저장할 문자열을 만들 버퍼
		char scorebuff[100];//정수로 저장된 점수를 문자열로 전환할 버퍼
		strcat(buff, rankboard[i].name);//strcat함수를 공부해보고 코드 분석해볼것
		strcat(buff, "#");
		itoa(rankboard[i].sscore, scorebuff, 10);
		strcat(buff, scorebuff);
		strcat(buff, "\n");
		fputs(buff, output);//만들어준 문자열을 파일에 기록함.
	}
	fclose(output);//메모리 관리를 위해 파일객체를 소멸시켜줌
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
	//두가지 경우 존재, 10명이 모두 체워져 있는 경우와 10명이 아직 다 게임을 하지 않았을 경우
	//두가지 모두 마지막 10위의 값을 새로운 값으로 체운다음 정렬을 해주면 됨.
	rankboard[9].sscore = score;
	rankboard[9].name = strdup(name);
	//정렬방식은 많은데 간단한 선택정렬로 구현함. 다른것 공부해봐
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
	//10명이 다 하지 않은 경우 랭킹의 갯수를 한개 올려준다.
}
void rank_print()
{
	printf("***************************현재 순위*****************************\n");
	printf("=================================================================\n");
	printf("       순위                   이름                   점수\n");
	printf("=================================================================\n");
	for (int i = 0; i < num; i++) {
		printf("%8d위              이름: %8s           점수: %5d\n", i + 1, rankboard[i].name, rankboard[i].sscore);
	}
	printf("=================================================================\n");
	printf("메뉴화면으로 돌아가려면~ Press any key");
}
