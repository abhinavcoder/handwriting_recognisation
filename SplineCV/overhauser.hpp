#ifndef overhauserHPP
#define overhauserHPP

#include "vec3.hpp"
#include <vector>

class CRSpline
{
public:

    // Constructors and destructor
    CRSpline();
    CRSpline(const CRSpline&);
    ~CRSpline();

    // Operations
    void AddSplinePoint(const vec3& v);
	vec3 GetInterpolatedSplinePoint(float t);   // t = 0...1; 0=vp[0] ... 1=vp[max]
	int GetNumPoints();
	vec3& GetNthPoint(int n);

    // Static method for computing the Catmull-Rom parametric equation
    // given a time (t) and a vector quadruple (p1,p2,p3,p4).
    static vec3 Eq(float t, const vec3& p1, const vec3& p2, const vec3& p3, const vec3& p4);

private:
    std::vector<vec3> vp;
    float delta_t;
};

#endif
