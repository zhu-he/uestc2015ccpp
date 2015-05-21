uniform sampler2D texture;
uniform float shadow_distance;

void main()
{
    vec2 offx = vec2(shadow_distance, 0.0);
    vec2 offy = vec2(0.0, shadow_distance);
    if (texture2D(texture, gl_TexCoord[0].xy).a == 0)
    {
        gl_FragColor =  gl_Color * texture2D(texture, gl_TexCoord[0].xy - offx - offy) / 2;
        gl_FragColor.a /= 4;
    }
    else
    {
        gl_FragColor =  gl_Color * texture2D(texture, gl_TexCoord[0].xy);
    }
}
