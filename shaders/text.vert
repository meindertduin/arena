#version 330 core
layout (location = 0) in vec2 aPos; // <vec2 pos, vec2 tex>
layout (location = 1) in vec2 aTexCoords; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(aPos, 0.0, 1.0);
    TexCoords = aTexCoords;
}  