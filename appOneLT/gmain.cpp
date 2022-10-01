#include"libOne.h"
//�SD���W�\����
struct POS{
	float x, y, z, w;
};
//�_�̐�
const int num = 16;
//�I���W�i���|�W�V����op
struct POS op[num] = {
	//�L���[�u�P
	-1,1,-1,-1,
	-1,-1,-1,-1,
	1,-1,-1,-1,
	1,1,-1,-1,
	-1,1,1,-1,
	-1,-1,1,-1,
	1,-1,1,-1,
	1,1,1,-1,
	//�L���[�u�Q
	-1,1,-1,1,
	-1,-1,-1,1,
	1,-1,-1,1,
	1,1,-1,1,
	-1,1,1,1,
	-1,-1,1,1,
	1,-1,1,1,
	1,1,1,1,
};
//���W�ϊ���|�W�V����p
struct POS p[num];
float ang = 0;

//���W�ϊ�
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
	//���̃��W�A��
	ang -= 0.5f * 3.141592f / 180;
}

//p[i]����p[j]�ɐ�������
void line(int i, int j) {
	mathLine(p[i].x, p[i].y, p[j].x, p[j].y);
}
//���Ɠ_�̕`��
void draw()
{
	//���w���W���g�p
	clear();
	mathAxis(1);
	//��
	stroke(150, 150, 255);
	strokeWeight(5);
	for (int i = 0; i < 4; i++) {
		int j = (i + 1) % 4;
		//�L���[�u�P
		line(i, j);
		line(i+4, j+4);
		line(i, i+4);
		//�L���[�u�Q
		line(i+8, j+8);
		line(i + 4+8, j + 4+8);
		line(i+8, i + 4+8);
		//�L���[�u�P����Q�ւ̐�
		line(i, i + 8);
		line(i+4, i + 8+4);
	}
	//�_
	stroke(0);
	strokeWeight(10);
	for (int i = 0; i < num; i++) {
		mathPoint(p[i].x, p[i].y);
	}
}

//���C��
void gmain()
{
	window(1920, 1080, full);
	hideCursor();
	while (notQuit) {
		update();
		draw();
	}
}