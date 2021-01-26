#include "ECS.h"
#include <algorithm>

int Entity::Getid() const{
    return id;
}

void System::AddEntityToSystem(Entity entity){
    entities.push_back(entity);
}
void System::RemoveEntityFromSystem(Entity entity){
    // naive way
    // for(int i=1; i <= entities.size(); i++){
    //     if (entities[i].Getid() == entity.Getid())
    //         entities.erase (entities.begin()+i);
    // }
    entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other){
        return entity == other;
    }), entities.end());
}
std::vector<Entity> System::GetSystementities() const{
    return entities;
}
const Signature& System::GetComponentSignature() const{
    return componentSignature;
}

