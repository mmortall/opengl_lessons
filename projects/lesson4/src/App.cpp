#include "stdafx.h"
#include "App.h"

#include "CTime.h"

//---------------------------------
App::App(void)
{
	m_time = new CTime();
}
//---------------------------------

App::~App(void)
{
}
//---------------------------------

void App::initVideo(char* title, int w, int h, bool fullscreen)
{
	m_wintitle = title;
	m_screenwidth = w;
	m_screenheight = h;
	m_fullscreen = fullscreen;

	//crate OpenGL windows
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize( w, h );
	glutCreateWindow("Lasson 4");

	glViewport(0, 0, (GLsizei)w, (GLsizei)h );

	glEnable(GL_DEPTH_TEST);	   //enable depth test
}
//---------------------------------
void App::createScene()
{
	SceneNode* box = 0;
	int cube_num = 20;
	for(int i=0; i < cube_num; i++)
	{
		for(int j=0; j < cube_num; j++)
		{
			for(int k=0; k < cube_num; k++)
			{
				box = createBox(i-cube_num*0.5, j-cube_num*0.5, -k-5);
				box->m_rotate[0] = 0.5f;
				box->m_scale[0] = 0.3f;
				box->m_scale[1] = 0.3f;
				box->m_scale[2] = 0.3f;
			}
		}
	}
	m_arrNode = new SceneNode* [m_node.size()];
	m_arrNode = &m_node.front();
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

    glMatrixMode( GL_PROJECTION ); //
    glLoadIdentity();              //
	//glOrtho(-1, 1, -1, 1, -100, 100);
	gluPerspective(45, (float)m_screenwidth/(float)m_screenheight, 0.5f, 100);

    glMatrixMode( GL_MODELVIEW );  //
    glLoadIdentity();              //

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	m_time->Reset();

	static int sizemode;
	sizemode = m_node.size();
	for(int i = 0; i < sizemode; i++)
	{
		m_node[i]->render();
		//m_arrNode[i]->render();
		//(*m_arrNode)->render();
		//(*m_arrNode)++;
	}
	/*std::vector<SceneNode*>::iterator  it = m_node.begin();
	for(;it != m_node.end(); it++) 
	{
		(*it)->render();
	}*/

	double dt = m_time->getDelta()*1000.0f;

	static char charBuf[50];
	sprintf(charBuf, "%s  fps: %f  ms:%f \n", m_wintitle, (float)1000.0f/dt,(float)dt);
	glutSetWindowTitle(charBuf);

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
