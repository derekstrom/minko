/*
Copyright (c) 2013 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/math/Box.hpp"

#include "minko/math/Ray.hpp"
#include "minko/math/Vector3.hpp"

using namespace minko;
using namespace minko::math;

Box::Box() :
	_topRight(Vector3::create()),
	_bottomLeft(Vector3::create())
{

}

bool
Box::cast(Ray::Ptr ray, float& distance)
{
	Vector3::Ptr near, far;

	if (_topRight->z() > _bottomLeft->z())
	{
		near = _bottomLeft;
		far = _topRight;
	}
	else
	{
		near = _topRight;
		far = _bottomLeft;
	}

	auto t0x = (near->x() - ray->origin()->x()) / ray->direction()->x();
	auto t1x = (far->x() - ray->origin()->x()) / ray->direction()->x();

	if (t0x > t1x)
		std::swap(t0x, t1x);

	auto tmin = t0x;
	auto tmax = t1x;

	auto t0y = (near->y() - ray->origin()->y()) / ray->direction()->y();
	auto t1y = (far->y() - ray->origin()->y()) / ray->direction()->y();

	if (t0y > t1y)
		std::swap(t0y, t1y);

	if (t0y > tmax || tmin > t1y)
		return false;

	if (t0y > tmin)
		tmin = t0y;
	if (t1y < tmax)
		tmax = t1y;

	auto t0z = (near->z() - ray->origin()->z()) / ray->direction()->z();
	auto t1z = (far->z() - ray->origin()->z()) / ray->direction()->z();

	if (t0z > t1z)
		std::swap(t0z, t1z);
	
	if (t0z > tmax || tmin > t1z)
		return false;

	if (t0z > tmin)
		tmin = t0z;
	if (t1z < tmax)
		tmax = t1z;

	distance = tmin;

	return true;
}
