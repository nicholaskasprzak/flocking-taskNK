#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    if (!neighborhood.empty()) {
        Vector2 position = boid->getPosition();
        int countCloseFlockmates = 0;

        // Iterates through neighborhood
        for (int i = 0; i < neighborhood.size(); i++)
        {
            float distance = Vector2::getMagnitude(position - neighborhood[i]->getPosition());

            // Checks if neighbor boid is within the desired distance of the current boid
            if (distance < desiredDistance)
            {
                // Calculates the inverse of the the difference and distance between the two boids
                // to get the force needed to push the current boid away.
                // This is then added to separatingForce to manage the sum of all forces being
                // applied to the boid for this frame.
                Vector2 difference = position - neighborhood[i]->getPosition();
                separatingForce += difference / distance;

                countCloseFlockmates++;
            }
        }
        
        // If there were other boids in range, divides the separatingForce sum
        // to get the average force needed to push the boid away from its neighbors.
        if (countCloseFlockmates > 0)
        {
            separatingForce /= countCloseFlockmates;
        }
    }

    separatingForce = Vector2::normalized(separatingForce);

    return separatingForce;
}

bool SeparationRule::drawImguiRuleExtra() {
    ImGui::SetCurrentContext(world->engine->imGuiContext);
    bool valusHasChanged = false;

    if (ImGui::DragFloat("Desired Separation", &desiredMinimalDistance, 0.05f)) {
        valusHasChanged = true;
    }

    return valusHasChanged;
}
