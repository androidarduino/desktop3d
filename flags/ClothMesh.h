<html><head><title>SimCloth.zip ClothMesh.h</title>
<LINK href="/inc/read_style.css" type=text/css rel=stylesheet></head>
<body>
<p><a href=http://www.pudn.com>www.pudn.com</a> &gt; <a href="http://www.pudn.com/downloads78/sourcecode/graph/detail298391.html">SimCloth.zip</a> &gt ClothMesh.h, change:2006-11-28,size:2706b</p><!-- saved from http://www.pudn.com -->
<script src="/inc/gg_read1.js"></script><BR>
<pre name="code" class="h">
/* ========================================================================= * 
 *	Name:		ClothMesh.h                                                  * 
 *	Function:	Define class ClothMesh. This class is used to deal with      * 
 *              cloth's mesh in 3D world.                                    * 
 *				And define some constant for cloth and mesh. For example,    * 
 *              gravity in scene, quotiety of cloth, ...                     * 
 *	Date:		2006-11-21                                                   * 
 *	Editor:		jixing_alex                                                  * 
 * ========================================================================= */ 
 
#ifndef __CLOTHMESH_H 
#define __CLOTHMESH_H 
 
// Include 
#include <iostream> 
#include <cmath> 
#include "Vector3D.h" 
 
// Declaration some constants 
#define GRAVITY		9.81f						// Gravity in scene 
#define MASS		1.0f						// The mass of every point 
#define QUOTIETY	21.0f						// Quotiety between adjacent points 
 
#define SIZEU		15							// Number of point in horizontal axis 
#define SIZEV		15							// Number of point in vertical axis 
#define WIDTH		200.0f						// Mesh's width 
#define LENGTH		240.0f						// Mesh's length 
 
#define FTIME		0.5f						// Interval 
 
class ClothMesh 
{ 
// The class's data members 
public: 
	Vector3D m_vPosition[SIZEV][SIZEU];			// Every point's position in cloth's mesh 
	Vector3D m_vNormal[SIZEV][SIZEU];			// Every point's normal vector in cloth's mesh 
	Vector3D m_vStretch[SIZEV][SIZEU];			// Every point's vector of the force(strecth) in cloth's mesh 
	Vector3D m_vShear[SIZEV][SIZEU];			// Every point's vector of the force(shear) in cloth's mesh 
	Vector3D m_vSpeed[SIZEV][SIZEU];			// Every point's speed in cloth's mesh 
 
// The class's functions 
public: 
	ClothMesh() 
	{ 
		int i, j; 
 
		for(i = 0; i < SIZEV; i++) 
			for(j = 0; j < SIZEU; j++) 
				m_vPosition[i][j] = Vector3D(j * WIDTH / (SIZEU - 1) - WIDTH / 2.0f, 
				                     i * LENGTH / (SIZEV - 1) - LENGTH / 2.0f, 
									 0.0f); 
		m_vPosition[SIZEV - 1][0] += Vector3D(0.0f, 0.0f, 2.0f); 
		m_vPosition[SIZEV - 1][SIZEU - 1] += Vector3D(0.0f, 0.0f, 2.0f); 
 
		for(i = 0; i < SIZEV; i++) 
			for(j = 0; j < SIZEU; j++) 
				m_vNormal[i][j] = Vector3D(0.0f, 0.0f, 1.0f); 
 
		for(i = 0; i < SIZEV; i++) 
			for(j = 0; j < SIZEU; j++) 
				m_vStretch[i][j] = Vector3D(0.0f, 0.0f, 0.0f); 
 
		for(i = 0; i < SIZEV; i++) 
			for(j = 0; j < SIZEU; j++) 
				m_vShear[i][j] = Vector3D(0.0f, 0.0f, 0.0f); 
 
		for(i = 0; i < SIZEV; i++) 
			for(j = 0; j < SIZEU; j++) 
				m_vSpeed[i][j] = Vector3D(0.0f, 0.0f, 0.0f); 
	} 
 
	void DealMesh(void); 
}; 
 
#endif		// !__CLOTHMESH_H</pre>
<script src="/inc/gg_read2.js"></script><BR>
<script src="http://s117.cnzz.com/stat.php?id=1236358&web_id=1236358&show=pic" language="JavaScript" charset="gb2312"></script>
</body></html>
