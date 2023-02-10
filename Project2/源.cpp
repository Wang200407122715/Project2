#include<stdio.h>
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>//媒体头文件
#pragma comment(lib,"winmm.lib")//媒体库文件
int main()
{
	//创建一个窗口
	initgraph(900, 600);
	//加载照片
	IMAGE bkimg[7];
	for (int i = 0; i < 7; i++)
	{
		char path[260];
		sprintf_s(path, "%d.jpg", i + 1);
		loadimage(&bkimg[i], path, 900, 600);
	}

	//加载苹果
	IMAGE appimg0, appimg1;
	loadimage(&appimg0, "apple0.jpg");
	loadimage(&appimg1, "apple1.jpg");
	//播放音乐
	mciSendString("open 告白气球.mp3", 0, 0, 0);
	mciSendString("play 告白气球.mp3", 0, 0, 0);

	//定义苹果坐标
	int x, y;
	char ch;              //字母
	int score = 0;        //分数
	ExMessage m;          //消息
	int index = 0;        //索引

	while (1)
	{
		x = rand() % 850;
		ch = 'A' + rand() % 26;

		for (y = 0; y < 600; y++)
		{
			BeginBatchDraw();//解决闪烁问题

			//显示背景图片
			putimage(0, 0, &bkimg[index]);
			//显示苹果（透明贴图法）
			putimage(x, y, &appimg0, SRCPAINT);
			putimage(x, y, &appimg1, SRCAND);
			//设置颜色背景透明
			setbkmode(0);
			//输出字母
			outtextxy(x + 20, y + 20, ch);
			//输出分数
			char str[20];
			sprintf_s(str, "分数：%d", score);
			outtextxy(5, 5, str);
			EndBatchDraw();

			//获取键盘输入
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