#pragma once

#include "SceneNode.h"
#include "CTime.h"

class App
{
public:
	App(void);
	~App(void);

	void initVideo(char* wintitle, int w, int h, bool fullscreen);
	void createScene();
	void update();
	void render();

	SceneNode* createBox(float x = 0, float y = 0, float z = 0);
	SceneNode* createSphere();
	SceneNode* createTor();

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
