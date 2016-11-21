__kernel void cube(
			__global float3 *pos_buffer,
			__global float3 *vel_buffer,
			uint particles_amount)
{
    uint i;
	__global float3 *position;
	__global float3 *velocity;
	
	i = get_global_id(0);
	position = &(pos_buffer[i]);
	velocity = &(vel_buffer[i]);

	uint	sdc = cbrt((float)particles_amount);
	uint	x = fmod((float)i, (float)sdc);
	uint	y = fmod((float)i / sdc, (float)sdc);
	uint	z = i / (sdc * sdc);

	float	sds = 1.0f / sdc;
	float	sds2 = sds / 2.0f;

	position->x = x * sds - 0.5f + sds2;
	position->y = y * sds - 0.5f + sds2;
	position->z = z * sds - 0.5f + sds2;
	velocity->x = 0;
	velocity->y = 0;
	velocity->z = 0;
}


__kernel void sphere(
			__global float3 *pos_buffer,
			__global float3 *vel_buffer,
			uint particles_amount)
{
    uint i;
	__global float3 *position;
	__global float3 *velocity;

	i = get_global_id(0);
	position = &(pos_buffer[i]);
	velocity = &(vel_buffer[i]);

	float offset = 2.0f / particles_amount;
	float increment = M_PI * (3.0f - sqrt(5.0f));

	position->y = ((i * offset) - 1) + (offset / 2);
	float r = sqrt(1 - pow(position->y, 2));
	float phi = ((i + 1) % particles_amount) * increment;
	position->x = cos(phi) * r;
	position->z = sin(phi) * r;

	velocity->x = 0;
	velocity->y = 0;
	velocity->z = 0;
}

__kernel void	emit(
			__global float3 *pos_buffer,
			__global float3 *vel_buffer,
			float3 emitter)
{
	uint	i;
	float3	position;
	float3	velocity;

	i = get_global_id(0);
	position = pos_buffer[i];
	velocity = vel_buffer[i];

	position = emitter;
	velocity.x = 0.0;
	velocity.y = 0.0;
	velocity.z = 0.0;
	pos_buffer[i] = position;
	vel_buffer[i] = velocity;
}


__kernel void	update(
			__global float3 *pos_buffer,
			__global float3 *vel_buffer,
			float3 gravity_point,
			float deltaTime,
			uint click)
{
	uint	i;
	float3	position;
	float3	velocity;
	float3	force;

	i = get_global_id(0);
	position = pos_buffer[i];
	velocity = vel_buffer[i];

	if (click == 1)
		force = (gravity_point - position) * 
			(float)( 550.0f / pow(distance(gravity_point, position) + 10.0f, 2));

	force -= (velocity * 0.3f);

	float3 prev = position;
	position = position + velocity * deltaTime + 0.5f * force / 10.0f *
		(float)pow(deltaTime, 2);
	velocity = (position - prev) / deltaTime;

	velocity.z = 0;
	position.z = 0;

	pos_buffer[i] = position;
	vel_buffer[i] = velocity;
}
