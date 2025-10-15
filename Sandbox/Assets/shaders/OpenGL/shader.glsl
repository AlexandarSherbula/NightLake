#type vertex
#version 450 core
			
layout (location = 0) in vec2 aPosition;

void main()
{	
	gl_Position = vec4(aPosition, 1.0, 1.0);
}

#type pixel
#version 450 core
			
out vec4 pixel;

void main()
{
    pixel = vec4(0.0, 0.0, 1.0, 1.0);
}