#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
using namespace glm;

#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"
#include "graphics/VoxelRenderer.h"
#include "window/Window.h"
#include "window/Events.h"
#include "window/Camera.h"
#include "loaders/png_loading.h"
#include "voxels/voxel.h"
#include "voxels/Chunk.h"

int WIDTH = 1920;
int HEIGHT = 1080;

float vertices[]  {
    // x     y     z     u     v
   -1.0f,-1.0f, 0.0f, 0.0f, 0.0f,
    1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

    1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
   -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
};

int attrs[] = {
    3,2, 0 // null terminator
};

int main() {
    Window::initialize(WIDTH, HEIGHT, "OpenGL Proj");
    Events::initialize();

    //std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    Shader* shader = load_shader("res/main.glslv", "res/main.glslf");
    if (shader == nullptr) {
        std::cerr << "failed to load shader" << std::endl;
        delete shader;
        Window::terminate();
        return 1;
    }

    Texture* texture = load_texture("res/block.png");
    if (texture == nullptr) {
        std::cerr << "failed to load texture" << std::endl;
        delete shader;
        Window::terminate();
        return 1 ;
    }
    
    VoxelRenderer renderer(1024*1024);
    Chunk* chunk = new Chunk();
    Mesh* mesh = renderer.render(chunk);
    glClearColor(83.0f/255, 69.0f/255, 136.0f/255, 1.0f);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Camera* camera = new Camera(vec3(10, 10, 10), radians(90.0f));

    mat4 model(1.0f);
    model = translate(model, vec3(0.5f, 0,0));
    //model = glm::scale(model, glm::vec3(0.5f,0.5f,0.5f));

    float lastTime = glfwGetTime();
    float deltaTime = 0.0f;

    float camX = 0.0f;
    float camY = 0.0f;
    
    while (!Window::isShouldClose()) {
        float currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;
        
        if (Events::jpressed(GLFW_KEY_ESCAPE)) {
            Window::setShouldClode(true);
        } 
        if (Events::jclicked(GLFW_MOUSE_BUTTON_1)) {
            glClearColor(135.0f/255, 206.0f/255, 235.0f/255, 1.0f);
        }
        if (Events::jpressed(GLFW_KEY_TAB)) {
            Events::toggleCursor();
        }

        float speed = 5.0f;
        if(Events::pressed(GLFW_KEY_W)) {
            camera->position += normalize(vec3(camera->front.x, 0.0f, camera->front.z)) * speed * deltaTime;
        }
        if(Events::pressed(GLFW_KEY_S)) {
            camera->position -= normalize(vec3(camera->front.x, 0.0f, camera->front.z)) * speed * deltaTime;
        }
        if(Events::pressed(GLFW_KEY_A)) {
            camera->position -= normalize(vec3(camera->right.x, 0.0f, camera->right.z)) * speed * deltaTime;
        }
        if(Events::pressed(GLFW_KEY_D)) {
            camera->position += normalize(vec3(camera->right.x, 0.0f, camera->right.z)) * speed * deltaTime;
        }
        if(Events::pressed(GLFW_KEY_SPACE)) {
            camera->position += normalize(vec3(0.0f, camera->up.y, 0.0f)) * speed * deltaTime;
        }
        if(Events::pressed(GLFW_KEY_LEFT_SHIFT)) {
            camera->position -= normalize(vec3(0.0f, camera->up.y, 0.0f)) * speed * deltaTime;
        }
        
        if (Events::_cursor_locked) {
            camY += -Events::deltaY / Window::height;
            camX += -Events::deltaX / Window::height;
        }
        
        if (camY < -radians(89.0f)) {
            camY = -radians(89.0f);
        }
        if (camY > radians(89.0f)) {
            camY = radians(89.0f);
        }

        camera->rotate(camY, camX, 0); 
        camera->rotation = mat4(1.0f);


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw VAO
        shader->use();
        shader->uniformMatrix("model", model);
        shader->uniformMatrix("projview", camera->getProjection() * camera->getView());
        texture->bind();
        mesh->draw(GL_TRIANGLES);

        Window::swapBuffers();
        Events::pullEvents();
    }

    delete shader;
    delete texture;
    delete mesh;
    delete chunk;

    Window::terminate();
    return 0;
}