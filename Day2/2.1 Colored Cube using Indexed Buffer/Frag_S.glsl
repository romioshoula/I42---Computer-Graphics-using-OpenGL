#version 330

in vec4 frag_color;
void main()
{
	//gl_FragColor=vec4(0,1,1,1);
	gl_FragColor=frag_color;
}