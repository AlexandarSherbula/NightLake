#type vertex
#version 450 core
			
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
};

layout(location = 0) out VertexOutput outVertex;

void main()
{
    outVertex.color = aColor;
	outVertex.texCoord = aTexCoord;
	gl_Position = vec4(aPosition, 1.0);
}

#type pixel
#version 450 core

struct VertexOutput
{
	vec4 color;
	vec2 texCoord;
};

layout(location = 0) in VertexOutput inVertex;

uniform sampler2D uImage;
			
out vec4 pixel;

void main()
{
    pixel = texture(uImage, inVertex.texCoord) * vec4(inVertex.color);
}