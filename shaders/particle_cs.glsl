#version 450

layout(local_size_x = 32) in;

struct Particle
{	vec3 pos;
	vec3 vel;
};

layout(binding = 1) buffer ParticleBuffer {
	Particle particles[];
};

uniform float current_time;
uniform float delta_time;

void main()
{	vec3 singularity = vec3(0.0, 0.0, 0.0);
	vec3 point = particles[gl_GlobalInvocationID.x].pos;
	vec3 accel = (singularity - point) / 1024;
	vec3 v0 = particles[gl_GlobalInvocationID.x].vel;
	vec3 v = v0 + accel;
	float vlen = length(v);
	//if(vlen > 2) v = normalize(v)*2;
	particles[gl_GlobalInvocationID.x].pos = point + delta_time*(v0 + v)/2.0;
	particles[gl_GlobalInvocationID.x].vel = v;
}