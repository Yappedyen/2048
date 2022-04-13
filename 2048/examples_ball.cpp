#include"examples.h"


int ball_main()
{
	double h = 300;				// 高度
	double v = 0;				// 速度（方向向下）
	double dv = 9.8 / 50;		// 加速度（每 1/50 秒）

	// 初始化绘图窗口
	initgraph(640, 480);
	// 消除闪烁
	BeginBatchDraw();
	// 画地平线
	line(100, 421, 540, 421);

	while (!_kbhit())
	{
		v += dv;				// 根据加速度计算速度
		h -= (v - dv / 2);		// 计算高度

		// 如果高度低于地平线，实现反弹，速度方向取反
		if (h <= 0)
		{
			h += (v - dv / 2);
			v = -v * 0.9;		// 反弹时能量损耗 10%
		}

		// 画绿色球
		setlinecolor(GREEN);
		circle(320, 400 - int(h), 20);
		//floodfill(320, 400 - int(h), WHITE);
		FlushBatchDraw();
		Sleep(20);				// 延时（每帧延时 1/50 秒）

		// 擦掉球
		setlinecolor(BLACK);
		circle(320, 400 - int(h), 20);
	}
	EndBatchDraw();
	// 关闭绘图窗口
	closegraph();
	return 0;
}