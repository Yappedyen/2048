#include<stdio.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<easyx.h>
#include<graphics.h>  // ͼ�ο�ͷ�ļ�
#include"examples.h"


constexpr auto GRID_WIDTH = 100;  // ���ӵĿ��;
#define INTERVAL 15  //����֮��ļ��
#define GRID_NUM 4  //���еĸ�������

// ö�ٸ�����ɫ
enum Color {
	zero = RGB(205, 193, 180),
	twoto1 = RGB(238, 228, 218),
	twoto2 = RGB(237, 224, 200),
	twoto3 = RGB(242, 177, 121),
	twoto4 = RGB(245, 149, 99),
	twoto5 = RGB(246, 124, 95),
	twoto6 = RGB(246, 94, 59),
	twoto7 = RGB(242, 177, 121),
	twoto8 = RGB(237, 204, 97),
	twoto9 = RGB(255, 0, 128),
	twoto10 = RGB(145, 0, 72),
	twoto11 = RGB(242, 17, 158),
	back = RGB(187, 173, 160),
};
Color colors[13] = { zero, twoto1, twoto2, twoto3, twoto4, twoto5, twoto6, twoto7, twoto8, twoto9, twoto10, twoto11, back};
// ���� 2���ʱȽϴ�4����С
int map[GRID_NUM][GRID_NUM];

// �������2��4
int rand2or4() {
	if (rand() % 10 == 5) {
		return 4;
	}
	else {
		return 2;
	}
}
// �����ɵ����ַ�������
void setnum(){
	// һ��Ҫ��֤�ɹ����ж�ԭ������������û������0
	while (true) {
		int r = rand() % GRID_NUM;  // [0, 4)
		int c = rand() % GRID_NUM;
		if (map[r][c] == 0) {
			map[r][c] = rand2or4();
			break;
		}
	}
}


void init() {
	setnum();
	setnum();
}


void moveup() {
	for (int i = 0; i < GRID_NUM; ++i) {
		int temp = 0;
		for (int beg = 1; beg < GRID_NUM; ++beg) {
			if (map[beg][i] != 0) {
				if (map[temp][i] == 0) {
					map[temp][i] = map[beg][i];
					map[beg][i] = 0;
				}
				else if (map[temp][i] == map[beg][i]) {
					map[temp][i] *= 2;
					map[beg][i] = 0;
					++temp;
				}
				else {
					map[temp + 1][i] = map[beg][i];
					if (temp + 1 != beg)
						map[beg][i] = 0;
					++temp;
				}
			}
		}
	}
}

void movedown() {
	for (int i = 0; i < GRID_NUM; ++i) {
		int temp = GRID_NUM -1;
		for (int beg = GRID_NUM - 2; beg >=0; --beg) {
			if (map[beg][i] != 0) {
				if (map[temp][i] == 0) {
					map[temp][i] = map[beg][i];
					map[beg][i] = 0;
				}
				else if (map[temp][i] == map[beg][i]) {
					map[temp][i] *= 2;
					map[beg][i] = 0;
					--temp;
				}
				else {
					map[temp - 1][i] = map[beg][i];
					if (temp - 1 != beg)
						map[beg][i] = 0;
					--temp;
				}
			}
		}
	}
}
// ����
void moveleft() {
	for (int i = 0; i < GRID_NUM; ++i) {
		int temp = 0;
		for (int beg = 1; beg < GRID_NUM; ++beg) {
			if (map[i][beg] != 0) {
				if (map[i][temp] == 0) {
					map[i][temp] = map[i][beg];
					map[i][beg] = 0;
				}
				else if (map[i][temp] == map[i][beg]) {
					map[i][temp] *= 2;
					map[i][beg] = 0;
					++temp;
				}
				else {
					map[i][temp + 1] = map[i][beg];
					if (temp + 1 != beg)
						map[i][beg] = 0;
					++temp;
				}
			}
		}
	}
}
// ����
void moveright() {
	for (int i = 0; i < GRID_NUM; ++i) {
		int temp = GRID_NUM - 1;
		for (int beg = GRID_NUM - 2; beg >= 0; --beg) {
			if (map[i][beg] != 0) {
				if (map[i][temp] == 0) {
					map[i][temp] = map[i][beg];
					map[i][beg] = 0;
				}
				else if (map[i][temp] == map[i][beg]) {
					map[i][temp] *= 2;
					map[i][beg] = 0;
					--temp;
				}
				else {
					map[i][temp - 1] = map[i][beg];
					if (temp - 1 != beg)
						map[i][beg] = 0;
					--temp;
				}
			}
		}
	}
}

void keyevent() {
	int key = _getch();  // ��ȡ���̰�����72 ��80 ��75 ��77
	switch (key) {
	case 72:
		moveup();
		setnum();
		break;
	case 80:
		movedown();
		setnum();
		break;
	case 75:
		moveleft();
		setnum();
		break;
	case 77:
		moveright();
		setnum();
		break;
	}
}


void draw() {
	// ���Ƹ���
	for (int i = 0; i < GRID_NUM; ++i) {
		for (int j = 0; j < GRID_NUM; ++j) {
			int x = i * GRID_WIDTH + (i + 1) * INTERVAL;
			int y = j * GRID_WIDTH + (j + 1) * INTERVAL;
			// ���ø��ӱ�����ɫ
			int index = log2(map[j][i]);	// ��colors�����л����ɫ�±�0 2 4 8  2^i = map[x][y]
			setfillcolor(colors[index]);
			// ������ת��Ϊ����
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);
			if (map[j][i] != 0) {
				// �ڸ�������ʾ����
				settextstyle(50, 0, "����");
				// ������ֵ��������ڼ����������¼��������
				char str[5] = { 0 };
				sprintf_s(str, "%d", map[j][i]);
				// �������Ҽ��
				int horspace = (GRID_WIDTH - textwidth(str)) / 2;
				// �������¼��
				int vecspace = (GRID_WIDTH - textheight(str)) / 2;
				// ��ʾ�ı�
				outtextxy(x + horspace, y + vecspace, str);
			}
			
		}
	}
}

int main() {

	int ret = ball_main();
	// ����ͼ�δ���
	initgraph(GRID_WIDTH * GRID_NUM + (GRID_NUM +1) *INTERVAL, GRID_WIDTH * GRID_NUM + (GRID_NUM + 1) * INTERVAL, EW_SHOWCONSOLE);
	// ���ñ�����ɫ
	setbkcolor(colors[12]);
	// ����
	cleardevice();
	// ���ñ���ģʽ
	setbkmode(TRANSPARENT);
	// �������������
	srand(time(NULL));

	init();
	while (true) {
		draw();
		keyevent();
	}
	
	return 0;
}