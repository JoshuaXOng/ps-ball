#pragma once
#include <vector>
#include <utility>

class Physicsable {
    
    virtual std::pair<float, float> getVelocityComponents() = 0;
    virtual std::pair<float, float> getAccelerationComponents() = 0;
    virtual std::vector<std::pair<std::pair<float, float>, std::pair<float, float>>> getForces() = 0;
    virtual float getMass() = 0;

    // virtual float getRotationalDisplacement() = 0;
    // virtual float getRotationalVelocity() = 0;
    // virtual float getRotationalAcceleration() = 0;
    
    //////////////////////////////////////////////////////////////////////////
    // RESOLUTION                                                           //
    //////////////////////////////////////////////////////////////////////////

    std::pair<float, float> calcDisplacementComponents() {
        
    }

    std::pair<float, float> calcVelocityComponents() {
        std::pair<float, float> previousVelocityComponents = this->getVelocityComponents();
        std::pair<float, float> accelerationComponents = this->calcAccelerationComponents();
        return { 
            previousVelocityComponents.first + accelerationComponents.first, 
            previousVelocityComponents.second + accelerationComponents.second
        };
    }

    std::pair<float, float> calcAccelerationComponents() {
        std::pair<float, float> netForceComponents = this->resolveNetForceComponents();
        return { netForceComponents.first / this->getMass(), netForceComponents.second / this->getMass() };
    }

    std::pair<float, float> resolveNetForceComponents() {
        float netXForce = 0;
        for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->getForces()) 
            netXForce += force.first.first;
        float netYForce = 0;
        for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->getForces()) 
            netYForce += force.first.second;
        return { netXForce, netYForce };
    };

    // float resolveRotationalDisplacement
    float calcRotationalDisplacement(SDL_Point centerOfRotation) {
        float netMoment = 0;
        for (std::pair<std::pair<float, float>, std::pair<float, float>> force : this->getForces()) {
            netMoment += -1 * (force.second.first - centerOfRotation.x) * force.first.second;
            netMoment += (force.second.second - centerOfRotation.y) * force.first.first;
        };
        return netMoment / 500;
    }

    //////////////////////////////////////////////////////////////////////////
    // END RESOLUTION                                                       //
    //////////////////////////////////////////////////////////////////////////

    // virtual void decayForces() = 0;

};