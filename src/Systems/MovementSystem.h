#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System {
    public:
        MovementSystem() {
            RequiredComponent<TransformComponent>();
            RequiredComponent<RigidBodyComponent>();
        }

        void Update(double deltaTime) {
            
             for (auto entity: GetSystemEntities()){
                 // Update entity based on its velocity.
                 
                 auto& transform = entity.GetComponent<TransformComponent>();
                 const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

                 transform.position.x += rigidbody.velocity.x * deltaTime;
                 transform.position.y += rigidbody.velocity.y * deltaTime;

                //  Logger::Log(
                //     "Entity id = " + 
                //     std::to_string(entity.Getid()) + 
                //     " position is now (" + 
                //     std::to_string(transform.position.x) + 
                //     "," + 
                //     std::to_string(transform.position.y) + 
                //     ")");

             }
            
        }
};

#endif