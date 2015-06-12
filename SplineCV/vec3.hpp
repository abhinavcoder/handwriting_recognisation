#ifndef vec3HPP
#define vec3HPP

/// Minimal 3-dimensional vector abstraction
class vec3
{
public:

    // Constructors
    vec3() : x(0), y(0), z(0)
	{}
	
	vec3(float vx, float vy, float vz)
	{
		x = vx;
		y = vy;
		z = vz;
	}

	vec3(const vec3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}

	// Destructor
	~vec3() {}

	// A minimal set of vector operations
	vec3 operator * (float mult) const // result = this * arg
	{
		return vec3(x * mult, y * mult, z * mult);
	}

	vec3 operator + (const vec3& v) const // result = this + arg
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}

	vec3 operator - (const vec3& v) const // result = this - arg
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}

	float x, y, z;
};

#endif
