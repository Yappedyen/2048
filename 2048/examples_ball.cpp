#include"examples.h"


int ball_main()
{
	double h = 300;				// �߶�
	double v = 0;				// �ٶȣ��������£�
	double dv = 9.8 / 50;		// ���ٶȣ�ÿ 1/50 �룩

	// ��ʼ����ͼ����
	initgraph(640, 480);
	// ������˸
	BeginBatchDraw();
	// ����ƽ��
	line(100, 421, 540, 421);

	while (!_kbhit())
	{
		v += dv;				// ���ݼ��ٶȼ����ٶ�
		h -= (v - dv / 2);		// ����߶�

		// ����߶ȵ��ڵ�ƽ�ߣ�ʵ�ַ������ٶȷ���ȡ��
		if (h <= 0)
		{
			h += (v - dv / 2);
			v = -v * 0.9;		// ����ʱ������� 10%
		}

		// ����ɫ��
		setlinecolor(GREEN);
		circle(320, 400 - int(h), 20);
		//floodfill(320, 400 - int(h), WHITE);
		FlushBatchDraw();
		Sleep(20);				// ��ʱ��ÿ֡��ʱ 1/50 �룩

		// ������
		setlinecolor(BLACK);
		circle(320, 400 - int(h), 20);
	}
	EndBatchDraw();
	// �رջ�ͼ����
	closegraph();
	return 0;
}