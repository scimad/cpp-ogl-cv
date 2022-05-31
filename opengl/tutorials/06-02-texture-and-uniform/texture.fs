#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 TexCoord;

uniform float r, g, b;
uniform sampler2D ourTexture;

void main(){
    // FragColor = texture(ourTexture, TexCoord);
    FragColor = texture(ourTexture, TexCoord) * vec4(r, g, b, 1.0);

};