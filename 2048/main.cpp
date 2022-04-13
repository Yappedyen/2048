#include<stdio.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<easyx.h>
#include<graphics.h>  // 图形库头文件
#include"examples.h"


constexpr auto GRID_WIDTH = 100;  // 格子的宽度;
#define INTERVAL 15  //格子之间的间隔
#define GRID_NUM 4  //行列的格子数量

// 枚举格子颜色
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
// 数字 2概率比较大，4概率小
int map[GRID_NUM][GRID_NUM];

// 随机生成2或4
int rand2or4() {
	if (rand() % 10 == 5) {
		return 4;
	}
	else {
		return 2;
	}
}
// 把生成的数字放入数组
void setnum(){
	// 一定要保证成功，判断原来数组里面有没有数据0
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
// 左移
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
// 右移
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
	int key = _getch();  // 获取键盘按键上72 下80 左75 右77
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
	// 绘制格子
	for (int i = 0; i < GRID_NUM; ++i) {
		for (int j = 0; j < GRID_NUM; ++j) {
			int x = i * GRID_WIDTH + (i + 1) * INTERVAL;
			int y = j * GRID_WIDTH + (j + 1) * INTERVAL;
			// 设置格子背景颜色
			int index = log2(map[j][i]);	// 在colors数组中获得颜色下标0 2 4 8  2^i = map[x][y]
			setfillcolor(colors[index]);
			// 将数据转化为界面
			solidroundrect(x, y, x + GRID_WIDTH, y + GRID_WIDTH, 10, 10);
			if (map[j][i] != 0) {
				// 在格子上显示数字
				settextstyle(50, 0, "宋体");
				// 存放数字到数组用于计算左右上下间距来居中
				char str[5] = { 0 };
				sprintf_s(str, "%d", map[j][i]);
				// 计算左右间距
				int horspace = (GRID_WIDTH - textwidth(str)) / 2;
				// 计算上下间距
				int vecspace = (GRID_WIDTH - textheight(str)) / 2;
				// 显示文本
				outtextxy(x + horspace, y + vecspace, str);
			}
			
		}
	}
}

int main() {

	int ret = ball_main();
	// 创建图形窗口
	initgraph(GRID_WIDTH * GRID_NUM + (GRID_NUM +1) *INTERVAL, GRID_WIDTH * GRID_NUM + (GRID_NUM + 1) * INTERVAL, EW_SHOWCONSOLE);
	// 设置背景颜色
	setbkcolor(colors[12]);
	// 清屏
	cleardevice();
	// 设置背景模式
	setbkmode(TRANSPARENT);
	// 设置随机数种子
	srand(time(NULL));

	init();
	while (true) {
		draw();
		keyevent();
	}
	
	return 0;
}