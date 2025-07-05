# Simple-Application-Based-on-OpenGL、

In the branch "Simple Moving Pentagon," a texture and color blending assignment for a pentagon has been implemented, and translation, rotation, and scaling have been achieved in a 2D plane.
在branch：Simple Moving Pentagon中，实现了一个五角星的纹理和颜色混合赋值，而且在平面中实现平移、旋转和缩放

In the branch "Swinging Robot," a texture assignment for a robot has been implemented, and the robot rotates in 3D space, accompanied by the swinging of its arms and legs.
在branch：Swinging Robot中，实现了一个机器人的纹理赋值，而且在立体中旋转，伴随着手臂和腿部的摆动。


在branch：main中，实现了一个基于城市环境的移动大巴模拟构建，具体内容如下：

声明：
注意！！！
受限于一些原因，该工程配置较为复杂，建议自行配置外界库并进行C++基于visual studio的链接，工程的重点是代码文件中的实际C++代码，希望这里面的代码能够带来一些思路上的参考，不建议直接照搬我的代码进行复现，如果真想复现，可以按照下面的说明进行，不过还是强烈不建议。
branch中的代码则比较简单，可以直接照搬复现
程序中涉及包括assimp-5.4.1、glfw-3.4、glm-master等外界库文件，这些都是目前非常流行的外界库，此外，还有很多.obj素材，这些素材大都难以找到出处来源，如有侵权，可以联系直接删除。

作品创作者：
“基于城市环境的移动大巴模拟构建”项目由Wang Yi主导，Xue Kaihan、Jiang Ruisheng、Zhang Heng、Li Wenluo几人合作开发；其它几个branch的内容则是由Wang Yi独立开发

1.设计概述
  本设计为基于城市环境的移动大巴模拟构建，即在一个模拟城市环境中，进行大巴的运行和控制，并且实时反馈结果。总体上来看，我们的总体底座为基于city.obj文件构建的城市模型，城市模型本身包含了高大复杂建筑物、道路、街道装饰等等。在城市模型之外，我们构建了天空盒以显示天空效果，并且在城市外的低处构建了海面模型，在正上方的天空添加了云层模型以显示云层效果。我们在视野的正前方构建了大巴模型，我们可以通过鼠标、键盘控制大巴的动作，大巴可以在城市中运行，而且视野会随着鼠标的移动而进行180度自由的变换。但大巴超过城市边界或触碰到障碍物时，大巴会有相应的爆炸解体效果，随后运行结束。我们还加入了小车模型，使用连续渲染使其在道路上直线行驶。
  总体上看，本设计结合大部分我们所学过的技术，包括外界模型的导入和解析着色、基于变换的地物摆放和场景构建、光源设计和光照渲染、阴影渲染、基于边界检测的障碍物识别、基于法向量的模型网格平移和变换、基于时间计算的地物循环移动、天空盒设置等等。

2.配置方法（警告：看前述声明）
（1）下载文件后，创建一个名为“workfinal2_”的文件夹用以存储文件
（2）在该文件夹中继续加入两个文件夹，分别名为txx和vis2022work
（3）txx文件夹中放入我在main中标注的几个Head File文件即可
（4）vis2022work文件夹中再创建一个同名的vis2022work文件夹
（5）在vis2022work文件夹中分别配置assimp-5.4.1、glfw-3.4、glm-master几个外界库文件夹，这几个文件夹自行到对应的外界库下载即可，是常用的C++外界库
（6）在vis2022work文件夹中创建名为objects文件夹，将vis2022work_vis2022work_objects标记的几个压缩文件解压放入即可
（7）在vis2022work文件夹中将vis2022work_vis2022work_skybox标记的压缩文件解压放入
（8）在vis2022work文件夹中创建一个名为Workfinal的文件夹，将vis2022work_vis2022work_Workfinal标记的压缩文件解压放入

3.运行情况
在开启时，会有一段时间的白屏时间，因为场景较大，部分地物比较复杂，所以需要较长的时间来渲染和构建，具体时间依电脑配置而定。在启动开始后，会首先看见大巴出现在眼前，然后在右侧会有一辆小车缓缓驶来，小车抵达左侧后就会自动消失，重新又在右侧起点处出现，可以控制大巴在城市的道路上行驶，使用鼠标可以展现大巴180度的视角变化，使用键盘的“W”“A”“S”“D”键可以控制大巴前进、左旋、后退、右旋，“Q”键可以进入自由漫游模式。但大巴行驶到城市边缘时，可以看到城市外部是一片广阔的海面，还有背景的蓝色天空，朝天上看，可以看到城市的顶部由一片云所笼罩，在城市街道中行驶，可以很显著地看到光照的不同，所有地物都有着鲜明的阴影效果，当大巴超出城市边界或者是超过了马路边缘时，大巴会瞬间产生碎裂效果，碎片四散而开，并且无法继续控制大巴，在数秒的场面之后自动退出程序，表示游戏失败。

