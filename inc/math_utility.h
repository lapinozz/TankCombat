#pragma once

// Define useful math function, principaly for vector

namespace math
{
	#ifndef M_PI

	/* Expose these macro definitions for common math constants if M_PI is
	 * not already defined. These are placed under an #ifdef
	 * since these commonly-defined names are not part of the C/C++ standards.
	 */

	 /* Definitions of useful mathematical constants
	  * M_E        - e
	  * M_LOG2E    - log2(e)
	  * M_LOG10E   - log10(e)
	  * M_LN2      - ln(2)
	  * M_LN10     - ln(10)
	  * M_PI       - pi
	  * M_PI_2     - pi/2
	  * M_PI_4     - pi/4
	  * M_1_PI     - 1/pi
	  * M_2_PI     - 2/pi
	  * M_2_SQRTPI - 2/sqrt(pi)
	  * M_SQRT2    - sqrt(2)
	  * M_SQRT1_2  - 1/sqrt(2)
	  */

	#define M_E        2.71828182845904523536
	#define M_LOG2E    1.44269504088896340736
	#define M_LOG10E   0.434294481903251827651
	#define M_LN2      0.693147180559945309417
	#define M_LN10     2.30258509299404568402
	#define M_PI       3.14159265358979323846
	#define M_PI_2     1.57079632679489661923
	#define M_PI_4     0.785398163397448309616
	#define M_1_PI     0.318309886183790671538
	#define M_2_PI     0.636619772367581343076
	#define M_2_SQRTPI 1.12837916709551257390
	#define M_SQRT2    1.41421356237309504880
	#define M_SQRT1_2  0.707106781186547524401

	#endif /* M_PI */

	template<class T> T getDistance(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
	{
		return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
	}

	template<class T> T toRad(const T& deg)
	{
		return deg * M_PI / 180;
	}

	template<class T> T toDeg(const T& rad)
	{
		return rad * 180 / M_PI;
	}

	template<class T> T lenght(const sf::Vector2<T>& vector)
	{
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	template<class T> T normalize(const T& vector)
	{
		float length = lenght(vector);

		//If lenght equal 0 return a 0,0 vector else return the vector
		//devised by its lenght
		return lenght == 0  ? {} : vector / lenght;
	}

	template<class T> sf::Vector2<T> angleToVector(const T& val)
	{
		return normalize(sf::Vector2<T>(sin(toRad(val)), -cos(toRad(val))));
	}

	template<class T> T vectorToAngle(const sf::Vector2<T>& val)
	{
		float angle = toDeg(atan2(val.x, -val.y));
		//    if(angle < 0.f)
		//        angle = 360.f + angle;
		return angle;
	}

	template<class T> T dot(const sf::Vector2<T>& vector1, const sf::Vector2<T>& vector2)
	{
		return vector1.x*vector2.x + vector1.y*vector2.y;
	}

	template<class T> T perpDot(const sf::Vector2<T>& vector1, const sf::Vector2<T>& vector2)
    {
		return (vector1.y*vector2.x) - (vector1.x*vector2.y);
	}

	template<class T> sf::Vector2<T> crossProduct(const T& val, const sf::Vector2<T>& vector)
	{
		return sf::Vector2<T>(-val * vector.y, val * vector.x);
	}

	template<typename T> T lerp(const T& value1, const T& value2, float interpolation)
	{
		return (value1 * (1.0f - interpolation)) + (value2 * interpolation);
	}

	template<typename T> sf::Vector2<T> perpandicular(const sf::Vector2<T>& vector)
	{
		return sf::Vector2<T>(-vector.y, vector.x);
	}

	const float tolerance = 0.0000001f;//1e-15;

	template<typename T> T roundNearZero(const T& val)
	{
		return std::fabs(val) < tolerance ? 0 : val;
	}

	template<typename T> sf::Vector2<T> roundNearZero(const sf::Vector2<T>& vector)
	{
		return {roundNearZero(vector.x), roundNearZero(vector.y)};
	}

};
