void main(void)
{
float gray=dot(gl_Color.rgb, vec3(0.299,0.587,0.114));
gl_FragColor=vec4(gray,gray,gray,1.0);
}
