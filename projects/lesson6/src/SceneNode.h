// Copyright (C) 2011-2012 Sergey Taraban

#pragma once

#include "stdafx.h"

class SceneNode
{
public:
	SceneNode(void);
	~SceneNode(void);

	void render(float useVBO);

	void setPosition(cml::vector3f pos)
	{
		m_mTranslate = cml::identity<4>();
		cml::matrix_translation(m_mTranslate, pos[0], pos[1], pos[2]); 
	};
	void setRotation(cml::vector3f rot)
	{
		m_mRotate = cml::identity<4>();
		if(rot[0] > 0) cml::matrix_rotate_about_local_x(m_mRotate, rot[0]); 
		if(rot[1] > 0) cml::matrix_rotate_about_local_y(m_mRotate, rot[1]); 
		if(rot[2] > 0) cml::matrix_rotate_about_local_z(m_mRotate, rot[2]); 
	};
	void setScale(cml::vector3f scale)
	{ 
		if(scale[0] + scale[1] + scale[2] < 0.001f) assert(false);
		m_mScale = cml::identity<4>();
		cml::matrix_scale(m_mScale, scale[0], scale[1], scale[2]); 
	};

	GLfloat m_mModelView[16];

	float*	m_vertex;	
	float*	m_color;
	float*	m_texcoord;
	int		m_vert_num; 
	int		m_text_coord_num; 
	int		m_vertex_size;
	int		m_texcoord_size;

	GLubyte*	m_index;

	GLuint  m_texID;			//texture ID
	GLuint  m_vbo_vertexID;		//vertex buffer object ID for vertex
	GLuint  m_vbo_texcoordID;	//vertex buffer object ID for tex coord

	float m_angle;

private:
	//object transformations
	matrix4f m_mTranslate; 
	matrix4f m_mRotate; 
	matrix4f m_mScale; 
};
