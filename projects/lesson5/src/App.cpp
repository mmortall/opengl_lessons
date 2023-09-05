#include "stdafx.h"
#include "App.h"

#include "CTime.h"

#include "png.h"
#include "pnginfo.h"

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
	glutCreateWindow(title);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h );

	glEnable(GL_DEPTH_TEST);	    //enable depth test
	glEnable(GL_TEXTURE_2D);		//enable textures
}

//---------------------------------
void App::resize(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h );
	m_screenwidth = w;
	m_screenheight = h;
}

//---------------------------------
void App::createScene()
{
	SceneNode* box = 0;
	box = createBox(-3, 2, -5, "", TFM_LINEAR);
	box = createBox( 0, 2, -5, "box.png", TFM_LINEAR);
	box = createBox( 3, 2, -5, "rockwall.png", TFM_LINEAR);

	box = createBox(-3, -2, -5, "", TFM_LINEAR_MIPMAP);
	box = createBox( 0, -2, -5, "box.png", TFM_LINEAR_MIPMAP);
	box = createBox( 3, -2, -5, "rockwall.png", TFM_LINEAR_MIPMAP);

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

    glMatrixMode( GL_PROJECTION ); // ����� ������� ��������
    glLoadIdentity();              // ����� ������� ��������
	//glOrtho(-1, 1, -1, 1, -100, 100);
	gluPerspective(45, (float)m_screenwidth/(float)m_screenheight, 0.5f, 100);

    glMatrixMode( GL_MODELVIEW );  // ����� ������� ���� ������
    glLoadIdentity();              // ����� ������� ���� ������

	gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);

	m_time->Reset();

	static int sizemode;
	sizemode = m_node.size();
	for(int i = 0; i < sizemode; i++)
	{
		m_node[i]->render();
	}

	double dt = m_time->getDelta()*1000.0f;

	static char charBuf[50];
	sprintf(charBuf, "%s  fps: %f  ms:%f \n", m_wintitle, (float)1000.0f/dt,(float)dt);
	glutSetWindowTitle(charBuf);

    glutSwapBuffers(); //�������� ������ ������� �� ������� �� ��������������
}

//--------------------------------------
SceneNode* App::createBox(float x, float y, float z, std::string texture, App::TEXTURE_FILTER_MODE txmode)
{
	float vertices[72] = {
		-1.0, -1.0,  -1.0, 	//0
		1.0, -1.0, -1.0,	//1
		1.0,  1.0,  -1.0,	//2
		-1.0,  1.0,  -1.0,	//3

		1.0, -1.0, 1.0,		//5
		-1.0, -1.0, 1.0,	//4
		-1.0, -1.0,  -1.0, 	//0
		1.0, -1.0, -1.0,	//1

		1.0, -1.0, -1.0,	//1
		1.0,  1.0,  -1.0,	//2
		1.0,  1.0, 1.0,		//6
		1.0, -1.0, 1.0,		//5

		1.0,  1.0,  -1.0,	//2
		-1.0,  1.0,  -1.0,	//3
		-1.0,  1.0, 1.0,	//7
		1.0,  1.0, 1.0,		//6

		-1.0, -1.0,  -1.0, 	//0
		-1.0, -1.0, 1.0,	//4
		-1.0,  1.0, 1.0,	//7
		-1.0,  1.0,  -1.0,	//3

		-1.0,  1.0, 1.0,	//7
		1.0,  1.0, 1.0,		//6
		1.0, -1.0, 1.0,		//5
		-1.0, -1.0, 1.0,	//4
	};

	float color[72] = {
		0.0, 1.0,  0.5,
		0.0, 1.0,  1.0,
		1.0,  0.0,  1.0,
		0.4,  1.0,  1.0,

		1.0, 0.0, 1.0,
		0.0, 1.0, 1.0,
		1.0,  0.5, 1.0,
		0.0,  0.0, 1.0,

		1.0, 0.0, 1.0,
		0.0, 1.0, 0.0,
		1.0,  0.5, 1.0,
		0.0,  0.0, 1.0,

		1.0, 0.0, 1.0,
		0.0, 1.0, 1.0,
		0.0,  0.5, 1.0,
		0.0,  0.0, 1.0,

		1.0, 0.0, 1.0,
		0.0, 1.0, 1.0,
		0.0,  0.5, 1.0,
		0.0,  0.0, 1.0,

		1.0, 0.0, 1.0,
		0.0, 1.0, 1.0,
		1.0,  0.5, 1.0,
		0.0,  0.0, 1.0,
	};

	float texcoord[48] = {
		0.0, 0.0,
		1.0, 0.0,
		1.0,  1.0,
		0.0,  1.0,

		0.0, 0.0,
		1.0, 0.0,
		1.0,  1.0,
		0.0,  1.0,

		0.0, 0.0,
		1.0, 0.0,
		1.0,  1.0,
		0.0,  1.0,

		0.0, 0.0,
		1.0, 0.0,
		1.0,  1.0,
		0.0,  1.0,

		0.0, 0.0,
		1.0, 0.0,
		1.0,  1.0,
		0.0,  1.0,

		0.0, 0.0,
		1.0, 0.0,
		1.0,  1.0,
		0.0,  1.0,

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

	node->m_vertex = new float[72];
	node->m_color = new float[72];
	node->m_index = new GLubyte[24];
	node->m_texcoord = new float[48];
	node->m_vert_num = 72;

	memcpy(node->m_vertex, vertices, 72*sizeof(float));
	memcpy(node->m_color, color, 72*sizeof(float));
	memcpy(node->m_index, indices, 24*sizeof(GLubyte));
	memcpy(node->m_texcoord, texcoord, 48*sizeof(float));

	//create texture
	int imgw = 32, imgh = 32;
	bool hasAlpha;
	GLubyte* img = NULL;
	if(texture == "")
	{
		img = createChessImage(imgw, imgh);
	}
	else
	{
		std::string str = std::string("../media/") + texture;
		img = loadTexture(str, imgw, imgh, hasAlpha);
	}

	glGenTextures(1, &node->m_texID); //
	glBindTexture(GL_TEXTURE_2D, node->m_texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	if(txmode == TFM_NEAREST)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgw, imgh, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}
	else if(txmode == TFM_LINEAR)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgw, imgh, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}
	else if(txmode == TFM_LINEAR_MIPMAP)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //we will use mipmap levels

		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, imgw, imgh, GL_RGBA, GL_UNSIGNED_BYTE, img);
	}

	delete [] img;

	//add node to render
	m_node.push_back(node);
	return node;
}