4.我们的制作过程

模型导入、地物坐标设计和天空盒创建
首先，我们在sketchup上寻找相关模型，刚开始，我们是准备使用一些高级的模型，即一些格式较复杂的模型，但是后来在引入模型的过程中遇到了较大的困难，发现其中需要更改比较底层的配置，我们在尝试了一周后放弃了这条路径，后来，我们直接按照.obj去寻找标准模型，在网上找到了某个日本城市相关的模型，包括城市模型、大巴模型、小车模型、云朵模型、大海模型。于是，我们分别导出了其.obj文件作为实际模型并取得了成功。以下是相关代码：
    Model car(FileSystem::getPath("objects/car/car.obj"));
    Model bus(FileSystem::getPath("objects/bus/bus.obj"));
    Model city(FileSystem::getPath("objects/city/city.obj"));
    Model cloud(FileSystem::getPath("objects/cloud/cloud.obj"));
    Model sea(FileSystem::getPath("objects/sea/sea.obj"));
    Model wheel(FileSystem::getPath("objects/wheel/wheel.obj"));
我们参考并移植了learnopengl中模型加载章节的部分内容，并根据我们的实际情况进行了更改，加载模型的具体细节都在model.h和mesh.h之中。
在mesh.h头文件中，Vertex结构体定义了构成网格顶点的数据，包括位置、法线、纹理坐标、切线、副法线以及ID和权重。Texture结构体存储了纹理的ID、类型和路径信息。Mesh类构造函数接受顶点、索引和纹理的向量作为参数，复制这些数据到类成员，并调用setupMesh方法来初始化网格。Draw函数使用传入的Shader对象来渲染网格。它设置纹理单元、绑定纹理、设置着色器的uniform变量，并使用glDrawElements来绘制网格。setupMesh用于设置网格的OpenGL缓冲区，包括生成VAO、VBO和EBO，绑定缓冲区，并将顶点和索引数据上传到GPU。同时，它还设置了顶点属性指针，用于顶点属性的配置。
在Model.h头文件中，Model类封装了从模型文件加载数据、处理场景图、创建网格和纹理，并最终渲染模型的过程。使用Assimp库来处理不同的3D模型格式，使其可以加载复杂的3D场景，并在OpenGL中进行渲染。
总的来说，模型引入部分的原理主要就是将.obj的网格进行了遍历着色并全部输出，使其成为一个可以被呈现和改造的模型。
最后我们进行了地物坐标设计，我们首先设定了不同地物的初始坐标，将不同地物聚拢在一起，进一步判断其朝向和大小关系，这里可以暂时忽略carrealposition和busrealposition，因为这里和地物摆放无关，主要是用来标记后续的车辆位置的。
glm::vec3 cityposition(35.0f, -6.05f, 0.0f);
glm::vec4 carrealposition(0.0f, -6.05f, 0.0f, 1.0f);
glm::vec4 busrealposition(0.0f, -6.05f, 0.0f, 1.0f);
glm::vec3 busposition(0.0f, -6.05f, 0.0f);
glm::vec3 cloudPosition(0.0f,150.5f, -0.0f);
glm::vec3 carPosition(0.0f, -6.05f, 0.0f);
glm::vec3 seaPosition(2.0f, -50.05f, 4.0f);
随后，我们通过初始位置地物的状态，对地物进行缩放、平移和旋转，将地物放到合适的位置，我们将云朵摆放到距离地面相当远的垂直位置，将海面摆放到城市地面以下，并将大巴放置到城市中央的初始位置（不能允许大巴刚开始就出现在道路之外，这样一开始就会触发障碍物碰撞机制导致大巴爆炸），这里综合利用了变换矩阵，参见以下的代码：（这里只展示海面、云朵和城市相关的代码，因为大巴和小车本身还和后续的控制、运动有关，会有更复杂的代码，在后续会讲到）：
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
接下来，我们设置天空盒，即在城市的外围使用一个巨大的天空盒包围起来，我们定义天空盒的具体坐标，对天空盒进行内部贴图，这里使用的贴图不是普通的贴图，而是参考了learnopengl中的立方体贴图方法，随后将天空盒放大到足够大的状态，使得整个城市模型都被包裹其中。我们刚开始准备使用旧有的贴图，但是我们发现原有贴图中包含了海面，当放在场景中时，会与我们的海面模型产生视觉的不适感，所以我们只使用了贴图中天空的部分，并且在六个面上都贴了相同的图片，这样就没有贴图中的海面和实际的海面相冲突的问题了。
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
     skyboxShader.use();
      skyboxShader.setMat4("view", view);
      skyboxShader.setMat4("projection", projection);

      glBindVertexArray(skyboxVAO);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
      glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);

