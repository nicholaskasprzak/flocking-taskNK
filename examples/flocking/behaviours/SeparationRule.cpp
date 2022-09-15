#include "SeparationRule.h"
#include "../gameobjects/Boid.h"
#include "../gameobjects/World.h"

Vector2 SeparationRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
    //Try to avoid boids too close
    Vector2 separatingForce = Vector2::zero();

    float desiredDistance = desiredMinimalDistance;

    // todo: implement a force that if neighbor(s) enter the radius, moves the boid away from it/them
    if (!neighborhood.empty()) {
        Vector2 position = boid->transform.position;
        int countCloseFlockmates = 0;

        for (int i = 0; i < neighborhood.size(); i++)
        {
            if (Vector2::getMagnitude(neighborhood[i]->getPosition() - position) < desiredDistance)
            {
                separatingForce += boid->getPosition() - neighborhood[i]->getPosition();
                countCloseFlockmates++;
            }
        }
        
        if (countCloseFlockmates > 0)
        {
            separatingForce.x = 1 / separatingForce.x;
            separatingForce.y = 1 / separatingForce.y;
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
