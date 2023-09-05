#include "stdafx.h"
#include "App.h"

//---------------------------------
App::App(void)
{
}
//---------------------------------

App::~App(void)
{
}
//---------------------------------

void App::initVideo(int w, int h, bool fullscreen)
{
	m_screenwidth = w;
	m_screenheight = h;
	m_fullscreen = fullscreen;

	//crate OpenGL windows
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize( w, h );
	glutCreateWindow("Lasson 3");

	glViewport(0, 0, (GLsizei)w, (GLsizei)h );

	glEnable(GL_DEPTH_TEST);	   //enable depth test
}
//---------------------------------
void App::createScene()
{
	createBox(0, 0, -5);
}

//---------------------------------
void App::update()
{
}

//---------------------------------
void App::render()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION ); // ����� ������� ��������
    glLoadIdentity();              // ����� ������� ��������
	//glOrtho(-1, 1, -1, 1, -100, 100);
	gluPerspective(45, (float)m_screenwidth/(float)m_screenheight, 0.5f, 100);

    glMatrixMode( GL_MODELVIEW );  // ����� ������� ���� ������
    glLoadIdentity();              // ����� ������� ���� ������

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	for(int i = 0; i < m_node.size(); i++)
	{
		m_node[i]->render();
	}

    glutSwapBuffers(); //�������� ������ ������� �� ������� �� ��������������
}

//--------------------------------------
SceneNode* App::createBox(float x, float y, float z)
{
	float vertices[24] = {  
		-1.0, -1.0,  -1.0,
		1.0, -1.0, -1.0,
		1.0,  1.0,  -1.0,
		-1.0,  1.0,  -1.0,
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0,  1.0, 1.0,
		-1.0,  1.0, 1.0,
	};
	float color[24] = {  
		1.0, 0.5,  0.5,
		0.0, 1.0,  1.0,
		1.0,  0.0,  1.0,
		0.4,  1.0,  1.0,
		1.0, 0.0, 1.0,
		0.0, 1.0, 1.0,
		1.0,  0.5, 1.0,
		0.0,  0.0, 1.0,
	};

	GLubyte indices[] = {0,1,2,3,   // 24 of indices
						 5,4,0,1,
						 1,2,6,5,
						 2,3,7,6,
						 0,4,7,3,
						 7,6,5,4};

	SceneNode* node = new SceneNode();
	node->m_coord[0] = x;
	node->m_coord[1] = y;
	node->m_coord[2] = z;

	node->m_vertex = new float[25];
	node->m_color = new float[25];
	node->m_index = new GLubyte[24];
	node->m_vert_num = 24;
	memcpy(node->m_vertex, vertices, 24*sizeof(float));
	memcpy(node->m_color, color, 24*sizeof(float));
	memcpy(node->m_index, indices, 24*sizeof(GLubyte));

	m_node.push_back(node);
	return node;
}

//--------------------------------------
SceneNode* App::createSphere()
{
	return 0;
}

//--------------------------------------
SceneNode* App::createTor()
{
	return 0;
}
//--------------------------------------
unsigned long App::getTick()
{
#ifdef WIN32
	return (unsigned long) GetTickCount();
#endif
	return 0;
}
