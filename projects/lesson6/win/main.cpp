// Copyright (C) 2011-2012 Sergey Taraban
//
//#include "stdafx.h"

#include "../src/stdafx.h"
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
	g_app->initVideo("Lesson 6. VBO.", 1024, 768, false);

    glutDisplayFunc( render );
	glutIdleFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key     );
    glutMouseFunc    ( mouse   );

#ifdef WIN32
	glewInit();
#endif

	//check for extensiont
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));
	printf("OpenGL Renderer: %s\n", glGetString(GL_RENDER));

	char* str = (char*)glGetString(GL_EXTENSIONS);
	
	bool draw_instanced_ext = (strstr((const char *)str, "GL_EXT_draw_instanced")!= NULL);
	bool fragment_progra_ext = (strstr((const char *)str, "GL_ARB_fragment_program")!= NULL);
	bool vertex_progra_ext = (strstr((const char *)str, "GL_ARB_vertex_program")!= NULL);
	bool VBA_supported = (strstr((const char *)str, "GL_ARB_vertex_buffer_object")!= NULL);

	int maxAnizotropic, maxTextureUnits, maxTextureSize = 0;
	glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnizotropic);
	glGetIntegerv(GL_MAX_TEXTURE_UNITS, &maxTextureUnits);
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &maxTextureSize);

	printf("OpenGL Extensions: %s\n", str);
	printf("Max anizotropic: %d  Max tx. units %d  Max tx. size %d\n", maxAnizotropic, maxTextureUnits, maxTextureSize);

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
	g_app->resize(w, h);
}

//-----------------------------------------------
void key ( unsigned char key, int x, int y )
{
    if ( key == 27)        // quit requested
        exit ( 0 );
    if ( key == '1')        // quit requested
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if ( key == '2')        // quit requested
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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