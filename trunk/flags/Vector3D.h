<html><head><title>SimCloth.zip Vector3D.h</title>
<LINK href="/inc/read_style.css" type=text/css rel=stylesheet></head>
<body>
<p><a href=http://www.pudn.com>www.pudn.com</a> &gt; <a href="http://www.pudn.com/downloads78/sourcecode/graph/detail298391.html">SimCloth.zip</a> &gt Vector3D.h, change:2006-11-28,size:1825b</p><!-- saved from http://www.pudn.com -->
<script src="/inc/gg_read1.js"></script><BR>
<pre name="code" class="h">
/* ========================================================================= * 
 *	Name:		Vector3d.h                                                   * 
 *	Function:	Define the class Vector3D. This class is used to deal with   * 
 *              vectors in 3D world.                                         * 
 *	Date:		2006-11-20                                                   * 
 *	Editor:		jixing_alex                                                  * 
 * ========================================================================= */ 
 
#ifndef __VECTOR3D_H 
#define __VECTOR3D_H 
 
// Include 
#include <iostream> 
#include <cmath> 
 
// Declaration of the class Vector3D 
class Vector3D 
{ 
// The class's data members 
public: 
	float m_fX, m_fY, m_fZ;						// Three weights of a vector in 3D world 
	 
// The class's functions 
public: 
	Vector3D::Vector3D () 
	{ 
		this->m_fX = 0.0f; 
		this->m_fY = 0.0f; 
		this->m_fZ = 0.0f; 
	} 
 
	Vector3D::Vector3D(float xi, float yi, float zi) 
	{ 
		this->m_fX = xi; 
		this->m_fY = yi; 
		this->m_fZ = zi; 
	} 
 
	Vector3D::Vector3D(const Vector3D &v3d) 
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
	 
	friend std::ostream operator << (std::ostream &, const Vector3D &); 
	friend std::istream &operator >> (std::istream &, Vector3D &); 
}; 
 
#endif		// !__VECTOR3D_H</pre>
<script src="/inc/gg_read2.js"></script><BR>
<script src="http://s117.cnzz.com/stat.php?id=1236358&web_id=1236358&show=pic" language="JavaScript" charset="gb2312"></script>
</body></html>
