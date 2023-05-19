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

uniform sampler2D maskImage;
uniform sampler2D image;
uniform sampler2D disque;
uniform float scale = 1;
uniform float x = 0.5;
uniform float y = 0.5;
uniform float mixDisque = 1.0;
uniform float alpha = 1.0;

void main()
{
	vec2 coord = (gl_TextureMatrix[0] * gl_TexCoord[0]).st;
	vec2 imgCoord = (coord - vec2(0.5, 0.5)) / scale + vec2(x, y);
	vec4 mask = texture2D(maskImage, coord);
	vec4 col = texture2D(image, imgCoord);
	vec4 disqueCol = texture2D(disque, coord);
	//col.a = mask.a;
	//disqueCol.a *= (1 - mask.a);
	gl_FragColor = col * mask.a + mixDisque * disqueCol * (1 - mask.a);
	gl_FragColor.a *= alpha;
}

