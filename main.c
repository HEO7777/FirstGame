#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

// 메모리 할당 이슈
#define ERROR_001 "ERROR-001: 문제가 발생하여 프로그램을 실행할 수 없습니다.\n"
// cmd 초기 설정값들
#define TITLE "title RPG GAME"
#define WIDTH 100
#define HEIGHT 30
#define SAVE_FILE "data"
// player_data 초기값들
#define INIT_POS 0
#define INIT_HP 50.0f
#define INIT_MP 10.0f
#define INIT_ATK 1.0f
#define INIT_DEF 0.0f
#define INIT_A_COOL 0.0f
#define INIT_A_MOT_S 2.00f
#define INIT_A_MOT_E 1.96f

typedef struct {
	int x, y;
	float hp, mp, ATK, DEF, a_cool, a_mot_start, a_mot_end;
} Player;



void print_title(void);
void print_start(void);
void init_game(Player* p1);
void attack_motion(Player* p1, int i);



int main(void)
{
	int i, key;
	const char character = 'O';
	const char* newlines = "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	const int line_num = strlen(newlines);
	FILE *f2;

	Player p1;

	init_game(&p1);
	
	printf("%c", character);
	printf("%s", newlines);
	while (1)
	{
		f2 = fopen(SAVE_FILE, "wb");

		if (GetAsyncKeyState(0x57) && p1.y > 0)
			p1.y--;
		if (GetAsyncKeyState(0x53) && p1.y < HEIGHT - 2)
			p1.y++;
		if (GetAsyncKeyState(0x41) && p1.x > 0)
			p1.x--;
		if (GetAsyncKeyState(0x44) && p1.x < WIDTH - 2)
			p1.x++;
		if (GetAsyncKeyState(0x4B) && p1.a_cool <= 0)
			p1.a_cool = 2.0f;

		printf("\n");
		for (i = 0; i < p1.y; ++i)
		{
			if (1.8f < p1.a_cool && p1.a_cool <= 2.0f)
				attack_motion(&p1, i);
			else
				printf("\n");
		}
		
		for (i = 0; i < p1.x; ++i)
			printf(" ");
		printf("%c", character);
		if (1.7f < p1.a_cool && p1.a_cool <= 1.8f)
			printf("--");

		for (i = 0; i < line_num - p1.y; ++i)
		{
			if (1.5f < p1.a_cool && p1.a_cool <= 1.7f)
				attack_motion(&p1, i);
			else
				printf("\n");
		}
			
		printf("HP: %.1f MP: %.1f | ATK: %.1f DEF: %.1f", p1.hp, p1.mp, p1.ATK, p1.DEF);

		// 구조체 변수를 좀 더 효율적으로 다룰 방법이 없나?
		fwrite(&(p1.x), sizeof(p1.x), 1, f2);
		fwrite(&(p1.y), sizeof(p1.y), 1, f2);
		fwrite(&(p1.hp), sizeof(p1.hp), 1, f2);
		fwrite(&(p1.mp), sizeof(p1.mp), 1, f2);
		fwrite(&(p1.ATK), sizeof(p1.ATK), 1, f2);
		fwrite(&(p1.DEF), sizeof(p1.DEF), 1, f2);
		fwrite(&(p1.a_cool), sizeof(p1.a_cool), 1, f2);
		fwrite(&(p1.a_mot_start), sizeof(p1.a_mot_start), 1, f2);
		fwrite(&(p1.a_mot_end), sizeof(p1.a_mot_end), 1, f2);
		fclose(f2);

		Sleep(10);
		if (p1.a_cool > 0)
			p1.a_cool -= 0.01;
	}
	
	return 0;
}




void print_title(void)
{
	const char str[9] = "RPG Game";
	printf("%54s", str);
	
	return;
}


void print_start(void)
{
	size_t length = 100;
	const char* chars = "계속하려면 Enter를 입력하세요.";
	char* outline = (char*)malloc(length);
	if (outline == NULL)
	{
		printf("%s", ERROR_001);
		exit(1);
	}

	for (int i = 0; i < length - 1; ++i)
		outline[i] = '-';
	outline[length - 1] = '\0';

	printf("%s", outline);

	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");

	print_title();

	printf("\n\n\n\n\n\n%65s\n\n\n\n\n\n\n\n", chars);

	printf("%s", outline);

	free(outline);

	return;
}


void init_game(Player* p1)
{
	FILE* f1;
	const size_t ci_len = 50;
	const char* cmd_info = (char*)malloc(ci_len);
	if (cmd_info == NULL)
	{
		printf("%s", ERROR_001);
		exit(1);
	}

	sprintf(cmd_info, "mode con: cols=%d lines=%d", WIDTH, HEIGHT);
	system(cmd_info);
	system(TITLE);

	if ((f1 = fopen(SAVE_FILE, "rb")) != NULL)
	{
		fread(&(p1->x), sizeof(p1->x), 1, f1);
		fread(&(p1->y), sizeof(p1->y), 1, f1);
		fread(&(p1->hp), sizeof(p1->hp), 1, f1);
		fread(&(p1->mp), sizeof(p1->mp), 1, f1);
		fread(&(p1->ATK), sizeof(p1->ATK), 1, f1);
		fread(&(p1->DEF), sizeof(p1->DEF), 1, f1);
		fread(&(p1->a_cool), sizeof(p1->a_cool), 1, f1);
		fread(&(p1->a_mot_start), sizeof(p1->a_mot_start), 1, f1);
		fread(&(p1->a_mot_end), sizeof(p1->a_mot_end), 1, f1);
		fclose(f1);
	}
	else {
		print_start();
		while (_getch() != 13)
		{
			printf("\n\n\n\n\n\n\n\n\n");
			print_start();
		}
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		// 구조체 변수를 좀 더 효율적으로 다룰 방법이 없나?
		p1->x = INIT_POS;
		p1->y = INIT_POS;
		p1->hp = INIT_HP;
		p1->mp = INIT_MP;
		p1->ATK = INIT_ATK;
		p1->DEF = INIT_DEF;
		p1->a_cool = INIT_A_COOL;
		p1->a_mot_start = INIT_A_MOT_S;
		p1->a_mot_end = INIT_A_MOT_E;
	}
}


void attack_motion(Player* p1, int i)
{
	if (i == p1->y - 1 && 1.9f < p1->a_cool && p1->a_cool <= 2.0f)
	{
		for (i = 0; i < p1->x; ++i)
			printf(" ");
		printf("l");
	}
	else if (i == p1->y - 1 && 1.8f < p1->a_cool && p1->a_cool <= 1.9f)
	{
		for (i = 0; i < p1->x + 2; ++i)
			printf(" ");
		printf("/");
	}
	else if (i == 1 && 1.6f < p1->a_cool && p1->a_cool <= 1.7f)
	{
		for (i = 0; i < p1->x + 2; ++i)
			printf(" ");
		printf("L");
	}
	else if (i == 1 && 1.5f < p1->a_cool && p1->a_cool <= 1.6f)
	{
		for (i = 0; i < p1->x; ++i)
			printf(" ");
		printf("l");
	}

	printf("\n");
}
