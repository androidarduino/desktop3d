<html><head><title>SimCloth.zip ClothMesh.cpp</title>
<LINK href="/inc/read_style.css" type=text/css rel=stylesheet></head>
<body>
<p><a href=http://www.pudn.com>www.pudn.com</a> &gt; <a href="http://www.pudn.com/downloads78/sourcecode/graph/detail298391.html">SimCloth.zip</a> &gt ClothMesh.cpp, change:2006-11-28,size:13401b</p><!-- saved from http://www.pudn.com -->
<script src="/inc/gg_read1.js"></script><BR>
<pre name="code" class="cpp">
/* ========================================================================= * 
 *	Name:		ClothMesh.cpp                                                * 
 *	Function:	Implement class ClothMesh.                                   * 
 *	Date:		2006-11-21                                                   * 
 *	Editor:		jixing_alex                                                  * 
 * ========================================================================= */ 
 
#include "ClothMesh.h" 
 
// Refresh point's data in cloth's mesh after interval 
void ClothMesh::DealMesh(void) 
{ 
	int i, j; 
	float fWidth, fLength, fCross;				// Record lengths for three state between adjacent points in unforce 
	Vector3D vForce[SIZEV][SIZEU];				// Composition of forces that include stretch and shear 
	Vector3D vLength;							// Vector between adjacent points. We need it's length and direction 
	Vector3D vNormal;							// Normal vector of every point in cloth's mesh 
	float fTmp;									// Record a temporary length value between adjacent points 
 
	fWidth = WIDTH / (SIZEU - 1); 
	fLength = LENGTH / (SIZEV - 1); 
	fCross = sqrt(fWidth * fWidth + fLength * fLength); 
 
	// Computer every point's composition of forces, position and speed 
	for(i = 0; i < SIZEV; i++) 
	{ 
		for(j = 0; j < SIZEU; j++) 
		{ 
			vForce[i][j] = m_vStretch[i][j] + m_vShear[i][j] - Vector3D(0.0f, GRAVITY, 0.0f); 
			if(!((i == (SIZEV - 1)) && ((j == 0) || (j == SIZEU - 1))))				// Except two points in top left and top right corner 
				m_vPosition[i][j] += m_vSpeed[i][j] * FTIME + vForce[i][j] * FTIME * FTIME / 2.0f / MASS * 0.1f; 
			m_vSpeed[i][j] += vForce[i][j] * FTIME / MASS * 0.01f; 
		} 
	} 
 
	// Computer every point's stretch and shear forces 
	for(i = 0; i < SIZEV; i++) 
	{ 
		for(j = 0; j < SIZEU; j++) 
		{ 
			// For special situations, we need special ways to solute it 
			if(i == 0) 
			{ 
				// While the point is in first row, 
				// the adjacent point will stretched it in second row 
				vLength = m_vPosition[i + 1][j] - m_vPosition[i][j]; 
				fTmp = vLength.Length() - fLength; 
				vLength.Unit(); 
				m_vStretch[i][j] = vLength * fTmp * QUOTIETY; 
				if(j == 0) 
				{ 
					// While the point is in first column, 
					// the adjacent point of second column will stretched it 
					vLength = m_vPosition[i][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
 
					// While the point is in both first row and first column, 
					// it will be sheared by the only point that is in second row and second column 
					vLength = m_vPosition[i + 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i][j + 1] - m_vPosition[i][j], m_vPosition[i + 1][j] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
				else if(j == SIZEU - 1) 
				{ 
					// While the point is in last column, 
					// the adjacent point of last but one column will stretched it 
					vLength = m_vPosition[i][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
 
					// While the point is in both first row and last column, 
					// it will be sheared by the only point that is in second row and last but one column 
					vLength = m_vPosition[i + 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i + 1][j] - m_vPosition[i][j], m_vPosition[i][j - 1] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
				else 
				{ 
					// While the point is in neither first nor last column, 
					// it will be stretched by two adjacent points that is in first row 
					vLength = m_vPosition[i][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
 
					// While the point is in both first row and is in neither first nor last column, 
					// it will be sheared by two adjacent diagonally points that is in second row 
					vLength = m_vPosition[i + 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i + 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i][j + 1] - m_vPosition[i][j], m_vPosition[i + 1][j] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i + 1][j] - m_vPosition[i][j], m_vPosition[i][j - 1] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
			} 
			else if(i == SIZEV - 1) 
			{ 
				// While the point is in last row, 
				// the adjacent point will stretched it in last but one row 
				vLength = m_vPosition[i - 1][j] - m_vPosition[i][j]; 
				fTmp = vLength.Length() - fLength; 
				vLength.Unit(); 
				m_vStretch[i][j] = vLength * fTmp * QUOTIETY; 
				if(j == 0) 
				{ 
					// While the point is in first column, 
					// the adjacent point of second column will stretched it 
					vLength = m_vPosition[i][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
					 
					// While the point is in both last row and first column, 
					// it will be sheared by the only point that is in last but one row and second column 
					vLength = m_vPosition[i - 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i - 1][j] - m_vPosition[i][j], m_vPosition[i][j + 1] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
				else if(j == SIZEU - 1) 
				{ 
					// While the point is in last column, 
					// the adjacent point of last but one column will stretched it 
					vLength = m_vPosition[i][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
					 
					// While the point is in both last row and last column, 
					// it will be sheared by the only point that is in last but one row and last but one column 
					vLength = m_vPosition[i - 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i][j - 1] - m_vPosition[i][j], m_vPosition[i - 1][j] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
				else 
				{ 
					// While the point is in neither first nor last column, 
					// it will be stretched by two adjacent points that is in last row 
					vLength = m_vPosition[i][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
					 
					// While the point is in last row and is in neither first nor last column, 
					// it will be sheared by two adjacent diagonally point that is in last but one row 
					vLength = m_vPosition[i - 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i - 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i - 1][j] - m_vPosition[i][j], m_vPosition[i][j + 1] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i][j - 1] - m_vPosition[i][j], m_vPosition[i - 1][j] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
			} 
			else 
			{ 
				// While the point is in neither first nor last row, 
				// it will be stretched two adjacent points that is in same row 
				vLength = m_vPosition[i + 1][j] - m_vPosition[i][j]; 
				fTmp = vLength.Length() - fLength; 
				vLength.Unit(); 
				m_vStretch[i][j] = vLength * fTmp * QUOTIETY; 
				vLength = m_vPosition[i - 1][j] - m_vPosition[i][j]; 
				fTmp = vLength.Length() - fLength; 
				vLength.Unit(); 
				m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
				if(j == 0) 
				{ 
					// While the point is in first column, 
					// the adjacent point of second column will stretched it 
					vLength = m_vPosition[i][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
 
					// While the point is in neither first nor last row and is in first column, 
					// it will be sheared by two adjacent diagonally points that is in second column 
					vLength = m_vPosition[i + 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i - 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i - 1][j] - m_vPosition[i][j], m_vPosition[i][j + 1] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i][j + 1] - m_vPosition[i][j], m_vPosition[i + 1][j] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
				else if(j == SIZEU - 1) 
				{ 
					// While the point is in last column, 
					// the adjacent point of last but one column will stretched it 
					vLength = m_vPosition[i][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
 
					// While the point is in neither first nor last row and is in last column, 
					// it will be sheared by two adjacent diagonally points that is in last but one column 
					vLength = m_vPosition[i + 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i - 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i + 1][j] - m_vPosition[i][j], m_vPosition[i][j - 1] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i][j - 1] - m_vPosition[i][j], m_vPosition[i - 1][j] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
				else 
				{ 
					// While the point is in neither first nor last column, 
					// it will be stretched by two adjacent points that is in same row 
					vLength = m_vPosition[i][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fWidth; 
					vLength.Unit(); 
					m_vStretch[i][j] += vLength * fTmp * QUOTIETY; 
 
					// While the point is in neither first nor last row and is in neither first nor last column, 
					// it will be sheared by four adjacent diagonally points 
					vLength = m_vPosition[i + 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] = vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i - 1][j + 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i + 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
					vLength = m_vPosition[i - 1][j - 1] - m_vPosition[i][j]; 
					fTmp = vLength.Length() - fCross; 
					vLength.Unit(); 
					m_vShear[i][j] += vLength * fTmp * QUOTIETY; 
 
					// Computer normal vector of the point 
					vNormal = Cross(m_vPosition[i][j + 1] - m_vPosition[i][j], m_vPosition[i + 1][j] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i + 1][j] - m_vPosition[i][j], m_vPosition[i][j - 1] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i - 1][j] - m_vPosition[i][j], m_vPosition[i][j + 1] - m_vPosition[i][j]); 
					vNormal += Cross(m_vPosition[i][j - 1] - m_vPosition[i][j], m_vPosition[i - 1][j] - m_vPosition[i][j]); 
					vNormal.Unit(); 
					m_vNormal[i][j] = vNormal; 
				} 
			} 
		} 
	} 
}</pre>
<script src="/inc/gg_read2.js"></script><BR>
<script src="http://s117.cnzz.com/stat.php?id=1236358&web_id=1236358&show=pic" language="JavaScript" charset="gb2312"></script>
</body></html>
