uniform sampler2D texture;
uniform vec4 uColorAdd;
uniform vec4 uColorMul;
uniform mat4 uColorTransform;

void main()
{
    // récupère le pixel dans la texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    pixel +=  uColorAdd;
    pixel *=  uColorMul;

    pixel = uColorTransform * pixel;

    // et multiplication avec la couleur pour obtenir le pixel final
    gl_FragColor = gl_Color * pixel;
}