基于鼠标和键盘的车辆控制
为了实现好封装独立性，避免原有代码过于冗杂，我们创建了一个car.h专门进行车辆控制代码的编写，以下是car.h中的代码：（这里省去了预编译的代码，只写其中发挥实际作用的部分）
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
这个类模拟了大巴的基本行为和属性，使得在主程序中可以很方便地创建具有位置、方向和旋转属性的游戏对象。每个对象都具有一个位置向量，表示它在世界空间中的坐标；一个前方向量，表示对象朝向的方向；一个上方向量，通常用于确定对象的垂直方向；以及一个右侧向量，垂直于前向和上向量，用于确定对象的水平方向。
类中的构造函数初始化了这些基本向量，并计算了初始的右侧向量，processInput 方法允许对象根据用户的输入（如键盘或控制器操作）在空间中移动。通过改变对象的位置，可以模拟向前或向后移动。processturn 方法则允许对象围绕垂直轴旋转，即偏航（Yaw）的增加或减少，从而改变其前方向。
updateVectors 方法用于根据当前的偏航角重新计算前方向量和右侧向量，确保它们始终垂直于上方向量，这对于保持对象在空间中的正确方向至关重要。rotate 方法提供了更高级的旋转功能，允许对象绕任意轴旋转，这在需要更复杂旋转操作时非常有用。此外，类还提供了几个获取器（getter）方法，允许外部代码查询对象的位置、偏航角和前方向量，这在渲染、碰撞检测或其他游戏逻辑中需要使用。
在主程序中，我们也写了相关代码进行总体的调用操作：
Camera camera(glm::vec3(0.0f, 8.0f, 0.0f));
GameObject buspos(glm::vec3(0.0f, 0.0f, 0.0f));

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool stop = false;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;


     if (!stop){
        busposition = buspos.Getobjposition();
        model = glm::translate(model, busposition);
        model = glm::scale(model, glm::vec3(0.01f, 0.01f, 0.01f));
        }
      if (!stop)
        {
            busrotation = buspos.Getobjrotation();
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
在主程序中，我们进行了游戏循环控制、用户输入处理、窗口和输入回调、摄像机和对象控制、停止游戏逻辑、鼠标首次输入处理、初始化和帧时间计算等等操作。
在初始化和帧时间计算中，创建了一个Camera对象和一个GameObject对象，分别用于控制摄像机视角和大巴的位置和旋转，同时初始化了一些变量。
在游戏循环控制中，首先检查是否应该停止游戏（例如，通过按键输入）。如果不是，则更新公交车的位置和模型变换，包括平移和缩放。
在用户输入处理中，processInput和processInput1函数处理键盘输入，允许用户通过WASD键控制摄像机的前后左右移动。Q键用于停止游戏。carmove函数处理键盘输入，控制公交车的前后移动和左右转向。转向逻辑通过检测按键的按下和释放来实现。
在窗口和输入回调函数中，framebuffer_size_callback函数用于处理窗口大小变化事件，通过调用glViewport来更新OpenGL的视口大小。mouse_callback函数处理鼠标移动事件，通过计算鼠标的偏移量来更新摄像机的视角。scroll_callback函数处理鼠标滚轮滚动事件，可用于摄像机的缩放。
在摄像机和对象控制中，摄像机的ProcessKeyboard和ProcessMouseMovement方法用于根据用户的键盘和鼠标输入来更新摄像机的位置和视角。公交车的processInput和processturn方法用于根据用户的键盘输入来更新公交车的位置和偏航角。
在停止游戏的逻辑中，在processInput、processInput1和carmove函数中，如果用户按下了ESC键，则调用glfwSetWindowShouldClose函数，请求关闭窗口并停止游戏循环。
在鼠标首次输入处理中，在mouse_callback函数中，如果检测到是第一次鼠标输入，则记录当前鼠标位置，并设置firstMouse标志为false，以便于后续处理鼠标移动。

车辆障碍物检测、车辆碎裂效果显示和小车自动循环运动
随后，我们加入车辆障碍物检测。刚开始我们准备引入障碍物外框法进行处理，但是后来我们发现没有必要使用这种方法，因为车辆本身是在城市模型中进行平面移动的，所以说只需要在平面中做边界检测就可以轻松实现车辆的障碍物检测。但是由于之前坐标系已经发生了比较复杂的变化，难以使用坐标变换的方式计算出城市模型中各个地方的边界。因此，我们直接在大巴运动的过程中加入返回值，让大巴沿着边界线跑一圈，然后在关键节点处记录相应坐标值，最后根据坐标值设定边界约束就可以了。如图13是在城市模型中的平面障碍物示意图，显示了整个城市模型的结构，依据此我们设计了边界示意图，通过竖向和横向的约束规定边界约束。我们优先使用数量较少的横向约束将整张图分为五个区域，然后在每个区域依次使用竖向约束分类讨论决定是否碰撞到障碍物。
根据结果，我们写出了判定大巴是否越过障碍物的相关函数：

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
经过实际调试和验证，证明这项障碍物检测方法虽然比较笨拙，但是非常有效，大巴能够有效地在整个城市模型中进行自动障碍物检测。
随后，我们需要在大巴检测到自身碰到障碍物时产生碎裂效果，这里我们参考了learnopengl中的几何着色器方法产生这样的效果。在每个网格上沿着法向量的方向进行移动，使得总的效果就像是物体在爆炸一样，在geometry_shader.fs、geometry_shader.gs和geometry_shader.vs中，分别有着产生爆炸效果的不同着色器程序，分别列在下面：
#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{
      FragColor = texture(texture_diffuse1, TexCoords);
}

