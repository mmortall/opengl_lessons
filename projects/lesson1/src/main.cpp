// lesson1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#ifdef WIN32
#include "windows.h"
#include "gl/glew.h"		//window library for OpenGL
#endif

#ifdef LINUX
#include "X11/X.h"
#endif

//OpenGL implemenataion
#include "GL/glut.h"	//gl utility library
#include "GL/glu.h"		//gl utility library
#include "GL/gl.h"
#include "GL/glext.h"

void render ();
void reshape ( int w, int h );
void key ( unsigned char key, int x, int y );
void mouse ( int button, int state, int x, int y );

#include <iostream>
#include <math.h>

using namespace std;

//Lyashenko Maxim
// VECTOR3D CLASS //
template <class T>
class Vector3D
{
	public:
		Vector3D();
		Vector3D(T x,T y, T z);
		Vector3D(T * initArray);

		 float GetLenght();
         float MultyScalar(Vector3D vec);
		 Vector3D MultyVector(Vector3D vec);
		 Vector3D Multiply(T a);
		 Vector3D DevideVector(T a);	
		 Vector3D AddictiveVector( Vector3D vec);
		 Vector3D SubtractionVector( Vector3D vec); 
		 float Corner( Vector3D vector);

		 Vector3D operator + (Vector3D vec);
		 Vector3D operator - (Vector3D vec);
		 Vector3D operator * (Vector3D vec);
		 Vector3D operator / (T a);
		 void operator = (Vector3D vec);
		 T operator [] (int i) { return (&x)[i]; }
		 
		void sumDot(const T &a);
		void sumVector(const T &a);
		T getX();
		void outVector(){cout<<"x = "<<x<<" y = "<<y<<"  z = "<<z<<endl;};
		~Vector3D(){};
	
		T x,y,z;
};

//constructor
template <class T>
Vector3D<T>::Vector3D():x(0),y(0),z(0)
{ };

//constructor 
template <class T>
Vector3D<T>::Vector3D(T x,T y, T z)
{	
	this->x = x;
	this->y = y;
	this->z = z;
};

//constructor
template <class T>
Vector3D<T>::Vector3D(T* initArray)
{
    this->x = initArray[0];
    this->y = initArray[1];
    this->z = initArray[2];
};

// get Length of Vector
template <class T>
float Vector3D<T>::GetLenght()
{
	return sqrt(pow((float)this->x, 2) + pow((float)this->y, 2) + pow((float)this->z, 2));
};

//Multiplication Scalar  
template <class T>
float Vector3D<T>::MultyScalar(Vector3D vec)
{
	return (vec.x * this->x + vec.y * this->y + vec.z * this->z);
};

//Multiplication Vector
template <class T>
Vector3D<T> Vector3D<T>::MultyVector(Vector3D vec)
{
	Vector3D res;
	res.x = (this->y * vec.z)-(vec.y * this->z);
	res.y = (this->x * vec.z)-(vec.x * this->z);
	res.z = (this->x * vec.y)-(vec.x * this->y);
	return res;
};

// Multiplication on number
template <class T>
Vector3D<T> Vector3D<T>::Multiply( T a)
{
	Vector3D res;
	res.x = this->x * a;
	res.y = this->y * a;
	res.z = this->z * a;
	return res;
};

//Division on number
template <class T>
Vector3D<T> Vector3D<T>::DevideVector(T a)
{
	float b = 1.0f / a;
	Vector3D res;
	res.x=this->x*b;
	res.y=this->y*b;
	res.z=this->z*b;
	return res;
};

//Addition vector
template <class T>
Vector3D<T> Vector3D<T>::AddictiveVector( Vector3D vec)
{
	Vector3D<T> res;
	res.x = this->x + vec.x;
	res.y = this->y + vec.y;
	res.z = this->z + vec.z;
	return res;
};

