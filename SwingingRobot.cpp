#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_m.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;	
float lastFrame = 0.0f;



struct Point {
    float x;
    float y;
};

void createVertices(float widthreal, float lengthreal, float heightreal, float vertices[]) {
    float w = widthreal / 2.0f;
    float l = lengthreal / 2.0f;
    float h = heightreal / 2.0f;

    int index = 0;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;

    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;

    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;

    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;

    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;

    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
}

void createHead1(float widthreal, float lengthreal, float heightreal, float vertices[]) {
    float w = widthreal / 2.0f;
    float l = lengthreal / 2.0f;
    float h = heightreal / 2.0f;

    int index = 0;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
}

void createHead2(float widthreal, float lengthreal, float heightreal, float vertices[]) {
    float w = widthreal / 2.0f;
    float l = lengthreal / 2.0f;
    float h = heightreal / 2.0f;

    int index = 0;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;

    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;

    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;

    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;

    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = -h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;

    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 1.0f; vertices[index++] = 1.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 1.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = l; vertices[index++] = 0.0f; vertices[index++] = 0.0f;
    vertices[index++] = -w; vertices[index++] = h; vertices[index++] = -l; vertices[index++] = 0.0f; vertices[index++] = 1.0f;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Homework", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("6.3.coordinate_systems.vs", "6.3.coordinate_systems.fs");

    float body[6*6*5];
    float widthreal = 5.0f, lengthreal = 5.0f, heightreal = 15.0f;
    widthreal = widthreal / 10;
    lengthreal = lengthreal / 10;
    heightreal = heightreal / 10;
    createVertices(widthreal, lengthreal, heightreal, body);

    float hands[6*6*5];
    widthreal = 2.5f, lengthreal = 10.0f, heightreal = 2.5f;
    widthreal = widthreal / 10;
    lengthreal = lengthreal / 10;
    heightreal = heightreal / 10;
    createVertices(widthreal, lengthreal, heightreal, hands);

    float feet[6 * 6 * 5];
    widthreal = 3.0f, lengthreal = 3.0f, heightreal = 12.0f;
    widthreal = widthreal / 10;
    lengthreal = lengthreal / 10;
    heightreal = heightreal / 10;
    createVertices(widthreal, lengthreal, heightreal, feet);

    float head1[1 * 6 * 5];
    widthreal = 2.5f, lengthreal = 2.5f, heightreal = 2.5f;
    widthreal = widthreal / 10;
    lengthreal = lengthreal / 10;
    heightreal = heightreal / 10;
    createHead1(widthreal, lengthreal, heightreal, head1);

    float head2[5 * 6 * 5];
    widthreal = 2.5f, lengthreal = 2.5f, heightreal = 2.5f;
    widthreal = widthreal / 10;
    lengthreal = lengthreal / 10;
    heightreal = heightreal / 10;
    createHead2(widthreal, lengthreal, heightreal, head2);

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
    };
    unsigned int VBOs[5], VAOs[5];
    glGenVertexArrays(5, VAOs);
    glGenBuffers(5, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(body), body, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hands), hands, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(head1), head1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(head2), head2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(feet), feet, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(false); 
    unsigned char *data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    ourShader.setMat4("projection", projection);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        ourShader.use();

        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        ourShader.setMat4("view", view);

        int record = 1;
        ourShader.setInt("myrecord", record);

        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        ourShader.setMat4("projection", projection); 


        float currentTime = glfwGetTime();
        glBindVertexArray(VAOs[0]);
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[0]);
            float angle = glm::radians(20.0f) * currentTime;
            model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glBindVertexArray(VAOs[1]);
        {
            float time = (float)glfwGetTime();
            float globalAngle = glm::radians(20.0f) * time;
            glm::mat4 model2 = glm::mat4(1.0f);

            model2 = glm::rotate(model2, globalAngle, glm::vec3(0.0f, 1.0f, 0.0f));

            model2 = glm::translate(model2, glm::vec3(-0.375f, 0.6f, 0.0f));

            model2 = glm::translate(model2, glm::vec3(0.0f, 0.2f, 0.3f)); 

            float legSwingAngle2 = glm::radians(15.0f) * sin((float)glfwGetTime() * 2.0f + glm::pi<float>()); // ÍÈ²¿°Ú¶¯½Ç¶È
            model2 = glm::rotate(model2, legSwingAngle2, glm::vec3(2.0f, 0.0f, 0.0f));

            model2 = glm::translate(model2, glm::vec3(0.0f, -0.3f, 0.0f)); 

            ourShader.setMat4("model", model2);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        {
            glm::mat4 model1 = glm::mat4(1.0f);
            float globalAngle = glm::radians(20.0f) * (float)glfwGetTime(); 
            model1 = glm::rotate(model1, globalAngle, glm::vec3(0.0f, 1.0f, 0.0f));

            model1 = glm::translate(model1, glm::vec3(0.375f, 0.6f, 0.0f));

            model1 = glm::translate(model1, glm::vec3(0.0f, 0.2f, 0.3f)); 

            float legSwingAngle1 = glm::radians(15.0f) * sin((float)glfwGetTime() * 2.0f); 
            model1 = glm::rotate(model1, legSwingAngle1, glm::vec3(2.0f, 0.0f, 0.0f));

            model1 = glm::translate(model1, glm::vec3(0.0f, -0.3f, 0.0f)); 

            ourShader.setMat4("model", model1);

            glDrawArrays(GL_TRIANGLES, 0, 36);

        }

        record = 0;
        ourShader.setInt("myrecord", record);

        glBindVertexArray(VAOs[2]);
        {
            glm::mat4 model = glm::mat4(1.0f);

            float angle = glm::radians(20.0f) * (float)glfwGetTime(); 
            model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));

            model = glm::translate(model, glm::vec3(0.0f, 0.875f, 0.0f));

            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        record = 1;
        ourShader.setInt("myrecord", record);

        glBindVertexArray(VAOs[3]);
        {
            glm::mat4 model = glm::mat4(1.0f);

            float angle = glm::radians(20.0f) * (float)glfwGetTime(); 
            model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));

            model = glm::translate(model, glm::vec3(0.0f, 0.875f, 0.0f));

            ourShader.setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 30);
        }

        

        glBindVertexArray(VAOs[4]);
        {

            glm::mat4 model1 = glm::mat4(1.0f);

            float globalAngle = glm::radians(20.0f) * (float)glfwGetTime(); 
            model1 = glm::rotate(model1, globalAngle, glm::vec3(0.0f, 1.0f, 0.0f));

            model1 = glm::translate(model1, glm::vec3(-0.4f, -0.8f, 0.0f));

            model1 = glm::translate(model1, glm::vec3(0.0f, 0.4f, 0.0f)); 

            float legSwingAngle1 = glm::radians(30.0f) * sin((float)glfwGetTime() * 2.0f); 
            model1 = glm::rotate(model1, legSwingAngle1, glm::vec3(1.0f, 0.0f, 0.0f));

            model1 = glm::translate(model1, glm::vec3(0.0f, -0.4f, 0.0f)); 

            ourShader.setMat4("model", model1);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        {
            float time = (float)glfwGetTime();
            float globalAngle = glm::radians(20.0f) * time;
            glm::mat4 model2 = glm::mat4(1.0f);

            model2 = glm::rotate(model2, globalAngle, glm::vec3(0.0f, 1.0f, 0.0f));

            model2 = glm::translate(model2, glm::vec3(0.4f, -0.8f, 0.0f));

            model2 = glm::translate(model2, glm::vec3(0.0f, 0.4f, 0.0f)); 

            float legSwingAngle2 = glm::radians(30.0f) * sin((float)glfwGetTime() * 2.0f + glm::pi<float>()); 
            model2 = glm::rotate(model2, legSwingAngle2, glm::vec3(1.0f, 0.0f, 0.0f));

            model2 = glm::translate(model2, glm::vec3(0.0f, -0.4f, 0.0f)); 

            ourShader.setMat4("model", model2);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    
    float cameraSpeed = static_cast<float>(2.5 * deltaTime);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
     
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}