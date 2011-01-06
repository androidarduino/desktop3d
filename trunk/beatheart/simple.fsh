void main(void)
{
    gl_Position=gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_FragColor=gl_Color/2;
}
