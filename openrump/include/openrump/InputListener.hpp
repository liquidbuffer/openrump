// ----------------------------------------------------------------------------
// InputListener.hpp
// ----------------------------------------------------------------------------

#ifndef __OPENRUMP_INPUT_LISTENER_HPP__
#define __OPENRUMP_INPUT_LISTENER_HPP__

namespace OpenRump {

class InputListener
{
public:

    /*!
     * @brief Allow destruction through base class pointer
     */
    virtual ~InputListener();

    /*!
     * @brief Exit program
     */
    virtual void onButtonExit() = 0;

    /*!
     * @brief The new directional vector and velocity.
     * @note The vector is normalised.
     */
    virtual void onChangeDirectionAndVelocity(float x, float y) = 0;

    /*!
     * @brief Whenever the camera should be moved, provides delta angles.
     * @note Angles are in degrees.
     */
    virtual void onChangeCameraAngleDelta(float deltaAngleX, float deltaAngleY) = 0;

    /*!
     * @brief Provides the new delta distance for the camera to change to.
     */
    virtual void onChangeCameraDistanceDelta(float deltaDistance) = 0;
};

} // namespace OpenRump

#endif // __OPENRUMP_INPUT_LISTENER_HPP__
