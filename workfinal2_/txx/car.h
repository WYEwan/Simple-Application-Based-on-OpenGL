#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader.h"
#include "model.h"
#include"filesystem.h"
#include "camera.h"
#define STB_IMAGE_IMPLEMENTATION


const float OBJSPEED = 8.0f;
class GameObject {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    float Yaw;
    GameObject(glm::vec3 pos) : position(pos), front(glm::vec3(1.0f, 0.0f, 0.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)),Yaw(0.0f) {
        right = glm::cross(front, up); 
        updateVectors();
    }

    void processInput(Camera_Movement direction,GLfloat deltaTime) {
        float velocity = OBJSPEED * deltaTime;

        if (direction == BACKWARD)
            position -= right * velocity;
        if (direction == FORWARD)
            position += right * velocity;
       
    }
    void processturn(Camera_Movement direction, GLfloat deltaTime) {
        float velocity = OBJSPEED * deltaTime;
        
        if (direction == RIGHT)

            Yaw -= 1.0f;
            
        if (direction == LEFT)

            Yaw += 1.0f;  
        updateVectors();
    }
    glm::vec3 Getobjposition()
    {
        return position;
    }
    float Getobjrotation()
    {

        return Yaw;
    }
    glm::vec3 Getobjfront()
    {

        return front;
    }
    void updateVectors() {
        glm::vec3 front2;
        front2.x = sin(glm::radians(Yaw));
        front2.y = front.y;
        front2.z = cos(glm::radians(Yaw));
        front = glm::normalize(front2);
        right = glm::cross(front, up); 
    }

    void rotate(GLfloat angle, glm::vec3 axis) {
        glm::quat rotation = glm::angleAxis(glm::radians(angle), axis);
        front = rotation * front; 
        updateVectors(); 
    }
};