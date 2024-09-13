#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h> 
#define _CRT_SECURE_NO_WARNINGS

int floor[10] = { 1,2,3,4,5,6,7,8,9,10 };

typedef struct {
    char num;
    int floor;
}people;

void gotoxy(int x, int y) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void clear_line2(int line) {        //������ ���� ����� �ڵ�
    gotoxy(5, line);
    printf("                                                                                ");
    gotoxy(5, line);
}

void clear_line(int line) {
    gotoxy(0, line);
    printf("                                                                                ");
    gotoxy(0, line);
}

void midway_passenger(people d[], int* c, int current_floor) {
    int new_passengers;
    clear_line(10);
    printf("%d�� ���� Ÿ�� ��� ���� �� ���Դϱ�? ", current_floor);
    scanf_s("%d", &new_passengers);

    for (int i = 0; i < new_passengers; i++) {
        clear_line(10);
        d[*c].num = 'a' + *c;  // ���ο� ����� ��ȣ ����
        printf("%c�� �������� �����ϱ�? ", d[*c].num);
        scanf_s("%d", &d[*c].floor);
        (*c)++;
    }
}

void find_max_min_floors(people d[], int c, int* max_floor, int* min_floor) {
    *max_floor = 0;
    *min_floor = 11;
    for (int i = 0; i < c; i++) {
        if (*max_floor < d[i].floor) {
            *max_floor = d[i].floor;
        }
        if (*min_floor > d[i].floor) {
            *min_floor = d[i].floor;
        }
    }
}

void find_max_floors(people d[], int c, int* max_floor) {
    *max_floor = 0;
    for (int i = 0; i < c; i++) {
        if (*max_floor < d[i].floor) {
            *max_floor = d[i].floor;
        }
    }
}

void find_min_floors(people d[], int c, int* min_floor) {
    *min_floor = 11;
    for (int i = 0; i < c; i++) {
        if (*min_floor > d[i].floor) {
            *min_floor = d[i].floor;
        }
    }
}

void up_floor(int a, int b, int c, people d[]) {
    for (int j = 10 - a; j >= 10 - b; j--) {
        gotoxy(5, j);
        for (int i = 0; i < c; i++) {       //ž���ο� ���
            printf("%c ", d[i].num);
        }

        midway_passenger(d, &c, 10 - j);

        find_max_floors(d, c, &b);

        for (int i = 0; i < c; i++) {       //ž���Ϸ��� �ο� �� ���� ���������� ��ġ���� �Ʒ� ���̸� ���x
            if (d[i].floor < 10 - j) {
                d[i].num = ' ';
            }
        }

        for (int i = 0; i < c; i++) {       //�����ο� ���
            if (d[i].floor == 10 - j) {
                d[i].num = ' ';
            }
        }
        clear_line2(j);
    }
}

void down_floor(int a, int b, int c, people d[]) {
    for (int j = 10 - a; j <= 10 - b; j++) {
        gotoxy(5, j);
        for (int i = 0; i < c; i++) {
            printf("%c ", d[i].num);
        }

        midway_passenger(d, &c, 10 - j);

        find_min_floors(d, c, &b);

        for (int i = 0; i < c; i++) {       ////ž���Ϸ��� �ο� �� ���� ���������� ��ġ���� �� ���̸� ���x
            if (d[i].floor > 10 - j) {
                d[i].num = ' ';
            }
        }

        for (int i = 0; i < c; i++) {
            if (d[i].floor == 10 - j) {
                d[i].num = ' ';
            }
        }
        clear_line2(j);
    }
}

int main(void) {
    bool game = true;
    int x1, z1;
    int temp_max;
    int temp_min;
    char updown;
    people p[26];

    for (int i = 9; i >= 0; i--) {
        printf("%d\n", floor[i]);
    }
    while (game) {
        for (int i = 0; i < 10; i++) {
            p[i].num = 'a' + i;
        }
        printf("���� ���������ʹ� ������ �ֽ��ϱ�? ");
        scanf_s("%d", &x1);
        clear_line(10);
        printf("�ö󰡴� ���������� �Դϱ�? (y/n) ");
        scanf_s(" %c", &updown);
        clear_line(10);
        printf("����� ž���մϱ�? ");
        scanf_s("%d", &z1);
        clear_line(10);
        for (int i = 0; i < z1; i++) {
            printf("%c�� �������� �����ϱ�? ", p[i].num);
            scanf_s("%d", &p[i].floor);
            clear_line(10);
        }

        find_max_min_floors(p, z1, &temp_max, &temp_min);

        if (updown == 'y') {
            up_floor(x1, temp_max, z1, p);
        }
        if (updown == 'n') {
            down_floor(x1, temp_min, z1, p);
        }

        clear_line(10);
        char continue_game;
        printf("���������͸� ��� �۵� �Ͻðڽ��ϱ�? (y/n): ");
        scanf_s(" %c", &continue_game);
        if (continue_game == 'n' || continue_game == 'N') {
            game = false;
        }
        clear_line(10);
    }
    return 0;
}