//--------------------------------------
SceneNode* App::createSphere()
{
	/*float RADIOUSX, RADIOUSY, RADIOUSZ = 1.0f;
	GLint LAYERS = 10;
	GLint SLICES = 10;
	float HALFPI = 3.141592 * 0.5f;

	for (GLint l = 0; l<LAYERS; l++)
	{
		float y = sin(l * HALFPI / LAYERS);
		float w = cos(l * HALFPI / LAYERS);
		for(GLint s = 0; s<SLICES; s++)
		{
			float x = sin(M_PI + s * M_PI_2 / SLICES) * w;
			float z = cos(M_PI + s * M_PI_2 / SLICES) * w;
			v[LAYERS - (l + 1)][s][0] = x * RADIOUSX;
			v[LAYERS - (l + 1)][s][1] = y * RADIOUSY;
			v[LAYERS - (l + 1)][s][2] = z * RADIOUSZ;
		}
	}*/
	return 0;
}

//--------------------------------------
/*SceneNode* App::createTor()
{
	return 0;
}*/

//--------------------------------------
GLubyte* App::createChessImage(const int width, const int height)
{
	GLubyte* ing = new GLubyte [width*height*4];
	int i, j, c;

	//ing[height*width*4 + 4] = 5;
	for (i = 0; i < height*4; i++)
	{
		for (j = 0; j < width; j+=4)
		{
		 c = ((((i&0x8)==0)^((j&0x8))==0))*255;
		 ing[i*width + j] = (GLubyte) c;
		 ing[i*width + j +1] = (GLubyte) c;
		 ing[i*width + j +2] = (GLubyte) c;
		 ing[i*width + j +3] = (GLubyte) 255;
		 printf("ing[%d*width + %d\n]",i, j);
		}
	}
	return ing;
}

//--------------------------------------
GLubyte* App::loadTexture(std::string filename, int &outWidth, int &outHeight, bool &outHasAlpha)
{
	GLubyte* img;

	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;
	FILE *fp;

    if ((fp = fopen(filename.c_str(), "rb")) == NULL)
    	return false;

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (png_ptr == NULL) {
		fclose(fp);
		return false;
	}

	/* Allocate/initialize the memory
	 * for image information.  REQUIRED. */
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fclose(fp);
		png_destroy_read_struct(&png_ptr, 0, 0);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		/* Free all of the memory associated
		 * with the png_ptr and info_ptr */
		png_destroy_read_struct(&png_ptr, &info_ptr, 0);
		fclose(fp);
		/* If we get here, we had a
		 * problem reading the file */
		return false;
	}

	/* Set up the output control if
	 * you are using standard C streams */
	png_init_io(png_ptr, fp);

	/* If we have already
	 * read some of the signature */
	png_set_sig_bytes(png_ptr, sig_read);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, 0);

	outWidth = info_ptr->width;
	outHeight = info_ptr->height;
	switch (info_ptr->color_type)
	{
		case PNG_COLOR_TYPE_RGBA:
			outHasAlpha = true;
			break;
		case PNG_COLOR_TYPE_RGB:
			outHasAlpha = false;
			break;
    }

	//read image data
    unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);

    img = new unsigned char [row_bytes * outHeight];
    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);
    for (int i = 0; i < outHeight; i++)
    {
    	memcpy(img+(row_bytes * i), row_pointers[i], row_bytes);
    	//memset(img +(outHeight * i), 255, outHeight);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, 0);

    fclose(fp);

	return img;
}


