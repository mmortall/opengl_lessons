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

	m_angle += 0.5f;
	if(m_angle > 360) m_angle = 0;

	glTranslatef(m_coord[0], m_coord[1], m_coord[2]);
	glRotatef(m_angle, 1, 1, 0);
	glScalef(m_scale[0], m_scale[1], m_scale[2]);

	// activate and specify pointer to vertex array
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glColorPointer(3, GL_FLOAT, 0, m_color);

	// draw a cube
	glDrawElements(GL_QUADS, m_vert_num, GL_UNSIGNED_BYTE, m_index);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix(); 
}
