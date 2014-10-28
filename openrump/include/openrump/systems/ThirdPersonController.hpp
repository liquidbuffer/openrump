// ----------------------------------------------------------------------------
// ThirdPersonController.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include "ontology/System.hpp"

#include "OgreMath.h"
#include "OgreVector2.h"

#include <fstream>

namespace OpenRump {
    
class ThirdPersonController :
    public Ontology::System
{
public:
    
    /*!
     * @brief Default constructor
     */
    ThirdPersonController();
    
    /*!
     * @brief Construct and load a configuration file.
     */
    ThirdPersonController(std::string fileName);
    
    /*!
     * @brief Loads a third person controller configuration from disk.
     */
    void loadFromXML(std::string fileName);
    void loadFromXML(std::istream& stream);
    
    void onDirectionChange(float x, float y);
    
private:
    
    // implement ontology methods
    void initialise() override;
    void processEntity(Ontology::Entity&) override;
    void configureEntity(Ontology::Entity&, std::string="") override;
    
    Ogre::Vector2 m_TargetDirection;

    Ogre::Real m_TargetSpeed;
    Ogre::Real m_MaxSpeed;
    Ogre::Real m_AccelerationFactor;

    Ogre::Real m_TurnAccelerationFactor;
    Ogre::Real m_RollAngleIntensityFactor;
    Ogre::Real m_RollAngleAccelerationFactor;
    Ogre::Real m_PitchAngleIntensityFactor;
    Ogre::Real m_PitchAngleAccelerationFactor;
    Ogre::Radian m_RollAngle;
    Ogre::Radian m_MaxRollAngle;
    Ogre::Radian m_PitchAngle;
    Ogre::Radian m_MaxPitchAngle;
};

} // namespace OpenRump