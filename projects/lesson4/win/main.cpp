// lesson1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include "../src/App.h"

void render ();
void reshape ( int w, int h );
void key ( unsigned char key, int x, int y );
void mouse ( int button, int state, int x, int y );

App* g_app;

//-----------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	g_app = new App();
	g_app->initVideo("Lesson 4. Performance.", 1024, 768, false);

    glutDisplayFunc( render );
	glutIdleFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key     );
    glutMouseFunc    ( mouse   );

	//check for extensiont
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDER));

	char* str = (char*)glGetString(GL_EXTENSIONS);
	
	bool draw_instanced_ext = (strstr((const char *)str, "GL_EXT_draw_instanced")!= NULL);
	bool fragment_progra_ext = (strstr((const char *)str, "GL_ARB_fragment_program")!= NULL);
	bool vertex_progra_ext = (strstr((const char *)str, "GL_ARB_vertex_program")!= NULL);

	g_app->createScene();

	//start main loop
	glutMainLoop();

	return 0;
}

//-----------------------------------------------
void render ()
{
	g_app->render();
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
