#version 450

layout(points) in;
layout(triangle_strip, max_vertices=12) out;

uniform mat4 mvp;

void main()
{
	gl_Position = mvp * (gl_in[0].gl_Position + vec4(0, 0.007, 0, 0));
    EmitVertex();
	gl_Position = mvp * (gl_in[0].gl_Position + vec4(-0.007, -0.007, -0.007, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0.007, -0.007, -0.007, 0));
    EmitVertex();
 	EndPrimitive();
 	
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0, 0.007, 0, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0, -0.007, 0.007, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(-0.007, -0.007, -0.007, 0));
    EmitVertex();
 	EndPrimitive();
 	
 	gl_Position = mvp * (gl_in[0].gl_Position + vec4(0, 0.007, 0, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0.007, -0.007, -0.007, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0, -0.007, 0.007, 0));
    EmitVertex();
    EndPrimitive();
    
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(-0.007, -0.007, -0.007, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0, -0.007, 0.007, 0));
    EmitVertex();
    gl_Position = mvp * (gl_in[0].gl_Position + vec4(0.007, -0.007, -0.007, 0));
    EmitVertex();
    EndPrimitive();
}