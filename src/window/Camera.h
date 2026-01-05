#ifndef WINDOW_CAMERA_H
#define WINDOW_CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using namespace glm;

class Camera {
    void updateVectors();
public:
    vec3 front;
    vec3 up;
    vec3 right;
    mat4 rotation;

    float fov;
    vec3 position;
    Camera(vec3 position, float fov);

    void rotate(float x, float y, float z);

    mat4 getProjection();
    mat4 getView();
};

#endif /* WINDOW_CAMERA_H */