//Subtraction vector
template <class T>
Vector3D<T> Vector3D<T>::SubtractionVector( Vector3D vec)
{
	Vector3D<T> res;
	res.x = vec.x+( - this->x);
	res.y = vec.y+( - this->y);
	res.z = vec.z+( - this->z);
	return res;
};

//get angle vith vectors
template <class T>
float Vector3D<T>::Corner( Vector3D vec)
{
	float cos = MultyScalar(vec) / (GetLenght() * vec.GetLenght());
	return acos(cos);
};


// overloaded operations
template <class T>
Vector3D<T> Vector3D<T>::operator + ( Vector3D vec)
{return AddictiveVector(vec);}; 

template <class T>
Vector3D<T> Vector3D<T>::operator - ( Vector3D vec)
{return SubtractionVector(vec);}; 

template <class T>
Vector3D<T> Vector3D<T>::operator * ( Vector3D vec)
{return MultyVector(vec);}; 

template <class T>
Vector3D<T> Vector3D<T>::operator / ( T a)
{return DevideVector(a);}; 

template <class T>
void Vector3D<T>::operator = ( Vector3D vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;	
}; 


//-----------------------------------------------
int main(int argc, char* argv[])
{
	Vector3D<int> a(3,7,8);
	Vector3D<int> b(2,6,7);
	
	cout<<"x[2] ="<<a[2]<<endl;

	a.outVector();
	a=a.SubtractionVector(b);

	//crate OpenGL windows
	glutInit(&argc, argv);
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL );
	glutInitWindowSize( 1024, 768 );
	glutCreateWindow("Lasson 1");

    glutDisplayFunc( render );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( key     );
    glutMouseFunc    ( mouse   );

	glViewport(0, 0, (GLsizei)1024, (GLsizei)768 );

	//check for extensiont
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("OpenGL Vendor: %s\n", glGetString(GL_VENDOR));

	char* str = (char*)glGetString(GL_EXTENSIONS);
	printf("OpenGL Extensions: %s\n", str);
	
	bool draw_instanced_ext = (strstr((const char *)str, "GL_EXT_draw_instanced")!= NULL);
	if(!draw_instanced_ext) printf("GL_EXT_draw_instanced not supported\n");

	//start main loop
	glutMainLoop();

	return 0;
}

//-----------------------------------------------
void init ()
{
    glMatrixMode( GL_PROJECTION ); // ��������������� ��������������������� ������������������������
    glLoadIdentity();              // ��������������� ��������������������� ������������������������

    glMatrixMode( GL_MODELVIEW );  // ��������������� ��������������������� ������������ ������������������
    glLoadIdentity();              // ��������������� ��������������������� ������������ ������������������
}


//-----------------------------------------------
void render ()
{
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION ); // ��������������� ��������������������� ������������������������
    glLoadIdentity();              // ��������������� ��������������������� ������������������������

    glMatrixMode( GL_MODELVIEW );  // ��������������� ��������������������� ������������ ������������������
    glLoadIdentity();              // ��������������� ��������������������� ������������ ������������������

    glBegin(GL_TRIANGLES);
            glVertex3f( 0.0f, 1.0f, 0.0f);  // ���������������
            glVertex3f(-1.0f,-1.0f, 0.0f);  // ��������������� ���������������
            glVertex3f( 1.0f,-1.0f, 0.0f);  // ������������������ ���������������
    glEnd();

    glutSwapBuffers();
}

//-----------------------------------------------
void reshape ( int w, int h )
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h );
}

//-----------------------------------------------
void key ( unsigned char key, int x, int y )
{
    if ( key == 27 || key == 'q' || key == 'Q' )        // quit requested
        exit ( 0 );
}

//-----------------------------------------------
void mouse ( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN )
    {
		printf("Mause down in pos: %d %d\n",x, y);
    }
    if ( state == GLUT_UP )
    {
		printf("Mause up in pos: %d %d\n",x, y);
    }
}
