#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>//ý��ͷ�ļ�
#pragma comment(lib,"winmm.lib")//ý����ļ�
int main()
{
	//����һ������
	initgraph(900, 600);
	//������Ƭ
	IMAGE bkimg[7];
	for (int i = 0; i < 7; i++)
	{
		char path[260];
		sprintf_s(path, "%d.jpg", i + 1);
		loadimage(&bkimg[i], path, 900, 600);
	}

	//����ƻ��
	IMAGE appimg0, appimg1;
	loadimage(&appimg0, "apple0.jpg");
	loadimage(&appimg1, "apple1.jpg");
	//��������
	mciSendString("open �������.mp3", 0, 0, 0);
	mciSendString("play �������.mp3", 0, 0, 0);

	//����ƻ������
	int x, y;
	char ch;              //��ĸ
	int score = 0;        //����
	ExMessage m;          //��Ϣ
	int index = 0;        //����

	while (1)
	{
		x = rand() % 850;
		ch = 'A' + rand() % 26;

		for (y = 0; y < 600; y++)
		{
			BeginBatchDraw();//�����˸����

			//��ʾ����ͼƬ
			putimage(0, 0, &bkimg[index]);
			//��ʾƻ����͸����ͼ����
			putimage(x, y, &appimg0, SRCPAINT);
			putimage(x, y, &appimg1, SRCAND);
			//������ɫ����͸��
			setbkmode(0);
			//�����ĸ
			outtextxy(x + 20, y + 20, ch);
			//�������
			char str[20];
			sprintf_s(str, "������%d", score);
			outtextxy(5, 5, str);
			EndBatchDraw();

			//��ȡ��������
			peekmessage(&m, EX_KEY);
			if (m.message == WM_KEYDOWN)
			{
				if (m.vkcode == ch)
				{
					index++;
					if (index >= 7)
					{
						index = 0;
					}
					score += 5;
					break;
				}
			}
			Sleep(10);
		}
	}
	return 0;
}