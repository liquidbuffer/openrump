// ----------------------------------------------------------------------------
// DefaultPhysicsWorld.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "openrump/systems/DefaultPhysicsWorld.hpp"

namespace OpenRump {

// ----------------------------------------------------------------------------
void DefaultPhysicsWorld::initialise()
{
    m_Broadphase.reset(
        new btDbvtBroadphase);
    m_CollisionConfiguration.reset(
        new btDefaultCollisionConfiguration);
    m_Dispatcher.reset(
        new btCollisionDispatcher(m_CollisionConfiguration.get()));
    m_Solver.reset(
        new btSequentialImpulseConstraintSolver);
    m_World.reset(
        new btDiscreteDynamicsWorld(m_Dispatcher.get(),
                                    m_Broadphase.get(),
                                    m_Solver.get(),
                                    m_CollisionConfiguration.get()));
    
    m_World->setGravity(btVector3(0, -9.81, 0));
}

// ----------------------------------------------------------------------------
void DefaultPhysicsWorld::processEntity(Ontology::Entity& e)
{
}

// ----------------------------------------------------------------------------
void DefaultPhysicsWorld::configureEntity(Ontology::Entity& e, std::string params)
{
}

}