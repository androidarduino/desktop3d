void main(void)
{
gl_Position=gl_ModelViewProjectionMatrix*gl_Vertex;
vec4 V=gl_ModelViewMatrix*gl_Vertex;
gl_FrontColor=gl_Color;
float ptSize=length(V);
ptSize*=ptSize;
gl_PointSize=100000.0/ptSize;
}
