#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform int myrecord;

void main()
{
    if(myrecord==0){
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.5);}
    else if(myrecord==1){
    FragColor = texture(texture1, TexCoord);}
}
