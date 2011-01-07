#include "vector.h" 
void Vector3D::Init() 
{ 
	m_fX = 0.0f; 
	m_fY = 0.0f; 
	m_fZ = 0.0f; 
} 
void Vector3D::Unit() 
{ 
	double a = sqrt(this->m_fX * this->m_fX + this->m_fY * this->m_fY + this->m_fZ * this->m_fZ); 
	if (a != 0.0) 
	{ 
		this->m_fX = this->m_fX / a; 
		this->m_fY = this->m_fY / a; 
		this->m_fZ = this->m_fZ / a; 
	} 
} 
float Vector3D::Length() 
{ 
	return sqrt(this->m_fX * this->m_fX + this->m_fY * this->m_fY + this->m_fZ * this->m_fZ); 
} 
Vector3D &Vector3D::operator = (const Vector3D &v3d) 
{ 
	this->m_fX = v3d.m_fX;  
	this->m_fY = v3d.m_fY; 
	this->m_fZ = v3d.m_fZ; 
	return *this; 
} 
Vector3D Vector3D::operator + (const Vector3D &v3d) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX + v3d.m_fX;  
	fY = this->m_fY + v3d.m_fY; 
	fZ = this->m_fZ + v3d.m_fZ; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
Vector3D &Vector3D::operator += (const Vector3D &v3d) 
{ 
	this->m_fX += v3d.m_fX; 
	this->m_fY += v3d.m_fY; 
	this->m_fZ += v3d.m_fZ; 
	return *this; 
} 
Vector3D Vector3D::operator - (const Vector3D &v3d) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX - v3d.m_fX; 
	fY = this->m_fY - v3d.m_fY; 
	fZ = this->m_fZ - v3d.m_fZ; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
Vector3D &Vector3D::operator -= (const Vector3D &v3d) 
{ 
	this->m_fX -= v3d.m_fX; 
	this->m_fY -= v3d.m_fY; 
	this->m_fZ -= v3d.m_fZ; 
	return *this; 
} 
Vector3D Vector3D::operator * (const float ft) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX * ft; 
	fY = this->m_fY * ft; 
	fZ = this->m_fZ * ft; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
Vector3D Vector3D::operator / (const float ft) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX / ft; 
	fY = this->m_fY / ft; 
	fZ = this->m_fZ / ft; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
float Dot(const Vector3D &v3d1, const Vector3D &v3d2) 
{ 
	float fX, fY, fZ; 
	fX = v3d1.m_fX * v3d2.m_fX; 
	fY = v3d1.m_fY * v3d2.m_fY; 
	fZ = v3d1.m_fZ * v3d2.m_fZ; 
	return (fX + fY + fZ); 
} 
Vector3D Cross(const Vector3D &v3d1, const Vector3D &v3d2) 
{ 
	float fX, fY, fZ; 
	fX = v3d1.m_fY * v3d2.m_fZ - v3d1.m_fZ * v3d2.m_fY; 
	fY = v3d1.m_fZ * v3d2.m_fX - v3d1.m_fX * v3d2.m_fZ; 
	fZ = v3d1.m_fX * v3d2.m_fY - v3d1.m_fY * v3d2.m_fX; 
	Vector3D re(fX, fY, fZ); 
	return re; 
}
/*
std::ostream operator << (std::ostream &ot, const Vector3D v3d) 
{ 
	ot << "(" << v3d.m_fX << "," << v3d.m_fY << "," << v3d.m_fZ << ")"; 
	return ot; 
} 
std::istream &operator >> (std::istream &it, Vector3D &v3d) 
{ 
	it >> v3d.m_fX >> v3d.m_fY >> v3d.m_fZ; 
	return it; 
}
*/
