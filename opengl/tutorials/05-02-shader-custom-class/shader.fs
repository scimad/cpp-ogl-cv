#version 330 core
out vec4 FragColor;
uniform float greenColor;
uniform float redColor;
uniform float blueColor;
void main(){
    FragColor = vec4(redColor, greenColor, blueColor, 1.0);
};