#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT {
      vec2 texCoords;
} gs_in[];

out vec2 TexCoords; 

uniform float time;

vec4 explode(vec4 position, vec3 normal)
{
      float magnitude = 2.0;
      float t;
      if(sin(time)>=1){
        t = 1;
      }
      else{
        t = time;
      }
      vec3 direction = normal * ((2*t + 1.0) / 7.0) * magnitude; 
      return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
      vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
      vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
      return normalize(cross(a, b));
}

void main() {    
      vec3 normal = GetNormal();

      gl_Position = explode(gl_in[0].gl_Position, normal);
      TexCoords = gs_in[0].texCoords;
      EmitVertex();
      gl_Position = explode(gl_in[1].gl_Position, normal);
      TexCoords = gs_in[1].texCoords;
      EmitVertex();
      gl_Position = explode(gl_in[2].gl_Position, normal);
      TexCoords = gs_in[2].texCoords;
      EmitVertex();
      EndPrimitive();
}

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
      vec2 texCoords;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main()
{
      vs_out.texCoords = aTexCoords;
      gl_Position = projection * view * model * vec4(aPos, 1.0); 
}
由于我们的爆炸效果是需要大巴碎片一瞬间达到一定距离，然后开始缓慢向外移动的，所以在第二段着色器代码中，加入t变量，并且更改了移动速度的大小，使得t能够瞬间达到较大值，然后缓慢增加。
为了与上面的着色器程序相配合，我们在主程序中也进行了设计，加入了一些判断逻辑使得大巴能够停下一切动作并且在爆炸数秒后自动退出程序，表示游戏结束。为了使得爆炸更为流畅，在渲染循环上我们进行了进一步的研究，我们采用了glfw中的时间变量来进行渲染的累计。
另外，我们同样使用了glfw的时间变量来实现小车的自动移动，我们让小车从街道的一端出发，然后以合适的速度移动，到达街道的另外一端后小车又会重新回到起点，并且重新出发。
以下是主程序中主要起作用的代码，需要指出的是，其中的w0、tem等变量主要是用于标记用，有的是用来记录碰到障碍物的瞬时时间，有的是用来记录小车的运行距离，这些变量能够有效帮助到后面爆炸循环和小车运动循环的逻辑：
float w0 = static_cast<float>(glfwGetTime());
float w1 = -2000;
float w2 = 0;
int tem = 1;
int k0 = -1;

if (test_obstacle(buspos) == FALSE) {
        goto label;
}
if (stop)
        processInput1(window);
else
        processInput(window);
carmove(window, turn);
label:


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

光照、阴影渲染和其他
光照和阴影渲染主要参考了learnopengl中的方法，由于在整个场景中，渲染的对象不是普通的立方体，而是各种.obj的模型，因此着色器的渲染应当是针对于.obj的所有网格而言的。我们首先设置了光源的位置，并且使用了深度测试的方法，对于模型求解出遮挡与被遮挡的关系，从而进一步确定阴影的区域。我们主要是使用了shadow_mapping_depth.vs、shadow_mapping_depth.fs、shader.vs、shader.fs进行这一操作的。在主程序中，我们使用了下列的代码进行光照和阴影渲染：

