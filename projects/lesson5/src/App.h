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
	SceneNode* createSphere();

	//image
	GLubyte* createChessImage(const int width = 128, const int height = 128);
	GLubyte* loadTexture(std::string filename, int &outWidth, int &outHeight, bool &outHasAlpha);

	unsigned long int getTick(); //return miliseconds from system start

private:
	std::vector<SceneNode*>  m_node;
	SceneNode** m_arrNode;

	char* m_wintitle;
	int m_screenwidth;
	int m_screenheight;
	bool m_fullscreen;

	CTime* m_time;
};
