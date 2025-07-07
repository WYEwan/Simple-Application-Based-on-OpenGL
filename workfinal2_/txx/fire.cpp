#define STB_IMAGE_IMPLEMENTATION
#define _CRT_SECURE_NO_WARNINGS

#include "camera.h"
#include "car.h"
#include "shader.h"
#include "model.h"
#include "filesystem.h"
#include "mesh.h"
#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <gl/GL.h>
#include <thread>
#include <chrono>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void processInput1(GLFWwindow *window);
void carmove(GLFWwindow* window, bool turn);
unsigned int loadCubemap(vector<std::string> faces);
unsigned int loadTexture(const char* path);
bool test_obstacle(GameObject k);

const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 1200;

float w0 = static_cast<float>(glfwGetTime());
float w1 = -2000;
float w2 = 0;
int tem = 1;
int k0 = -1;

glm::vec3 cityposition(35.0f, -6.05f, 0.0f);
glm::vec4 carrealposition(0.0f, -6.05f, 0.0f, 1.0f);
glm::vec4 busrealposition(0.0f, -6.05f, 0.0f, 1.0f);
glm::vec3 busposition(0.0f, -6.05f, 0.0f);
glm::vec3 cloudPosition(0.0f,150.5f, -0.0f);
glm::vec3 carPosition(0.0f, -6.05f, 0.0f);
glm::vec3 seaPosition(2.0f, -50.05f, 4.0f);

float busrotation;
bool turn = false;

