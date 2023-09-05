// Copyright (C) 2011-2012 Sergey Taraban

#include "stdafx.h"
#include "SceneNode.h"

SceneNode::SceneNode(void)
{
	m_mTranslate = cml::identity<4>();
	m_mRotate = cml::identity<4>();
	m_mScale = cml::identity<4>();
	cml::matrix_translation(m_mScale, 1.0f, 1.0f, 1.0f); 

	m_vertex= m_texcoord= NULL;
	m_index = 0;

	m_angle = 0;
	m_vertex_size = 0;

	m_texID = GL_INVALID_VALUE;

	m_vbo_vertexID = GL_INVALID_VALUE;
	m_vbo_texcoordID = GL_INVALID_VALUE;

	m_ambient = cml::vector3f(0.5f, 0.5f, 0.5f); 
	m_diffuse = cml::vector3f(0.5f, 0.5f, 0.5f); 
	m_specular = cml::vector3f(0.5f, 0.5f, 0.5f); 
	m_shininess = 50;
	m_alphaTest = false;
}

//---------------------------------
SceneNode::~SceneNode(void)
{
	delete [] m_vertex;
	delete [] m_index;
	delete [] m_texcoord;

	glDeleteTextures(1, &m_texID);
	glDeleteBuffers(1, &m_vbo_vertexID);
	glDeleteBuffers(1, &m_vbo_texcoordID);
}

//---------------------------------
void SceneNode::render(float useVBO)
{
	//m_angle = 0;
	glDisable(GL_CULL_FACE);

	glPushMatrix(); 

	matrix4f mWorldTransform = m_mRotate*m_mScale*m_mTranslate; 

    if(m_name == "light 0") 
	{
		m_angle += 0.002f;
		if(m_angle > 2*M_PI) m_angle = 0;
		matrix4f mRotationAround = cml::identity<4>();
		cml::matrix_rotate_about_local_z(mRotationAround, m_angle);
		mWorldTransform *= mRotationAround;
		
		glLightfv(GL_LIGHT0, GL_POSITION, cml::vector4f(mWorldTransform(3,0), mWorldTransform(3,1), mWorldTransform(3,2), 1.0f).data());
	}
    if(m_name == "light 1") 
	{
		m_angle += 0.001f;
		if(m_angle > 2*M_PI) m_angle = 0;
		matrix4f mRotationAround = cml::identity<4>();
		cml::matrix_rotate_about_local_y(mRotationAround, m_angle);
		mWorldTransform *= mRotationAround;
		glLightfv(GL_LIGHT1, GL_POSITION, cml::vector4f(mWorldTransform(3,0), mWorldTransform(3,1), mWorldTransform(3,2), 1.0f).data());
	}

	glMultMatrixf(mWorldTransform.data());
	glGetFloatv (GL_MODELVIEW_MATRIX, m_mModelView);

	//set material
	glMaterialfv (GL_FRONT_AND_BACK,GL_AMBIENT, m_ambient.data());
	glMaterialfv (GL_FRONT_AND_BACK,GL_DIFFUSE, m_diffuse.data());
	glMaterialfv (GL_FRONT_AND_BACK,GL_SPECULAR, m_specular.data());
	glMaterialf  (GL_FRONT,GL_SHININESS, m_shininess);

	if(m_alphaTest) 
	{
		glEnable(GL_BLEND);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_NOTEQUAL, 0.0f);
	}
	else
	{
		glDisable(GL_BLEND);
		glDisable(GL_ALPHA_TEST);
	}

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, m_texID);

	if(useVBO == 1)
	{
		// activate and specify pointer to vertex array
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vbo_vertexID);
		glVertexPointer(3, GL_FLOAT, 0, NULL);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vbo_normalsID);
		glNormalPointer(GL_FLOAT, 0, NULL);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, m_vbo_texcoordID);
		glTexCoordPointer(2, GL_FLOAT, 0, NULL);

		//glColorPointer(3, GL_FLOAT, 0, m_color);

		// draw a cube
		//glDrawElements(GL_QUADS, m_vert_num, GL_UNSIGNED_BYTE, m_index);
		glDrawArrays(GL_TRIANGLES, 0, m_vert_num/3);

		// deactivate vertex arrays after drawing
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

		glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0); //disable VBO
	}
	else
	{
		// activate and specify pointer to vertex array
		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, m_vertex);
		glTexCoordPointer(2, GL_FLOAT, 0, m_texcoord);
		//glColorPointer(3, GL_FLOAT, 0, m_color);

		// draw a cube
		//glDrawElements(GL_TRIANGLES, m_vert_num, GL_UNSIGNED_BYTE, m_index);
		//glDrawArrays(GL_QUADS, 0, (m_vert_num/3));
		glDrawArrays(GL_TRIANGLES, 0, (m_vert_num/3));

		// deactivate vertex arrays after drawing
		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	glPopMatrix(); 

	//assert(glGetError() == 0);
}
