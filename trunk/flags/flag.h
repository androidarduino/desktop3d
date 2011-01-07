#ifndef FLAG_H 
#define FLAG_H 
#include <iostream> 
#include <cmath> 
#include "vector.h" 
#define GRAVITY		9.81f						// Gravity in scene 
#define MASS		1.0f						// The mass of every point 
#define QUOTIETY	21.0f						// Quotiety between adjacent points 
#define SIZEU		15							// Number of point in horizontal axis 
#define SIZEV		15							// Number of point in vertical axis 
#define WIDTH		400.0f						// Mesh's width 
#define LENGTH		240.0f						// Mesh's length 
#define FTIME		0.5f						// Interval 
class ClothMesh 
{ 
public: 
	Vector3D m_vPosition[SIZEV][SIZEU];			// Every point's position in cloth's mesh 
	Vector3D m_vNormal[SIZEV][SIZEU];			// Every point's normal vector in cloth's mesh 
	Vector3D m_vStretch[SIZEV][SIZEU];			// Every point's vector of the force(strecth) in cloth's mesh 
	Vector3D m_vShear[SIZEV][SIZEU];			// Every point's vector of the force(shear) in cloth's mesh 
	Vector3D m_vSpeed[SIZEV][SIZEU];			// Every point's speed in cloth's mesh 
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
#endif
