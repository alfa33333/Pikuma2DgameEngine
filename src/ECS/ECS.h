#ifndef ECS_H
#define ECS_H

#include <bitset>
#include <vector>

const unsigned int MAX_COMPONENT = 32;

///////////////////////////////////////////////////
// Signature
///////////////////////////////////////////////////
// We use a bitset (1s and 0s) to keep track of which components and
// entity
///////////////////////////////////////////////////
typedef std::bitset<MAX_COMPONENT> Signature;


class Component {

};

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id){};
        int Getid() const;
};
///////////////////////////////////////////////////////
// System
//////////////////////////////////////////////////////
// The system processes entities that contain a specific signature
//////////////////////////////////////////////////////
class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;

    public:
        System() = default;
        ~System() = default;
        
        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystementities() const;
        Signature& GetComponentSignature() const;

        //Define the component type T
        // considered by the system
        template <typename T> void RequiredComponent();
};


class Registry {

};

#endif