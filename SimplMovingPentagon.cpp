
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader_s.h>

#include <iostream>
#include <cmath>
#define M_E        2.71828182845904523536   
#define M_LOG2E    1.44269504088896340736   
#define M_LOG10E   0.434294481903251827651  
#define M_LN2      0.693147180559945309417  
#define M_LN10     2.30258509299404568402   
#define M_PI       3.14159265358979323846   
#define M_PI_2     1.57079632679489661923   
#define M_PI_4     0.785398163397448309616  
#define M_1_PI     0.318309886183790671538  
#define M_2_PI     0.636619772367581343076  
#define M_2_SQRTPI 1.12837916709551257390   
#define M_SQRT2    1.41421356237309504880   
#define M_SQRT1_2  0.707106781186547524401  

#include <cstdlib> 
#include <ctime>   

struct Point {
    double x;
    double y;
};

struct Point_float {
    float x;
    float y;
};

void update_move_level(Point starPoints[], double movepace) {
    
    for (int i = 0; i < 10; ++i) {
        starPoints[i].x += movepace;
    }
}


void update_move_vertical(Point starPoints[], double movepace) {
    
    for (int i = 0; i < 10; ++i) {
        starPoints[i].y += movepace;
    }
};

void update_rotate(Point starPoints[], double rotatepace) {
    
    double rotateRadians = rotatepace * M_PI / 180.0;

    
    Point center;
    center.x = (starPoints[0].x + starPoints[1].x + starPoints[2].x + starPoints[3].x + starPoints[4].x +
        starPoints[5].x + starPoints[6].x + starPoints[7].x + starPoints[8].x + starPoints[9].x) / 10.0;
    center.y = (starPoints[0].y + starPoints[1].y + starPoints[2].y + starPoints[3].y + starPoints[4].y +
        starPoints[5].y + starPoints[6].y + starPoints[7].y + starPoints[8].y + starPoints[9].y) / 10.0;

    
    for (int i = 0; i < 10; ++i) {
        double newX = (starPoints[i].x - center.x) * cos(rotateRadians) - (starPoints[i].y - center.y) * sin(rotateRadians) + center.x;
        double newY = (starPoints[i].x - center.x) * sin(rotateRadians) + (starPoints[i].y - center.y) * cos(rotateRadians) + center.y;
        starPoints[i].x = newX;
        starPoints[i].y = newY;
    }
}


void update_zoom(Point starPoints[], double zoompace) {
    
    double scale = (zoompace > 0) ? (1.0 / zoompace) : (-zoompace);

    
    Point center;
    center.x = (starPoints[0].x + starPoints[1].x + starPoints[2].x + starPoints[3].x + starPoints[4].x +
        starPoints[5].x + starPoints[6].x + starPoints[7].x + starPoints[8].x + starPoints[9].x) / 10.0;
    center.y = (starPoints[0].y + starPoints[1].y + starPoints[2].y + starPoints[3].y + starPoints[4].y +
        starPoints[5].y + starPoints[6].y + starPoints[7].y + starPoints[8].y + starPoints[9].y) / 10.0;

    
    for (int i = 0; i < 10; ++i) {
        starPoints[i].x = center.x + scale * (starPoints[i].x - center.x);
        starPoints[i].y = center.y + scale * (starPoints[i].y - center.y);
    }
}


Point calculatePoint(double r, double angleInDegrees) {
    Point p;
    double angleInRadians = angleInDegrees * M_PI / 180.0;
    p.x = r * cos(angleInRadians);
    p.y = r * sin(angleInRadians);
    return p;
}


void calculateStarPoints(Point starPoints[]) {
    double r = 1.0;
    double r_prime = r * sin(18 * M_PI / 180) / sin(126 * M_PI / 180);

    
    starPoints[0] = calculatePoint(r, 18);
    starPoints[1] = calculatePoint(r, 90);
    starPoints[2] = calculatePoint(r, 162);
    starPoints[3] = calculatePoint(r, 234);
    starPoints[4] = calculatePoint(r, 306);

    
    starPoints[5] = calculatePoint(r_prime, 54);
    starPoints[6] = calculatePoint(r_prime, 126);
    starPoints[7] = calculatePoint(r_prime, 198);
    starPoints[8] = calculatePoint(r_prime, 270);
    starPoints[9] = calculatePoint(r_prime, 342);
}

Point_float* convertPoints(Point* starPoints, Point_float* starPointnew, int size) {
    for (int i = 0; i < size; ++i) {
        starPointnew[i].x = static_cast<float>(starPoints[i].x);
        starPointnew[i].y = static_cast<float>(starPoints[i].y);
    }
    return starPointnew;
}

void generateVertices(float* vertices, Point_float* newPointer, int size) {
    
    srand(time(NULL));

    for (int i = 0; i < size; ++i) {
        
        vertices[i * 8] = newPointer[i].x;
        vertices[i * 8 + 1] = newPointer[i].y;
        vertices[i * 8 + 2] = 0.0f; 

        
        vertices[i * 8 + 3] = static_cast<float>(rand()) / RAND_MAX; 
        vertices[i * 8 + 4] = static_cast<float>(rand()) / RAND_MAX; 
        vertices[i * 8 + 5] = static_cast<float>(rand()) / RAND_MAX; 

        
        vertices[i * 8 + 6] = newPointer[i].x;
        vertices[i * 8 + 7] = newPointer[i].y;
    }
}

void generateindices(unsigned int* indices) {
    indices[0] = 0;  indices[1] = 5;  indices[2] = 9;  
    indices[3] = 1;  indices[4] = 6;  indices[5] = 5;  
    indices[6] = 2;  indices[7] = 6;  indices[8] = 7; 
    indices[9] = 3;  indices[10] = 7; indices[11] = 8; 
    indices[12] = 4; indices[13] = 8; indices[14] = 9; 

    indices[15] = 6; indices[16] = 7; indices[17] = 8; 
    indices[18] = 5; indices[19] = 8; indices[20] = 9; 
    indices[21] = 5; indices[22] = 6; indices[23] = 8; 
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "HOMEWORK", NULL, NULL);
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

    Shader ourShader("5.2.transform.vs", "5.2.transform.fs");

    Point starPoints[10];
    Point_float starPointnew[10]; 
    calculateStarPoints(starPoints);
    convertPoints(starPoints, starPointnew, 10);
    float vertices[10 * 8];
    generateVertices(vertices, starPointnew, 10);
    unsigned int indices[24];
    generateindices(indices);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
    
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


    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glm::mat4 transform = glm::mat4(1.0f); 


        transform = glm::translate(transform, glm::vec3(0.0f, (float)sin(glfwGetTime()), 0.0f));

        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

        transform = glm::scale(transform, glm::vec3((float)sin(glfwGetTime()), (float)sin(glfwGetTime()), (float)sin(glfwGetTime())));

        unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);


        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}