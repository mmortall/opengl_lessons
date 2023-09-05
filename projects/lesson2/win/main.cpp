// lesson1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef WIN32
#include "windows.h"
#include "gl/glew.h"		//window library for OpenGL
#endif

#ifdef LINUX
#include "X11/X.h"
#include "X11/GLX.h"
#endif

//OpenGL implemenataion
#include "gl/glut.h"	//gl utility library
#include "gl/glu.h"		//gl utility library
#include "gl/gl.h"
#include "gl/glext.h"

void render ();
void reshape ( int w, int h );
void key ( unsigned char key, int x, int y );
void mouse ( int button, int state, int x, int y );

//-----------------------------------------------
int main(int argc, char* argv[])
{
	//crate OpenGL windows
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize( 1024, 1024 );
	glutCreateWindow("Lasson 1");

    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key     );
    glutMouseFunc    ( mouse   );

	glViewport(0, 0, (GLsizei)1024, (GLsizei)768 );

	//check for extensiont
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));

	char* str = (char*)glGetString(GL_EXTENSIONS);

	//start main loop
	glutMainLoop();

	return 0;
}

//-----------------------------------------------
void init ()
{
    glMatrixMode( GL_PROJECTION ); // Выбор матрицы проекций
    glLoadIdentity();              // Сброс матрицы проекции

    glMatrixMode( GL_MODELVIEW );  // Выбор матрицы вида модели
    glLoadIdentity();              // Сброс матрицы вида модели

	glEnable(GL_DEPTH_TEST);	   // вкочбение текста глубины
}


//-----------------------------------------------
void render ()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION ); // Выбор матрицы проекций
    glLoadIdentity();              // Сброс матрицы проекции
	//glOrtho(-1, 1, -1, 1, -100, 100);
	gluPerspective(45, 1.0f, 0.5f, 100);

    glMatrixMode( GL_MODELVIEW );  // Выбор матрицы вида модели
    glLoadIdentity();              // Сброс матрицы вида модели

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	//draw triagle
	glPushMatrix(); //скопировали текущую матрицу моделивида

	glScalef(0.3f, 0.3f, 0.3f);
	glTranslatef(-1.5f,0.0f,0.0f);

    glBegin(GL_TRIANGLES); 
		glColor3f(1.0f, 0, 0);
        glVertex3f( 0.0f, 1.0f, 0.0f);  // Вверх
		glColor3f(0, 1.0f, 0);
        glVertex3f(-1.0f,-1.0f, 0.0f);  // Слева снизу
		glColor3f(0, 0, 1.0f);
        glVertex3f( 1.0f,-1.0f, 0.0f);  // Справа снизу
    glEnd();

	glPopMatrix(); //заменили текцщю матрицу на матрицу до преобразований

	//draw quad
	glPushMatrix();  //скопировали текущую матрицу моделивида

	glScalef(0.3f, 0.3f, 0.3f);
	glTranslatef(+1.5f,0.0f,+5.0f);

    glBegin(GL_QUADS);
		glColor3f(0, 1.0f, 0);
        glVertex3f(-1.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f, 1.0f, 0.0f);
        glVertex3f( 1.0f,-1.0f, 0.0f);
        glVertex3f(-1.0f,-1.0f, 0.0f);
    glEnd();

	//draw lines
	glPushMatrix();  //скопировали текущую матрицу моделивида

	glTranslatef(+0.0f,1.0f,+5.0f);

    glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f( 1.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f,1.0f, 0.0f);
        glVertex3f( 0.0f, 1.0f, 0.0f);
        glVertex3f( -1.0f,1.0f, 0.0f);
    glEnd();

	glPopMatrix();

    glutSwapBuffers(); //заменили текцщю матрицу на матрицу до преобразований
}

//-----------------------------------------------
void reshape ( int w, int h )
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h );
}

//-----------------------------------------------
void key ( unsigned char key, int x, int y )
{
    if ( key == 27 || key == 'q' || key == 'Q' )        // quit requested
        exit ( 0 );
}

//-----------------------------------------------
void mouse ( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN )
    {
		printf("Mause down in pos: %d %d\n",x, y);
    }
    if ( state == GLUT_UP )
    {
		printf("Mause up in pos: %d %d\n",x, y);
    }
}
