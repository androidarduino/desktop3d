#ifndef VECTOR_H 
#define VECTOR_H 
 
#include <iostream> 
#include <cmath> 
 
class Vector3D 
{ 
public: 
	float m_fX, m_fY, m_fZ;	
public: 
	Vector3D () 
	{ 
		this->m_fX = 0.0f; 
		this->m_fY = 0.0f; 
		this->m_fZ = 0.0f; 
	} 
	Vector3D(float xi, float yi, float zi) 
	{ 
		this->m_fX = xi; 
		this->m_fY = yi; 
		this->m_fZ = zi; 
	} 
	Vector3D(const Vector3D &v3d) 
	{ 
		this->m_fX = v3d.m_fX; 
		this->m_fY = v3d.m_fY; 
		this->m_fZ = v3d.m_fZ; 
	} 
	void Init(); 
	void Unit(); 
	float Length(); 
	Vector3D &operator = (const Vector3D &); 
	Vector3D operator + (const Vector3D &); 
	Vector3D &operator += (const Vector3D &); 
	Vector3D operator - (const Vector3D &); 
	Vector3D &operator -= (const Vector3D &); 
	Vector3D operator * (const float); 
	Vector3D operator / (const float); 
	friend float Dot(const Vector3D &, const Vector3D &); 
	friend Vector3D Cross(const Vector3D &, const Vector3D &); 
//	friend std::ostream operator << (std::ostream &, const Vector3D &); 
//	friend std::istream &operator >> (std::istream &, Vector3D &); 
}; 
 
#endif
