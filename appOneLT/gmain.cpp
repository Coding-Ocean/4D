#include"libOne.h"
//４D座標構造体
struct POS{
	float x, y, z, w;
};
//点の数
const int num = 16;
//オリジナルポジションop
struct POS op[num] = {
	//キューブ１
	-1,1,-1,-1,
	-1,-1,-1,-1,
	1,-1,-1,-1,
	1,1,-1,-1,
	-1,1,1,-1,
	-1,-1,1,-1,
	1,-1,1,-1,
	1,1,1,-1,
	//キューブ２
	-1,1,-1,1,
	-1,-1,-1,1,
	1,-1,-1,1,
	1,1,-1,1,
	-1,1,1,1,
	-1,-1,1,1,
	1,-1,1,1,
	1,1,1,1,
};
//座標変換後ポジションp
struct POS p[num];
float ang = 0;

//座標変換
void update()
{
	for (int i = 0; i < num; i++) {
		//transform
		p[i].x = Cos(ang) * op[i].x - Sin(ang) * op[i].z;
		p[i].z = Sin(ang) * op[i].x + Cos(ang) * op[i].z;
		p[i].y = Cos(ang) * op[i].y - Sin(ang) * op[i].w;
		p[i].w = Sin(ang) * op[i].y + Cos(ang) * op[i].w;
		//4D to 3D projection
		p[i].w += 2;
		p[i].x /= p[i].w;
		p[i].y /= p[i].w;
		p[i].z /= p[i].w;
		//3D to 2D projection
		p[i].z += 6;
		p[i].x /= p[i].z;
		p[i].y /= p[i].z;
	}
	//次のラジアン
	ang -= 0.5f * 3.141592f / 180;
}

//p[i]からp[j]に線を引く
void line(int i, int j) {
	mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
}
//線と点の描画
void draw()
{
	//数学座標を使用
	clear();
	mathAxis(1);
	//線
	stroke(150, 150, 255);
	strokeWeight(5);
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		//キューブ１
		line(i, j);
		line(i+4, j+4);
		line(i, i+4);
		//キューブ２
		line(i+8, j+8);
		line(i + 4+8, j + 4+8);
		line(i+8, i + 4+8);
		//キューブ１から２への線
		line(i, i + 8);
		line(i+4, i + 8+4);
	}
	//点
	stroke(0);
	strokeWeight(10);
	for (int i = 0; i < num; i++) {
		mathPoint(p[i].x, p[i].y);
	}
}

//メイン
void gmain()
{
	window(1920, 1080, full);
	hideCursor();
	while (notQuit) {
		update();
		draw();
	}
}