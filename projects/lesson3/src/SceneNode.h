#pragma once

class SceneNode
{
public:
	SceneNode(void);
	~SceneNode(void);

	void render();

	float	m_coord[3];
	float	m_rotate[3];
	float	m_scale[3];

	float*	m_vertex;	//������ ������
	float*	m_color;
	int		m_vert_num; //����� ������
	GLubyte*	m_index;

	float m_angle;
};
