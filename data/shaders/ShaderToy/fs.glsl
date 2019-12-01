#ifdef GL_ES
precision mediump float;
#endif
void main( void ) {

	float dist = distance(gl_FragCoord.xy, vec2(0.5,0.5));
	float color = 0.0;
	if(dist<100.0)
		color=1.0;
	else
		color=0.0;
	gl_FragColor = vec4(color,color,color,color);

}
