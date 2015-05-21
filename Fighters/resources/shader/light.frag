uniform vec2 frag_LightOrigin;
uniform vec3 frag_LightColor;
uniform float frag_LightAttenuation;

void main()
{
	float attenuation = 1.0 / (frag_LightAttenuation * length(frag_LightOrigin - gl_FragCoord.xy));
	gl_FragColor = vec4(attenuation, attenuation, attenuation, 1.0) * vec4(frag_LightColor, 1.0);
}