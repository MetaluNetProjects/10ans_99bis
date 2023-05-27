uniform sampler2D tex0;
uniform vec2 distance;
uniform vec2 TX;

void main (void) 
{ 

	vec2 texcoord = (gl_TextureMatrix[0] * gl_TexCoord[0]).st;

#if 1
	vec4 sample = 0.5 * texture2D(tex0, texcoord - distance);
	sample += texture2D(tex0, texcoord);
	sample += 0.5 * texture2D(tex0, texcoord + distance);

	sample /= 1.9;
	gl_FragColor =  sample;

#else

	vec4 sample1 = 0.5 * texture2D(tex0, texcoord - distance);
	vec4 sample2 = 0.5 * texture2D(tex0, texcoord + distance);

	vec4 sample0 = texture2D(tex0, texcoord);


	gl_FragColor =  max(sample1, max(sample2, sample0));
	
#endif
} 


