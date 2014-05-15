#ifndef CAMERA_FOLLOWER_H_
#define CAMERA_FOLLOWER_H_

#include <Components/ParsedComponent.h>

class CameraFollower: public ParsedComponent
{
public:
    virtual bool load(const tinyxml2::XMLElement *pElement) final;

    static const char* g_name;
    virtual const char *getName() const final { return g_name; }
};

#endif // CAMERA_FOLLOWER_H_