Camera camera(glm::vec3(0.0f, 8.0f, 0.0f));
GameObject buspos(glm::vec3(0.0f, 0.0f, 0.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool stop = false;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(25.0f, 50.0f, 25.0f);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Final Work", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;

        return -1;
    }


    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    Shader ourShader("shader.vs", "shader.fs");
    Shader skyboxShader("skybox.vs", "skybox.fs");
    Shader shader("cubemaps.vs", "cubemaps.fs");
    Shader lightingShader("light_casters.vs", "light_casters.fs");
    Shader lightCubeShader("light_cube.vs", "light_cube.fs");
    Shader simpleDepthShader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs");
    Shader geometry_shader("geometry_shader.vs", "geometry_shader.fs", "geometry_shader.gs");


    float scale = 90000.0f;
    float skyboxVertices[] = {
 -1.0f * scale,  1.0f * scale, -1.0f * scale,
 -1.0f * scale, -1.0f * scale, -1.0f * scale,
 1.0f * scale, -1.0f * scale, -1.0f * scale,
 1.0f * scale, -1.0f * scale, -1.0f * scale,
 1.0f * scale,  1.0f * scale, -1.0f * scale,
-1.0f * scale,  1.0f * scale, -1.0f * scale,

-1.0f * scale, -1.0f * scale,  1.0f * scale,
-1.0f * scale, -1.0f * scale, -1.0f * scale,
-1.0f * scale,  1.0f * scale, -1.0f * scale,
-1.0f * scale,  1.0f * scale, -1.0f * scale,
-1.0f * scale,  1.0f * scale,  1.0f * scale,
-1.0f * scale, -1.0f * scale,  1.0f * scale,

 1.0f * scale, -1.0f * scale, -1.0f * scale,
 1.0f * scale, -1.0f * scale,  1.0f * scale,
 1.0f * scale,  1.0f * scale,  1.0f * scale,
 1.0f * scale,  1.0f * scale,  1.0f * scale,
 1.0f * scale,  1.0f * scale, -1.0f * scale,
 1.0f * scale, -1.0f * scale, -1.0f * scale,

-1.0f * scale, -1.0f * scale,  1.0f * scale,
-1.0f * scale,  1.0f * scale,  1.0f * scale,
 1.0f * scale,  1.0f * scale,  1.0f * scale,
 1.0f * scale,  1.0f * scale,  1.0f * scale,
 1.0f * scale, -1.0f * scale,  1.0f * scale,
-1.0f * scale, -1.0f * scale,  1.0f * scale,

-1.0f * scale,  1.0f * scale, -1.0f * scale,
 1.0f * scale,  1.0f * scale, -1.0f * scale,
 1.0f * scale,  1.0f * scale,  1.0f * scale,
 1.0f * scale,  1.0f * scale,  1.0f * scale,
-1.0f * scale,  1.0f * scale,  1.0f * scale,
-1.0f * scale,  1.0f * scale, -1.0f * scale,

-1.0f * scale, -1.0f * scale, -1.0f * scale,
-1.0f * scale, -1.0f * scale,  1.0f * scale,
 1.0f * scale, -1.0f * scale, -1.0f * scale,
 1.0f * scale, -1.0f * scale, -1.0f * scale,
-1.0f * scale, -1.0f * scale,  1.0f * scale,
 1.0f * scale, -1.0f * scale,  1.0f * scale
            
        };



    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    unsigned int skyboxVAO, skyboxVBO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    vector<std::string> faces
    {
        FileSystem::getPath("objects/skybox/top.jpg"), //前
        FileSystem::getPath("objects/skybox/top.jpg"), //后
        FileSystem::getPath("objects/skybox/top.jpg"), //上
        FileSystem::getPath("objects/skybox/top.jpg"), //下
        FileSystem::getPath("objects/skybox/top.jpg"), //左
        FileSystem::getPath("objects/skybox/top.jpg")  //右
    };

    unsigned int cubemapTexture = loadCubemap(faces);
    skyboxShader.use();
    skyboxShader.setInt("skybox", 0);

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Model car(FileSystem::getPath("objects/car/car.obj"));
    Model bus(FileSystem::getPath("objects/bus/bus.obj"));
    Model city(FileSystem::getPath("objects/city/city.obj"));
    Model cloud(FileSystem::getPath("objects/cloud/cloud.obj"));
    Model sea(FileSystem::getPath("objects/sea/sea.obj"));
    Model wheel(FileSystem::getPath("objects/wheel/wheel.obj"));

    ourShader.use();
    ourShader.setVec3("lightColor", 0.8f, 0.8f, 0.8f);
    ourShader.setVec3("lightPos", lightPos);
    ourShader.setVec3("viewPos", 0.0f, 0.0f, 8.0f);

    glm::vec3 seaScaleVector(60.0f);
    glm::vec3 cloudScaleVector(9.0f);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        if (test_obstacle(buspos) == FALSE) {
            goto label;
        }
        if (stop)
            processInput1(window);
        else
            processInput(window);
        carmove(window, turn);
        label:


        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 50.0f;
        lightProjection = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, near_plane, far_plane);
        lightView = glm::lookAt(lightPos, glm::vec3(2.0f, -6.05f, 0.0f), glm::vec3(0.0, 1.0, 0.0));
        lightSpaceMatrix = lightProjection * lightView;
        
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);

        simpleDepthShader.use();
        simpleDepthShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, seaPosition); 
        model = glm::scale(model, seaScaleVector);   
        simpleDepthShader.setMat4("model", model);
        sea.Draw(simpleDepthShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, cityposition);
        simpleDepthShader.setMat4("model", model);
        city.Draw(simpleDepthShader);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        simpleDepthShader.setMat4("projection", projection);
        glm::mat4 view = camera.GetViewMatrix(buspos.position, buspos.Yaw);
        simpleDepthShader.setMat4("view", view);
        simpleDepthShader.setMat4("projection", projection);
        model = glm::mat4(1.0f);


        if (!stop)
            busposition = buspos.Getobjposition();
        model = glm::translate(model, busposition);
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        if (!stop)
        {
            busrotation = buspos.Getobjrotation();
        }

        model = glm::rotate(model, glm::radians(busrotation), glm::vec3(0.0f, 1.0f, 0.0f));
        simpleDepthShader.setMat4("model", model);
        wheel.Draw(ourShader);
        bus.Draw(simpleDepthShader);
        simpleDepthShader.setMat4("model", model);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        ourShader.use();
        ourShader.setMat4("lightSpaceMatrix", lightSpaceMatrix);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        ourShader.setInt("shadowMap", 1);

        model = glm::mat4(1.0f);
        model = glm::translate(model, seaPosition); 
        model = glm::scale(model, seaScaleVector);   
        ourShader.setMat4("model", model);
        sea.Draw(ourShader);
        
        model = glm::mat4(1.0f); 
        model = glm::translate(model, cloudPosition);
        model = glm::scale(model, cloudScaleVector);
        ourShader.setMat4("model", model);
        cloud.Draw(ourShader); 

        model = glm::mat4(1.0f);
        model = glm::translate(model, cityposition);
        ourShader.setMat4("model", model);
        city.Draw(ourShader);

        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);
        view = camera.GetViewMatrix(buspos.position, buspos.Yaw);
        ourShader.setMat4("view", view);
        ourShader.setMat4("projection", projection);
        model = glm::mat4(1.0f);

        if (!stop)
            busposition = buspos.Getobjposition();
        model = glm::translate(model, busposition);
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        if (!stop)
        {
            busrotation = buspos.Getobjrotation();
        }

        model = glm::rotate(model, glm::radians(busrotation), glm::vec3(0.0f, 1.0f, 0.0f));
        ourShader.setMat4("model", model);
        busrealposition = model * busrealposition;

        if (test_obstacle(buspos) == FALSE) {
            if (tem == 1) {
                w2 = static_cast<float>(glfwGetTime());
            }
            else {
                k0 = w2+5.0;
            }
            geometry_shader.use();
            geometry_shader.setMat4("projection", projection);
            geometry_shader.setMat4("view", view);
            geometry_shader.setMat4("model", model);
            geometry_shader.setFloat("time", static_cast<float>(glfwGetTime())- w0);

            bus.Draw(geometry_shader);
            if (k0==-1) {
                k0 = w2 + 5;
            }
            else if (static_cast<float>(glfwGetTime()) >= k0) {
                return 0;
            }
            tem = 0;
        }
        else {
            bus.Draw(ourShader);
        }

        model = glm::mat4(1.0f);
        model = glm::translate(model, carPosition);
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        model = glm::scale(model, glm::vec3(0.03f, 0.03f, 0.03f));

        w1 = w1 + (static_cast<float>(glfwGetTime())- w0)/20;
        if (w1 >= 2000) {

            w0 = static_cast<float>(glfwGetTime());
            w1 = -2000;
        }
        model = glm::translate(model, glm::vec3 (-100.0f, 210.0f, w1));//

        float angle = glm::radians(68.0f); 
        model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        carrealposition = model * carrealposition;

        ourShader.setMat4("model", model);
        car.Draw(ourShader);
        car.Draw(simpleDepthShader);
        glDepthFunc(GL_LEQUAL);  

        skyboxShader.use();
        skyboxShader.setMat4("view", view);
        skyboxShader.setMat4("projection", projection);

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        glDepthFunc(GL_LESS); 
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.stopthecar(stop);
}
void processInput1(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard1(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard1(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard1(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard1(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.stopthecar(stop);
}
void carmove(GLFWwindow *window,bool turn)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        buspos.processInput(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        buspos.processInput(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && !turn)
    {
        buspos.processturn(LEFT, deltaTime);
        turn = true;
    }        
    else if(glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)\
        turn = false;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && !turn)
    {
        buspos.processturn(RIGHT, deltaTime);
        turn = true;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)\
        turn = false;
}



void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}



void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


unsigned int loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

bool test_obstacle(GameObject k) {
    float carx = k.position.x;
    float carz = k.position.z;
    if ((carz >= -69)&&(carz <= -42)) {
        if ((carx >= -7) && (carx <= 7)) {
            return TRUE;
        }
        else if ((carx >= 62.5) && (carx <= 76.5)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if ((carz >= -42) && (carz <= -28)) {
        if ((carx >= -34) && (carx <= 103)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if ((carz >= -28) && (carz <= 28)) {
        if ((carx >= -7) && (carx <= 7)) {
            return TRUE;
        }
        else if ((carx >= 62.5) && (carx <= 76.5)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if ((carz >= 28) && (carz <= 42)) {
        if ((carx >= -34) && (carx <= 103)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if ((carz >= 42) && (carz <= 69)) {
        if ((carx >= -7) && (carx <= 7)) {
            return TRUE;
        }
        else if ((carx >= 62.5) && (carx <= 76.5)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}