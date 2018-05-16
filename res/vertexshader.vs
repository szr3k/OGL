#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTex;

out vec3 ourColor;
out vec2 TexCoord;
uniform float fRotate;
void main()
{
	vec2 uPosition = vec2(0.0,0.0);
	uPosition.x = (cos(fRotate)*aPos.x)-(sin(fRotate)*aPos.y);
	uPosition.y = (cos(fRotate)*aPos.y) + (sin(fRotate)*aPos.x);
	gl_Position = vec4(uPosition.x , uPosition.y, aPos.z, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTex.x, aTex.y);
}