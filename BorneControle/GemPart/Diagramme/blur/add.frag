#version 120
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform float mix0 = 1.0;
uniform float mix1 = 0.5;

uniform float delta = 0.0015;
vec2 deltaG = vec2(delta, delta);
vec2 deltaB = vec2(delta, -delta);

void main (void) 
{ 

	vec2 pos = (gl_TextureMatrix[0] * gl_TexCoord[0]).st;
	vec4 colR = texture2D(tex0, pos);
	vec4 colG = texture2D(tex0, pos+ deltaG);
	vec4 colB = texture2D(tex0, pos+ deltaB);
	vec4 sample0 = //texture2D(tex0, texcoord);
					vec4(colR.r , colG.g , colB.b , colR.a + colG.a + colB.a);

	vec4 sample1 = texture2D(tex1, pos);

	gl_FragColor =  mix0 * sample0 + mix1 * sample1;
} 


