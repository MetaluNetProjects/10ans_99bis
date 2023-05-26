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
uniform float colorR = 1.0;
uniform float colorG = 1.0;
uniform float colorB = 1.0;
uniform bool colorOn = true;
uniform float alpha = 1;

// chromaKey
//uniform vec3 chromaKey = vec3(0,0,0);
uniform float chromaR = 0.0;
uniform float chromaG = 0.0;
uniform float chromaB = 0.0;

uniform float chromaThreshold = 0.0;
uniform float chromaFade = 0.0;
uniform bool chromaKeyOn = true;

// contrast
uniform float brightness = 0, contrast = 1, saturation = 0;
uniform bool bcsOn = true;


void main()
{
	vec4 col = texture2D(texture0, (gl_TextureMatrix[0] * gl_TexCoord[0]).st /*texCoordVarying*/);
	vec3 color = vec3(colorR, colorG, colorB);
	// chromaKey
	vec3 chromaKey = vec3(chromaR, chromaG, chromaB);
	if (chromaKeyOn) col.a *= clamp((distance(chromaKey, col.rgb) - chromaThreshold) / chromaFade, 0, 1);	
		
	// contrast
	if (bcsOn){
		const vec3 lumCoeff = vec3(0.2125,  0.7154, 0.0721);
		float l = min(1, 5 * length(col.rgb));

		col.rgb /= col.a;
		col.rgb += brightness;

		col.rgb = (col.rgb - 0.5) * contrast + 0.5 ;

		vec3 intens = vec3(dot(col.rgb, lumCoeff));
		col.rgb = mix(intens, col.rgb, saturation);

		col.rgb *= col.a;
		col.rgb *= pow(l,0.1);
	}
	
	// color
	if (colorOn) col.rgb *= color;
	
	// alpha
	 gl_FragColor = vec4(col.rgb, col.a*alpha);
}

