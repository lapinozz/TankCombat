#ifndef COLLISION_H
#define COLLISION_H

#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

#include "inc/math_utility.hpp"

namespace Collision
{

typedef std::array<sf::Vector2f, 2> Axe;

struct Manifold
{
    bool collide = false;
    float depth = 0.f;
    sf::Vector2f normal = sf::Vector2f(0, 0);

    // Collision point relative to each entity
    // Eg: contactPoints[1][0] is the first collision point relative to the second entity
    std::array<std::vector<sf::Vector2f>, 2> contactPoints;
};

class CollisionEntity
{

public:

    CollisionEntity(const sf::Shape& shape)
    {
        for(size_t x = 0; x < shape.getPointCount(); x++)
            points.push_back(shape.getTransform() * shape.getPoint(x));

        recomputeAxes();
    }

    // Circle collision entity shall have, in order
    // One point at the center
    // One point on there perimeter
    CollisionEntity(const sf::CircleShape& shape)
    {
        points.push_back(shape.getPosition());
        points.push_back(shape.getPosition() + sf::Vector2f(shape.getRadius(), 0.f));
    }

    CollisionEntity(const sf::FloatRect& rect)
    {
        points.emplace_back(rect.left, rect.top);
        points.emplace_back(rect.left + rect.width, rect.top);
        points.emplace_back(rect.left + rect.width, rect.top + rect.height);
        points.emplace_back(rect.left, rect.top + rect.height);

        recomputeAxes();
    }

    CollisionEntity(const sf::FloatRect& rect, const sf::Transform& trans)
    {
        points.push_back(trans.transformPoint(-rect.width/2.f, -rect.height/2.f));
        points.push_back(trans.transformPoint(rect.width/2.f, -rect.height/2.f));
        points.push_back(trans.transformPoint(rect.width/2.f, rect.height/2.f));
        points.push_back(trans.transformPoint(-rect.width/2.f, rect.height/2.f));

        recomputeAxes();
    }

    CollisionEntity(const sf::Vector2f& p1, const sf::Vector2f& p2)
    {
        points.push_back(p1);
        points.push_back(p2);

        recomputeAxes();
    }

    const std::vector<Axe>& getAxes() const
    {
        return this->axes;
    }

    // Project each point on axis and store the min and max
    // of the shape on the axi in the parameter passed
    void projectOntoAxis(const sf::Vector2f& axis, float& min, float& max) const
    {
        min = math::dot(points[0], axis);
        max = min;
        for(const sf::Vector2f& point : points)
        {
            float projection = math::dot(point, axis);

            if(projection < min)
                min = projection;

            if(projection > max)
                max = projection;
        }
    }

    // Find the most advanced points on a given axis
    // Return multiple one if they are at the same level
    std::vector<sf::Vector2f> getSupportPoints(sf::Vector2f dir) const
    {
        float bestProjection = std::numeric_limits<int>::min();

        sf::Vector2f bestVertex;

        std::vector<sf::Vector2f> suportPoints;

        for(const sf::Vector2f& point : points)
        {
            float projection = math::dot(point, dir);

            if(projection > bestProjection)
            {
                suportPoints.clear();
                suportPoints.push_back(point);

                bestProjection = projection;
            }
            else if(math::roundNearZero(projection - bestProjection) == 0.f)//projection == bestProjection
            {
                suportPoints.push_back(point);
            }
        }

        return suportPoints;
    }

private:

    //Fill the axes vector from the points
    void recomputeAxes()
    {
        size_t start = 0;
        size_t end = 1;
        for(size_t x = 0; x < points.size(); x++)
        {
            axes.emplace_back(Axe{points[start], points[end]});
            start++;
            end++;
            //if we are at the end we need to wrap to get the last axe
            end = end == points.size() ? 0 : end;
        }

        // Warning: This create duplicated axi for quad and line
        // I did some test and it was faster to do the collision test
        // with the duplicated axes than filtering them
    }

    std::vector<sf::Vector2f> points;
    std::vector<Axe> axes;
};


Manifold polygonVSpolygon(const CollisionEntity& object1, const CollisionEntity& object2);
Manifold PolygonvsCircle(CollisionEntity& object1, CollisionEntity& object2);
Manifold CirclevsCircle(CollisionEntity& object1, CollisionEntity& object2);

}

#endif  /* COLLISION_H */
