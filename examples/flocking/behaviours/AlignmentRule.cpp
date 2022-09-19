#include "AlignmentRule.h"
#include "../gameobjects/Boid.h"

Vector2 AlignmentRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    Vector2 averageVelocity = Vector2::zero();

    if (!neighborhood.empty())
    {
        // Iterate through the neighborhood to get a sum of all nearby boid's velocities
        for (int i = 0; i < neighborhood.size(); i++)
        {
            averageVelocity += neighborhood[i]->velocity;
        }

        // Get the average velocity so the boid moves at 
        // a similar rate to the boids around it
        averageVelocity /= neighborhood.size();
    }

    return Vector2::normalized(averageVelocity);
}