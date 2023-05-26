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
uniform float brightness = -0.15, contrast = 1.7, saturation = 0;

void main()
{
	vec4 col = texture2D(texture0, (gl_TextureMatrix[0] * gl_TexCoord[0]).st);

	const vec3 lumCoeff = vec3(0.2125,  0.7154, 0.0721);
	float l = min(1, 5 * length(col.rgb));

	col.rgb /= col.a;
	col.rgb += brightness;

	col.rgb = (col.rgb - 0.5) * contrast + 0.5 ;

	vec3 intens = vec3(dot(col.rgb, lumCoeff));
	col.rgb = mix(intens, col.rgb, saturation);

	col.rgb *= col.a;
	col.rgb *= pow(l,0.1);
	gl_FragColor = vec4(col.rgb, col.a);
}

