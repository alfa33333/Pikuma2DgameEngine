#ifndef MOVEMENTSYSTEM_H
#define MOVEMENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem: public System {
    public:
        MovementSystem() {
            Logger::Log("ok1");
            RequiredComponent<TransformComponent>();
            RequiredComponent<RigidBodyComponent>();
        }

        void Update() {
            
             for (auto entity: GetSystemEntities()){
                 // Update entity based on its velocity.
                 
                 auto& transform = entity.GetComponent<TransformComponent>();
                 const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

                 transform.position.x += rigidbody.velocity.x;
                 transform.position.y += rigidbody.velocity.y;

                 Logger::Log(
                    "Entity id = " + 
                    std::to_string(entity.Getid()) + 
                    " position is now (" + 
                    std::to_string(transform.position.x) + 
                    "," + 
                    std::to_string(transform.position.y) + 
                    ")");

                //Logger::Log("ok");
             }
            
        }
};

#endif