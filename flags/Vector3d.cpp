<html><head><title>SimCloth.zip Vector3d.cpp</title>
<LINK href="/inc/read_style.css" type=text/css rel=stylesheet></head>
<body>
<p><a href=http://www.pudn.com>www.pudn.com</a> &gt; <a href="http://www.pudn.com/downloads78/sourcecode/graph/detail298391.html">SimCloth.zip</a> &gt Vector3d.cpp, change:2006-11-28,size:3442b</p><!-- saved from http://www.pudn.com -->
<script src="/inc/gg_read1.js"></script><BR>
<pre name="code" class="cpp">
/* ========================================================================= * 
 *	Name:		Vector3d.cpp                                                 * 
 *	Function:	Implement the class Vector3D                                 * 
 *	Date:		2006-11-20                                                   * 
 *	Editor:		jixing_alex                                                  * 
 * ========================================================================= */ 
 
#include "Vector3d.h" 
 
// Initialize the class. All variable of the class will become zero 
void Vector3D::Init() 
{ 
	m_fX = 0.0f; 
	m_fY = 0.0f; 
	m_fZ = 0.0f; 
} 
 
// Hold formerly direction, but it's lenght will be one 
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
 
// Return the vector's length 
float Vector3D::Length() 
{ 
	return sqrt(this->m_fX * this->m_fX + this->m_fY * this->m_fY + this->m_fZ * this->m_fZ); 
} 
 
// Operation = in vectors 
Vector3D &Vector3D::operator = (const Vector3D &v3d) 
{ 
	this->m_fX = v3d.m_fX;  
	this->m_fY = v3d.m_fY; 
	this->m_fZ = v3d.m_fZ; 
	return *this; 
} 
 
// Operation + in vectors 
Vector3D Vector3D::operator + (const Vector3D &v3d) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX + v3d.m_fX;  
	fY = this->m_fY + v3d.m_fY; 
	fZ = this->m_fZ + v3d.m_fZ; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
 
// Operation += in vectors 
Vector3D &Vector3D::operator += (const Vector3D &v3d) 
{ 
	this->m_fX += v3d.m_fX; 
	this->m_fY += v3d.m_fY; 
	this->m_fZ += v3d.m_fZ; 
	return *this; 
} 
 
// Operation - in vectors 
Vector3D Vector3D::operator - (const Vector3D &v3d) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX - v3d.m_fX; 
	fY = this->m_fY - v3d.m_fY; 
	fZ = this->m_fZ - v3d.m_fZ; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
 
// Operation -= in vectors 
Vector3D &Vector3D::operator -= (const Vector3D &v3d) 
{ 
	this->m_fX -= v3d.m_fX; 
	this->m_fY -= v3d.m_fY; 
	this->m_fZ -= v3d.m_fZ; 
	return *this; 
} 
 
// Operation * in vectors 
Vector3D Vector3D::operator * (const float ft) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX * ft; 
	fY = this->m_fY * ft; 
	fZ = this->m_fZ * ft; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
 
// Operation / in vectors 
Vector3D Vector3D::operator / (const float ft) 
{ 
	float fX, fY, fZ; 
	fX = this->m_fX / ft; 
	fY = this->m_fY / ft; 
	fZ = this->m_fZ / ft; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
 
// Dot multiplication in vectors 
float Dot(const Vector3D &v3d1, const Vector3D &v3d2) 
{ 
	float fX, fY, fZ; 
	fX = v3d1.m_fX * v3d2.m_fX; 
	fY = v3d1.m_fY * v3d2.m_fY; 
	fZ = v3d1.m_fZ * v3d2.m_fZ; 
	return (fX + fY + fZ); 
} 
 
// Cross multiplication in vectors 
Vector3D Cross(const Vector3D &v3d1, const Vector3D &v3d2) 
{ 
	float fX, fY, fZ; 
	fX = v3d1.m_fY * v3d2.m_fZ - v3d1.m_fZ * v3d2.m_fY; 
	fY = v3d1.m_fZ * v3d2.m_fX - v3d1.m_fX * v3d2.m_fZ; 
	fZ = v3d1.m_fX * v3d2.m_fY - v3d1.m_fY * v3d2.m_fX; 
	Vector3D re(fX, fY, fZ); 
	return re; 
} 
 
// Output stream operation 
std::ostream operator << (std::ostream &ot, const Vector3D v3d) 
{ 
	ot << "(" << v3d.m_fX << "," << v3d.m_fY << "," << v3d.m_fZ << ")"; 
	return ot; 
} 
 
// Input stream operation 
std::istream &operator >> (std::istream &it, Vector3D &v3d) 
{ 
	it >> v3d.m_fX >> v3d.m_fY >> v3d.m_fZ; 
	return it; 
}</pre>
<script src="/inc/gg_read2.js"></script><BR>
<script src="http://s117.cnzz.com/stat.php?id=1236358&web_id=1236358&show=pic" language="JavaScript" charset="gb2312"></script>
</body></html>
