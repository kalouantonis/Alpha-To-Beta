#include <Systems/CameraFollowingSystem.h>

#include <Graphics/Camera2D.h>

CameraFollowingSystem::CameraFollowingSystem(Camera2D &camera)
    : m_camera(camera)
{
    addComponentType<Transform>();
    addComponentType<CameraFollower>();
}

void CameraFollowingSystem::processEntity(artemis::Entity &e)
{
    Transform* pTransform = m_transformMapper.get(e);

    m_camera.setCenter(pTransform->position);
}

void CameraFollowingSystem::initialize()
{
    m_transformMapper.init(*world);
}

