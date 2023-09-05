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
	g_app->initVideo("Lesson 5", 1024, 768, false);
	g_app->createScene();

    glutDisplayFunc( render );
	glutIdleFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key     );
    glutMouseFunc    ( mouse   );

	//check for extensiont
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));

	char* str = (char*)glGetString(GL_EXTENSIONS);
	
	bool draw_instanced_ext = (strstr((const char *)str, "GL_EXT_draw_instanced")!= NULL);
	bool fragment_progra_ext = (strstr((const char *)str, "GL_ARB_fragment_program")!= NULL);
	bool vertex_progra_ext = (strstr((const char *)str, "GL_ARB_vertex_program")!= NULL);

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
	g_app->resize(w, h);
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

//-----------------------------------------------
char *file2string(const char *path)
{
	FILE *fd;
	long len,
		 r;
	char *str;
 
	if (!(fd = fopen(path, "r")))
	{
		fprintf(stderr, "Can't open file '%s' for reading\n", path);
		return NULL;
	}
 
	fseek(fd, 0, SEEK_END);
	len = ftell(fd);
 
	printf("File '%s' is %ld long\n", path, len);
 
	fseek(fd, 0, SEEK_SET);
 
	if (!(str = (char*)malloc(len * sizeof(char))))
	{
		fprintf(stderr, "Can't malloc space for '%s'\n", path);
		return NULL;
	}
 
	r = fread(str, sizeof(char), len, fd);
 
	str[r - 1] = '\0'; /* Shader sources have to term with null */
 
	fclose(fd);
 
	return str;
}

//-----------------------------------------------
GLuint getProgram(char* vertexShader, char* fragmentShader)
{
	const GLchar* vsSource = file2string(vertexShader);
	const GLchar* fsSource = file2string(fragmentShader);	

	GLuint vs, /* Vertex Shader */
		   fs, /* Fragment Shader */
		   program; /* Shader Program */

	vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSource, NULL);
	glCompileShader(vs);
 
	fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSource, NULL);
	glCompileShader(fs);
 
	free((void*)vsSource);
	free((void*)fsSource);
 
	program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	return program;
}