glm::vec3 lightPos(25.0f, 50.0f, 25.0f);
Shader ourShader("shader.vs", "shader.fs");
Shader simpleDepthShader("shadow_mapping_depth.vs", "shadow_mapping_depth.fs");

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

ourShader.use();
ourShader.setVec3("lightColor", 0.8f, 0.8f, 0.8f);
ourShader.setVec3("lightPos", lightPos);
ourShader.setVec3("viewPos", 0.0f, 0.0f, 8.0f);

以下是shader.fs的代码，该片段着色器进行光照计算，首先定义了输出颜色FragColor和输入变量，包括从顶点着色器传入的顶点位置、法线、纹理坐标以及在光照空间中的顶点位置。代码中使用了uniform变量来存储光照颜色、位置、观察者位置和纹理信息。
核心功能包括环境光、漫反射和镜面反射的计算，以及阴影效果的实现。环境光提供了场景的基础亮度，漫反射计算了光直接照射到物体表面的效果，而镜面反射则模拟了光在物体表面的反射。阴影计算通过在光照空间中采样阴影映射来实现，减少阴影的锯齿效果。
最终，这些光照效果与纹理颜色结合，生成了最终的像素颜色，输出到FragColor。这段着色器代码是实现逼真3D渲染的关键部分，通过模拟真实世界的光照和阴影效果，增强了视觉效果。

#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords; 
in vec4 FragPosLightSpace;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform sampler2D texture_diffuse; 
uniform sampler2D shadowMap;

float ShadowCalculation(vec4 fragPosLightSpace)
{
      vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
      projCoords = projCoords * 0.5 + 0.5;
      float closestDepth = texture(shadowMap, projCoords.xy).r; 
      float currentDepth = projCoords.z;
      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPos);
      float bias = max(0.05 * (1.0 - dot(norm, lightDir)), 0.005);
      float shadow = 0.0;
      vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
      for(int x = -1; x <= 1; ++x)
      {
          for(int y = -1; y <= 1; ++y)
          {
              float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
              shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
          }    
      }
      shadow /= 9.0;
      return shadow;
}

void main()
{
      float ambientStrength = 0.9;
      vec3 ambient = ambientStrength * lightColor;

      vec3 norm = normalize(Normal);
      vec3 lightDir = normalize(lightPos);
      float diff = max(dot(norm, lightDir), 0.0);
      vec3 diffuse = diff * lightColor;

      float specularStrength = 0.5;
      vec3 viewDir = normalize(viewPos - FragPos);
      vec3 reflectDir = reflect(-lightDir, norm);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
      vec3 specular = specularStrength * spec * lightColor;

      vec3 textureColor = texture(texture_diffuse, TexCoords).rgb;

      float shadow = ShadowCalculation(FragPosLightSpace); 

      vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * textureColor;
      FragColor = vec4(result, 1.0);
}
以下是shader.vs的代码，用于处理3D图形的顶点变换和光照准备，定义了输入顶点位置aPos、法线aNormal和纹理坐标aTexCoords，以及输出到片段着色器的变量，负责将顶点从模型空间转换到裁剪空间，并准备必要的数据以供片段着色器进行光照和阴影计算。
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 FragPosLightSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
      FragPos = vec3(model * vec4(aPos, 1.0));
      Normal = mat3(transpose(inverse(model))) * aNormal;
      TexCoords = vec2(aTexCoords.x, 1.0f-aTexCoords.y);
      FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
      gl_Position = projection * view * vec4(FragPos, 1.0);
}
以下是shadow_mapping_depth.fs和shadow_mapping_depth.vs的代码，比较简短，在第一个片段没有进行操作，在第二个片段上设置了在阴影映射中的顶点位置，接收一个顶点位置aPos作为输入，并使用uniform变量lightSpaceMatrix和model来执行矩阵变换，生成阴影映射，其中lightSpaceMatrix通常用于将顶点从模型空间变换到特定的光源空间，以便在深度图中捕捉场景的深度信息。

#version 330 core
  
void main()
{             
} 

#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main()
{
      gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}
以上就是光照渲染的部分，能够让场景中的所有模型都能进行光照和阴影的渲染，使得场景更加真实。目前来讲已经基本包含了程序中的所有部分，但还有少数代码没有提及，包括其中对于opengl的初始化操作，包括窗口创建、基本量初始化等等，然后还有几个VAO和VBO的操作，由于比较简单，这里也不再赘述，具体的可以参见后面附加的详细代码。

