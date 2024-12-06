#version 330 core

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inCol;

out vec3 chCol;

uniform float uRx;
uniform float uRy;
uniform vec2 uTranslate;

void main()
{
	vec2 scaledPosition = vec2(inPos.x * uRx, inPos.y * uRy);
    vec2 translatedPosition = scaledPosition + uTranslate;
	gl_Position = vec4(translatedPosition, 0.0, 1.0);

	chCol = inCol;
}