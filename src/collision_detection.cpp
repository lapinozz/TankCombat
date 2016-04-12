#include "inc/collision_detection.hpp"

namespace Collision
{

//
//bool quickCircleTest(const Entity* entity1, const Entity* entity2)
//{
//    const float r = entity1->getMinimumRadius()+entity2->getMinimumRadius();
//    const sf::Vector2f diff = entity1->getWorldPosition() - entity2->getWorldPosition();
//    return (r*r) > (diff.x*diff.x) + (diff.y*diff.y);
//}

Manifold polygonVSpolygon(const CollisionEntity& polygon1, const CollisionEntity& polygon2)
{
    Manifold manifold;

    std::vector<sf::Vector2f> axes;

    for(const auto& axe : polygon1.getAxes())
            axes.push_back(math::normalize(math::perpandicular(axe[0] - axe[1])));

    for(const auto& axe : polygon2.getAxes())
            axes.push_back(math::normalize(math::perpandicular(axe[0] - axe[1])));

    int minimumDepth = std::numeric_limits<int>::max();
    sf::Vector2f minimumAxi;
    int dir = 1;

    for (const sf::Vector2f& axe : axes)
    {
        float min1, max1, min2, max2;

        polygon1.projectOntoAxis(axe, min1, max1);
        polygon2.projectOntoAxis(axe, min2, max2);

        //If they dosent overlap on this axi then they are not colliding, return
        if (!(min2 <= max1 && max2 >= min1))
            return manifold;
        else
        {
            float dist1 = std::abs(min1 - max2);
            float dist2 = std::abs(max1 - min2);

            if(dist1 < minimumDepth)
            {
                minimumDepth = dist1;
                minimumAxi = axe;
                dir = -1;

            }
            if(dist2 < minimumDepth)
            {
                minimumDepth = dist2;
                minimumAxi = axe;
                dir = 1;
            }
        }
    }

    manifold.collide = true;

    sf::Vector2f normal = minimumAxi * (float)dir;

    manifold.depth = minimumDepth;
    manifold.normal = normal;

    manifold.contactPoints[0] = polygon1.getSupportPoints(normal);
    manifold.contactPoints[1] = polygon2.getSupportPoints(-normal);

    return manifold;
}

//Manifold OBBvsCircle(CollisionEntity& object1, CollisionEntity& object2)
//{
//    Manifold manifold;
//    manifold.object1 = &object1;
//    manifold.object2 = &object2;
//
//    OrientedBoundingBox obb(object1);
//
//    sf::Vector2f circleCenter = object2.getWorldPosition();
//    float radius = object2.getSize().x/2.f;
//
//    std::vector<std::array<sf::Vector2f, 2>> axes;
//
//    if(!manifold.collide)
//    {
//        for(int x = 0; x < 4; x++)
//        {
//            sf::Vector2f point = closestPointOnSegment(obb.axes[x][0], obb.axes[x][1], circleCenter);
//            float depth = distance(circleCenter, point) - radius;
//            if(depth < 0 && std::fabs(depth) > std::fabs(manifold.depth))
//            {
//                manifold.collide = 1;
//                manifold.depth = 0.f;//-depth;
//                manifold.nbContactPoints[0] = 1;
//                manifold.nbContactPoints[1] = 1;
//                manifold.contactPoints[0][0] = point;
//                manifold.contactPoints[1][0] = point;
//                manifold.contactPoints[0][1] = point;
//                manifold.contactPoints[1][1] = point;
//                manifold.normal = -normalize(point - circleCenter);
//            }
//        }
//    }
//
//    return manifold;
//}

//Manifold CirclevsCircle(CollisionEntity& object1, CollisionEntity& object2)
//{
//    Manifold manifold;
//    manifold.object1 = &object1;
//    manifold.object2 = &object2;
//
//    OrientedBoundingBox obb(object1);
//
//    sf::Vector2f circleCenter[2] = {object1.getWorldPosition(), object2.getWorldPosition()};
//    float radius[2] = {object1.getSize().x/2.f, object2.getSize().x/2.f};
//
//    float depth = distance(circleCenter[0], circleCenter[1]) - (radius[0] + radius[1]);
//    if(depth < 0)
//    {
//        manifold.collide = 1;
//        manifold.depth = -depth;
//        manifold.normal = -normalize(circleCenter[0] - circleCenter[1]);
//
//        sf::Vector2f point = circleCenter[1] - (manifold.normal*((radius[0] + radius[1])/2.f));
//
//        manifold.nbContactPoints[0] = 1;
//        manifold.nbContactPoints[1] = 1;
//        manifold.contactPoints[0][0] = point;
//        manifold.contactPoints[1][0] = point;
//        manifold.contactPoints[0][1] = point;
//        manifold.contactPoints[1][1] = point;
//    }
//
//    return manifold;
//}

//void collisionResponse(Manifold manifold)
//{
//    sf::Vector2f contactPoint;
//
//    if(manifold.nbContactPoints[0] == 2)
//        contactPoint = manifold.contactPoints[1][0];
//    else if(manifold.nbContactPoints[1] == 2)
//        contactPoint = manifold.contactPoints[0][0];
//
//    CollisionEntity info1, info2;
//
//    manifold.object1->getShip()->computeEntity(info1);
//    manifold.object2->getShip()->computeEntity(info2);
//
//    Entity* Object1 = info1.applyTo;
//    Entity* Object2 = info2.applyTo;
//
//    info1.centerOfMass += Object1->getWorldPosition();
//    info2.centerOfMass += Object2->getWorldPosition();
//
//    if(Object1 == Object2)
//        return;
//
//    sf::Vector2f rv = (Object1->getWorldVelocity() - Object2->getWorldVelocity());
//    sf::Vector2f arv = sf::Vector2f(0, 0);
//
//    for(int x = 0; x < 2; x++)
//    {
//        Entity* Object = x == 0 ? Object1 : Object2;
//
//        float radius = distance(Object->getWorldPosition(), contactPoint);
//        float radians = ::radians(Object->getWorldRotationVelocity());
//        sf::Vector2f normal = sf::Vector2f((contactPoint-Object->getWorldPosition()).y, -((contactPoint-Object->getWorldPosition()).x));
//
//        normal = normalize(normal);
//
//        arv += (x == 0 ? normal * (radius * radians) : -(normal * (radius * radians)) );
//    }
//
//    rv -= arv;
//
//    float contactReal = dot(rv, manifold.normal);
//
//    float j = -(1.f + 0.5f) * contactReal;
//
//    //Object1->move(-manifold.normal*((manifold.depth+0.5f)/2.f));
//    //Object2->move(manifold.normal*((manifold.depth+0.5f)/2.f));
//
//    float InvMassA = 1 / info1.mass;
//    float InvMassB = 1 / info2.mass;
//
////    std::cout << "Mass: " << InvMassA << " : " << InvMassB << std::endl;
//
//    Object1->move(-manifold.normal*((manifold.depth+0.5f) /*Diviser part 2 pour une animation */) * (InvMassA) / (InvMassA + InvMassB) );
//    Object2->move(manifold.normal*((manifold.depth+0.5f) /*Diviser part 2 pour une animation */) * (InvMassB) / (InvMassA + InvMassB) );
//
//    Object1->accelerate( (j * manifold.normal) * (InvMassA) / (InvMassA + InvMassB) );
//    Object2->accelerate( -(j * manifold.normal) * (InvMassB) / (InvMassA + InvMassB) );
//
//    j /= 2;
//    sf::Vector2f impulse = j * manifold.normal;
//
//    if(manifold.nbContactPoints[0] == 2)
//    {
//        Object1->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[1][0]-info1.centerOfMass, impulse)) * (InvMassA) / (InvMassA + InvMassB) );
//        Object2->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[1][0]-info2.centerOfMass, -impulse)) * (InvMassB) / (InvMassA + InvMassB) );
//    }
//    if(manifold.nbContactPoints[1] == 2)
//    {
//        Object1->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[0][0]-info1.centerOfMass, impulse)) * (InvMassA) / (InvMassA + InvMassB) );
//        Object2->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[0][0]-info2.centerOfMass, -impulse)) * (InvMassB) / (InvMassA + InvMassB) );
//    }
////    if(manifold.nbContactPoints[0] == 2 && manifold.nbContactPoints[1] == 2)
////    {
////        Object1->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[1][1]-info1.centerOfMass, impulse)) * (InvMassA) / (InvMassA + InvMassB) );
////        Object2->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[1][1]-info2.centerOfMass, -impulse)) * (InvMassB) / (InvMassA + InvMassB) );
////
////        Object1->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[0][1]-info1.centerOfMass, impulse)) * (InvMassA) / (InvMassA + InvMassB) );
////        Object2->accelerateRotation(0.01*(crossProduct(manifold.contactPoints[0][1]-info2.centerOfMass, -impulse)) * (InvMassB) / (InvMassA + InvMassB) );
////    }
//}
//}
}
