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

__kernel void	update(
			__global float3 *pos_buffer,
			__global float3 *vel_buffer,
			float4 gravity_point,
			float deltaTime,
			uint click)
{
	uint	i;
	float3	position;
	float3	velocity;
	float2	gp;
	float2	force;
	float2	pos2;
	float2	vel2;

	i = get_global_id(0);
	position = pos_buffer[i];
	velocity = vel_buffer[i];

	pos2.x = position.x;
	pos2.y = position.y;

	vel2.x = velocity.x;
	vel2.y = velocity.y;

	gp.x = gravity_point.x;
	gp.y = gravity_point.y;

	force.x = 0;
	force.y = 0;

	if (click == 1)
		force = (gp - pos2) * (float)( 550.0f / pow(distance(gp, pos2) + 10.0f, 2));

	force -= (vel2 * 0.3f);

	float2 prev = pos2;
	pos2 = pos2 + vel2 * deltaTime + 0.5f * force / 10.0f * (float)pow(deltaTime, 2);
	vel2 = (pos2 - prev) / deltaTime;


	pos_buffer[i].x = pos2.x;
	pos_buffer[i].y = pos2.y;
	vel_buffer[i].x = vel2.x;
	vel_buffer[i].y = vel2.y;
}
