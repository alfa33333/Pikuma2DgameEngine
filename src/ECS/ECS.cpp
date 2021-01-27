#include "ECS.h"
#include "../Logger/Logger.h"
#include <algorithm>

int IComponent::nextId = 0;

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

Entity Registry::CreateEntity(){
    int entityId;

    entityId = numEntities++;

    Entity entity(entityId);
    entitiesToBeAdded.insert(entity);

    // Make sure the entityCompoenent Signatures vector can accomodate the new entity
    if (entityId >= entityComponentSignatures.size()){
        entityComponentSignatures.resize(entityId+1);
    }

    Logger::Log("Entity created with id= " + std::to_string(entityId));
    return entity;
}

void Registry::AddEntityToSystems(Entity entity){
    const auto entityId = entity.Getid();

    //TODO: Match entities
    const auto& entityComponentSignature =  entityComponentSignatures[entityId];
    
    //Loop all the systems
    for (auto& system: systems){
        const auto& systemComponentSignature = system.second->GetComponentSignature();
        
        bool isInterested = (entityComponentSignature & systemComponentSignature) == systemComponentSignature;
        
        if (isInterested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}

void Registry::Update(){
    //TODO Add the entities that are waiting to be created to the active systems
    for (auto entity: entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();
    //TODO Remove the entities
}
