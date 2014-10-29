// ----------------------------------------------------------------------------
// DefaultPhysicsWorld.hpp
// ----------------------------------------------------------------------------

#ifndef _OPENRUMP_DEFAULT_PHYSICS_WORLD_HPP_
#define _OPENRUMP_DEFAULT_PHYSICS_WORLD_HPP_

// ----------------------------------------------------------------------------
// include files

#include "ontology/System.hpp"

#include <btBulletDynamicsCommon.h>

#include <memory>

namespace OpenRump {

class DefaultPhysicsWorld : public Ontology::System
{
public:
private:
    
    // override ontology methods
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    void configureEntity(Ontology::Entity&, std::string="") override;
    
    std::unique_ptr<btBroadphaseInterface>                  m_Broadphase;
    std::unique_ptr<btDefaultCollisionConfiguration>        m_CollisionConfiguration;
    std::unique_ptr<btCollisionDispatcher>                  m_Dispatcher;
    std::unique_ptr<btSequentialImpulseConstraintSolver>    m_Solver;
    std::unique_ptr<btDiscreteDynamicsWorld>                m_World;
};

} // namespace OpenRump

#endif // _OPENRUMP_DEFAULT_PHYSICS_WORLD_HPP_