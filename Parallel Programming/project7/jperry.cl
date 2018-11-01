typedef float4 point;
typedef float4 vector;
typedef float4 color;
typedef float4 sphere;

vector
Bounce( vector in, vector n )
{
	vector out = in - n*(vector)( 2.*dot(in.xyz, n.xyz) );
	out.w = 0.;
	return out;
}

vector
BounceSphere( point p, vector v, sphere s )
{
	vector n;
	n.xyz = fast_normalize( p.xyz - s.xyz );
	n.w = 0.;
	return Bounce( v, n );
}

bool
IsInsideSphere( point p, sphere s )
{
	float r = fast_length( p.xyz - s.xyz );
	return  ( r < s.w );
}

kernel
void
Particle( global point *dPobj, global vector *dVel, global color *dCobj)
{
	const float4 G       = (float4) ( 0., -9.8, 0., 0. );
	const float  DT      = 0.1;
	const sphere Sphere1 = (sphere)( -550., -800., 0.,  300. );
	const sphere Sphere2 = (sphere)( 550., -800., 0.,  300. );
	int gid = get_global_id( 0 );

	point  p = dPobj[gid];
	vector v = dVel[gid];
	color  c = dCobj[gid];

	point  pp = p + v*DT + G*(point)( .5*DT*DT );
	vector vp = v + G*DT;
	pp.w = 1.;
	vp.w = 0.;

	if( IsInsideSphere( pp, Sphere1 ) )
	{
		vp = BounceSphere( p, v, Sphere1 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		float r = gid % 10;
		float g = gid % 100 / r;
		float b = gid % 1000 / r / g;
		if(r > g){
			c = (color)(r, 0., 0., 1.);
		}else if(g > b ){
			c = (color)(0., g, 0., 1.);
		}else{
			c = (color)(0., 0., b, 1.);
		}
	}
	if( IsInsideSphere( pp, Sphere2 ) )
	{
		vp = BounceSphere( p, v, Sphere2 );
		pp = p + vp*DT + G*(point)( .5*DT*DT );
		float r = gid % 10;
		float g = gid % 100 / r;
		float b = gid % 1000 / r / g;
		if(r > g){
			c = (color)(r, 0., 0., 1.);
		}else if(g > b ){
			c = (color)(0., g, 0., 1.);
		}else{
			c = (color)(0., 0., b, 1.);
		}
	}
	dPobj[gid] = pp;
	dVel[gid]  = vp;
	dCobj[gid] = c;
}
