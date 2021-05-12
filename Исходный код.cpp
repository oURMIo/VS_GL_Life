
#pragma comment(lib, "glut32.lib")

#include <Windows.h>
#include "GL/glut.h"
#include <stdlib.h>


#define M 800
#define N 512

#define ALIFE	0
#define DEAD	3

#define WINDOW_W	1600
#define WINDOW_H	1024

#define KLETKA_W  4 //	(WINDOW_H / M)
#define KLETKA_H  4 //	(WINDOW_H / N)

unsigned char data[M][N] = { DEAD };
unsigned char old_data[M][N] = { DEAD };

GLfloat colorYes[4][3] = 
{
	{ 0.7, 0.9, 0.3 },
	{ 0.3, 0.5, 0.0 },
	{ 0.1, 0.3, 0.0 },
	{ 0.0, 0.1, 0.0 }
};

void BackupGeneration()
{
	int i, j;

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
			old_data[i][j] = data[i][j];
}
void SwapGeneration()
{
	int i, j;

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
			old_data[i][j] = data[i][j] + old_data[i][j];
			data[i][j] = old_data[i][j] - data[i][j];
			old_data[i][j] = old_data[i][j] - data[i][j];
		}

}
int CountCitizens(int icheck, int jcheck)
{
	int i, j, count = 0, ileft, iright, jleft, jright;

	ileft = icheck - 1;
	iright = icheck + 1;
	jleft = jcheck - 1;
	jright = jcheck + 1;

		for (i = ileft; i <= iright; i++)
			for (j = jleft; j <= jright; j++)
			{
			//if (i != icheck && j != jcheck && i != -1 && j != -1 && i != M && j != N && old_data[i][j] == ALIFE)
			if (
				(!((i == icheck) && (j == jcheck))) && 
				((i != -1) && (j != -1) && (i != M) && (j != N)) &&
				(old_data[i][j] == ALIFE))
					count++;
			}
	
	
	return count;
}
void NewGeneration()
{
	int i, j, count;

	//SwapGeneration();
	BackupGeneration();

	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
			count = CountCitizens(i, j);
			if (count == 3)
				data[i][j] = ALIFE;
			else if ((count < 2) || (count > 3))
				data[i][j] = DEAD;
			else if (count == 2) 
				data[i][j] = old_data[i][j];
		}

}

void display()
{
	int i, j;
	glClearColor(0.0, 0.0, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//glColor3fv(colorYes[0]);
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			//if (NO != data[i][j])
			{
				//if (ALIFE == data[i][j]) glColor3fv(colorYes[0]);
				//if (DEAD == data[i][j]) glColor3fv(colorYes[3]);
				glColor3fv(colorYes[data[i][j]]);
				glRectf(i * KLETKA_W, j * KLETKA_H, i * KLETKA_W + KLETKA_W - 1, j * KLETKA_H + KLETKA_H - 1);
			}
		}

	// окончание работы с кадром
	glFlush();
	glFinish();
}


//void  initData(unsigned char **data)
void initData()
{
	int i, j;
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
		data[i][j] = (rand() % 2) ? ALIFE : DEAD;
		}

}


void keyboard(unsigned char key, int x, int y)
{
	initData();
}


void stepData()
{
	int i, j;

	NewGeneration();
	/*
	for (i = 0; i < M; i++)
		for (j = 0; j < N; j++)
		{
			if (data[j][i] < 3) 
				data[j][i] = data[j][i] + 1;
			
		}*/
}

void timer(int value)
{
	glutPostRedisplay();  // Redraw windows
	stepData();
	glutTimerFunc(150, timer, 0);
}


int main(int argc, char **argv)
//int main()
{
	glutInit(&argc, argv);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Life");
	glutInitWindowPosition(20, 20);

	
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutTimerFunc(600, timer, 0);

	glOrtho(0.0, WINDOW_W, 0.0, WINDOW_H, -1.0, 1.0);
	glTranslatef(10, 10, 0);

	initData();

	glutMainLoop();
	return 0;
}