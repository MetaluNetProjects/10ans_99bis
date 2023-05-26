/* 
 * Color engine : RGB, alpha, chromaKey, saturation/contrast/brightness
 * 
 * fragment program
 * 
 * Copyright (c) 2014 Antoine Rousseau <antoine@metalu.net>
 * BSD Simplified License, see the file "LICENSE.txt" in this distribution.
 * See https://github.com/Ant1r/ofxPof for documentation and updates.
 */

#version 120
//#extension GL_ARB_texture_rectangle : enable

uniform sampler2D texture0;
//varying vec2 texCoordVarying;

// color
//uniform vec3 color = vec3(1,1,1);
uniform float delta = 0.0035;
vec2 deltaG = vec2(delta, delta);
vec2 deltaB = vec2(delta, -delta);

void main()
{
	vec2 pos = (gl_TextureMatrix[0] * gl_TexCoord[0]).st;
	/*vec4 colR = vec4(texture2D(texture0, pos).r, 0, 0, texture2D(texture0, pos).a);
	vec4 colG = vec4(0, texture2D(texture0, pos+ deltaG).g, 0, texture2D(texture0, pos+ deltaG).a);
	vec4 colB = vec4(0, 0, texture2D(texture0, pos+ deltaB).g, texture2D(texture0, pos+ deltaB).a);*/

	vec4 colR = texture2D(texture0, pos);
	vec4 colG = texture2D(texture0, pos+ deltaG);
	vec4 colB = texture2D(texture0, pos+ deltaB);

	gl_FragColor = vec4(colR.r / 3, colG.g / 1.5, colB.b / 3, colR.a + colG.a + colB.a);
}

