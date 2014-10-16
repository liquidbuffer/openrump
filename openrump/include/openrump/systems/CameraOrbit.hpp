// ----------------------------------------------------------------------------
// CameraOrbit.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <ontology/System.hpp>

#include <boost/thread/recursive_mutex.hpp>

namespace OpenRump {

class CameraOrbit :
    public Ontology::System
{
public:

    /*!
     * @brief Default constructor
     */
    CameraOrbit();

    void onNewCameraAngle(float x, float y);
    void onNewCameraDistance(float distance);

private:

    void initialise() override;
    void processEntity(Ontology::Entity&) override;

    struct Angle_t
    {
        Angle_t() : x(0), y(0) {}
        float x, y;
    } m_Angle;
    float m_Distance;

    mutable boost::recursive_mutex m_Mutex;
};

} // namespace OpenRump
