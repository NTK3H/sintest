#include <stdio.h>
#include <math.h>
#include <windows.h>

void gotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}

int main()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
	SetConsoleCursorInfo(hOut, &cursor_info);
	COORD size = {120, 35};
	SetConsoleScreenBufferSize(hOut,size);
	SMALL_RECT rc = {0,0,120-1,35-1};
	SetConsoleWindowInfo(hOut, TRUE,&rc);
	CONSOLE_FONT_INFOEX info = {0};
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 24;
	info.FontWeight = FW_NORMAL;
	wcscpy(info.FaceName, L"Arial");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
	HWND hWnd = GetConsoleWindow();
	PostMessage(hWnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_BLUE);
	//上面的代码用于设置控制台的属性
	
	double j=0,f = 0.011;	//f代表频率
	int y;

	//这两个循环用于绘制X和Y轴
	for(int i=0;i<120;i+=1)
	{
		gotoxy(i,16);
		printf("*");
	}
	for(int i=0;i<35;i+=1)
	{
		gotoxy(60,i);
		printf("*");
	}

	gotoxy(105,33);
	printf("ω = %g",3.1415926*2*f);
	while(1)
	{
		for(int i=0;i<120;i+=1)
		{
			y = sin(i*3.1415926*2*f+j)*15;		//x轴将保持线性变化其值将体现在i上,根据y = Asin(ωt+φ)计算y。i是t的映射
			gotoxy(i,y+16);
			printf("*");
		}
		gotoxy(105,34);
		printf("φ = %g",j);
		Sleep(100);
		for(int i=0;i<120;i+=1)
		{
			y = sin(i*3.1415926*2*f+j)*15;		//同理但是这里重新算是为了刷新界面
			if(y==0||i==60)
				continue;
			gotoxy(i,y+16);
			printf(" ");
		}
		j=j>5?0:j+0.5;	//相位体现在t上
	}
}
