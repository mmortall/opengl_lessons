// Copyright (C) 2011-2012 Sergey Taraban

#pragma once

#include "stdafx.h"

#include "SceneNode.h"
#include "CTime.h"

class App
{
public:
	enum TEXTURE_FILTER_MODE
	{
		TFM_NEAREST,
		TFM_LINEAR,
		TFM_LINEAR_MIPMAP,
	};

	App(void);
	~App(void);

	void initVideo(char* wintitle, int w, int h, bool fullscreen);
	void createScene();
	void update();
	void render();
	void resize(int w, int h);

	SceneNode* createBox(float x = 0, float y = 0, float z = 0, std::string texture="", TEXTURE_FILTER_MODE txmode = TFM_NEAREST);
	SceneNode* createFromFile(std::string filename, std::string texture="", TEXTURE_FILTER_MODE txmode = TFM_NEAREST);
	SceneNode* createPlane(std::string texture="", TEXTURE_FILTER_MODE txmode = TFM_NEAREST);

	void setCamera(cml::vector3f pos, cml::vector3f target, cml::vector3f up = cml::vector3f(0, 1, 0))
	{
		m_camPos = pos;
		m_camTarget = target;
		m_camUpVector = up;
	};

	//image
	GLubyte* createChessImage(const int width = 128, const int height = 128);
	GLubyte* loadTexture(std::string filename, int &outWidth, int &outHeight, bool &outHasAlpha);

	unsigned long int getTick(); //return miliseconds from system start

private:
	std::vector<SceneNode*>  m_node;
	SceneNode** m_arrNode;

	char* 	m_wintitle;
	int 	m_screenwidth;
	int 	m_screenheight;
	bool 	m_fullscreen;

	int 	m_useVBO;
	int 	m_face_num;

	GLfloat m_mWorld[16];
	GLfloat m_mView[16];
	GLfloat m_mProjection[16];

	cml::vector3f m_camPos;
	cml::vector3f m_camTarget;
	cml::vector3f m_camUpVector;

	CTime* m_time;
};
