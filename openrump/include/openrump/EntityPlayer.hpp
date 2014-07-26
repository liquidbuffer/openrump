// ----------------------------------------------------------------------------
// EntityPlayer.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <openrump/EntityBase.hpp>
#include <openrump/InputListener.hpp>
#include <openrump/RendererFrameListener.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace OpenRump {
    class Input;
    class OgreRenderer;
}

namespace OpenRump {

class EntityPlayer :
    public EntityBase,
    public InputListener,
    public RendererFrameListener
{
private:

    /*!
     * @brief Constructor with renderer - only for delegating
     */
    EntityPlayer(OgreRenderer* sm);

public:

    /*!
     * @brief Constructs a player using the specified ogre scene manager.
     * @param input A pointer to the input controller, as the player entity
     * has internal methods that will react to user input, such as player
     * movement and camera movement.
     * @param renderer The renderer to use to load this entity.
     * @param instanceName A globally unique name for this instance.
     * @param meshName The name of the mesh to load for this instance.
     */
    // DEPRECATED
    EntityPlayer(Input* input,
                 OgreRenderer* renderer,
                 Ogre::String instanceName,
                 Ogre::String meshName);

    /*!
     * @brief Constructs a player from an XML file using the specified ogre sm.
     * @param input A pointer to the input controller, as the player entity
     * has internal methods that will react to user input, such as player
     * movement and camera movement.
     * @param renderer The renderer to use to load this entity.
     * @param fileName The file name of the XML file to load.
     */
    EntityPlayer(Input* input,
                 OgreRenderer* renderer,
                 Ogre::String fileName);

    /*!
     * @brief Default destructor
     */
    ~EntityPlayer();

private:

    /*!
     * @brief Loads the player from an XML file
     * @param stream The name of the XML file to load.
     * @return Returns the globally unique identifier string of the entity,
     * as specified in the XML file.
     */
    Ogre::String loadFromXML(std::istream& stream);

    // override input events
    virtual void onChangeDirectionAndVelocity(float x, float y);

    // override renderer events
    virtual bool onUpdateGameLoop(const float timeStep);

    Input* m_Input;
    OgreRenderer* m_Renderer;

    Ogre::Vector3 m_Direction;
    Ogre::Vector3 m_TargetDirection;

    Ogre::Real m_TargetSpeed;
    Ogre::Real m_Speed;
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
