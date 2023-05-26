#version 120
/* 
 * Color engine : RGB, alpha, chromaKey, saturation/contrast/brightness
 * 
 * vertex program
 * 
 * Copyright (c) 2014 Antoine Rousseau <antoine@metalu.net>
 * BSD Simplified License, see the file "LICENSE.txt" in this distribution.
 * See https://github.com/Ant1r/ofxPof for documentation and updates.
 */


//varying vec2 texCoordVarying;


void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_Position = ftransform();
}

