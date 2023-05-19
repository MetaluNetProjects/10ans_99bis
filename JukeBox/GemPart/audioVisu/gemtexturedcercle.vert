//
#version 120

//varying vec2 texcoord;
//varying vec2 coord;
void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
	//coord = gl_MultiTexCoord0;
    // perform standard transform on vertex
    gl_Position = ftransform();
}

/*//
//precision highp float;
uniform mat4 modelViewProjectionMatrix;
attribute vec2 texcoord;
attribute vec4 position;

varying vec2 coord;

void main()
{
    coord = texcoord;

    gl_Position = modelViewProjectionMatrix * position;
}*/
