#ifndef CAMERA_FOLLOWING_SYSTEM_H_
#define CAMERA_FOLLOWING_SYSTEM_H_

#include <Artemis/EntityProcessingSystem.h>
#include <Artemis/ComponentMapper.h>

#include <Components/Transform.h>
#include <Components/CameraFollower.h>

//fwd defs
class Camera2D;

class CameraFollowingSystem: public artemis::EntityProcessingSystem
{
public:
    CameraFollowingSystem(Camera2D& camera);

    virtual void processEntity(artemis::Entity& e) final;

private:
    virtual void initialize() final;
    artemis::ComponentMapper<Transform> m_transformMapper;

    Camera2D& m_camera;
};

#endif // CAMERA_FOLLOWING_SYSTEM_H_
