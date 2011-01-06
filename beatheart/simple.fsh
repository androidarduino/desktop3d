void main(void)
{
    gl_position=glModelViewProjectionMatrix * gl_Vertex;
    gl_FragColor=glColor;
}
