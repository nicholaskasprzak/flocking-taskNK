#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2 CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 cohesionForce;

    if (!neighborhood.empty())
    {
        Vector2 centerOfMass = Vector2::zero();

        // Iterate through the neighboorhood to get a sum of all nearby boid positions
        for (int i = 0; i < neighborhood.size(); i++)
        {
            centerOfMass += neighborhood[i]->getPosition();
        }

        // Divide by the neighborhood size to get the average position,
        // or center of mass, of the neighborhood
        centerOfMass /= neighborhood.size();

        // Create force towards centerOfMass
        cohesionForce = centerOfMass - boid->getPosition();
    }

    cohesionForce = Vector2::normalized(cohesionForce);

    return cohesionForce;
}