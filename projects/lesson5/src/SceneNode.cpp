#include "stdafx.h"
#include "SceneNode.h"

SceneNode::SceneNode(void)
{
	memset(m_coord, 0, 3*(sizeof(float)));
	memset(m_rotate, 0, 3*(sizeof(float)));
	m_scale[0] = 1.0f;
	m_scale[1] = 1.0f;
	m_scale[2] = 1.0f;

	m_angle = 0;

	m_texID = GL_INVALID_VALUE;
}

//---------------------------------
SceneNode::~SceneNode(void)
{
	delete [] m_vertex;
	delete [] m_index;
}

//---------------------------------
void SceneNode::render()
{
	glPushMatrix(); 

	m_angle += 0.06f;
	if(m_angle > 360) m_angle = 0;

	glTranslatef(m_coord[0], m_coord[1], m_coord[2]);
	glRotatef(m_angle, 1, 1, 0);
	glScalef(m_scale[0], m_scale[1], m_scale[2]);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, m_texID);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glColorPointer(3, GL_FLOAT, 0, m_color);
	glTexCoordPointer(2, GL_FLOAT, 0, m_texcoord);

	// draw a cube
	//glDrawElements(GL_QUADS, m_vert_num, GL_UNSIGNED_BYTE, m_index);
	glDrawArrays(GL_QUADS, 0, (m_vert_num/3));

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glPopMatrix(); 
}
