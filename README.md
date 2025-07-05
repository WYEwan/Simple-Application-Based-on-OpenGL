# Simple-Application-Based-on-OpenGL、

In the branch "Simple Moving Pentagon," a texture and color blending assignment for a pentagon has been implemented, and translation, rotation, and scaling have been achieved in a 2D plane.
在branch：Simple Moving Pentagon中，实现了一个五角星的纹理和颜色混合赋值，而且在平面中实现平移、旋转和缩放

In the branch "Swinging Robot," a texture assignment for a robot has been implemented, and the robot rotates in 3D space, accompanied by the swinging of its arms and legs.
在branch：Swinging Robot中，实现了一个机器人的纹理赋值，而且在立体中旋转，伴随着手臂和腿部的摆动。


在branch：main中，实现了一个基于城市环境的移动大巴模拟构建，具体内容如下：

作品创作者：
“基于城市环境的移动大巴模拟构建”项目由Wang Yi主导，Xue Kaihan、Jiang Ruisheng、Zhang Heng、Li Wenluo几人合作开发；其它几个branch的内容则是由Wang Yi独立开发

1.设计概述
  本设计为基于城市环境的移动大巴模拟构建，即在一个模拟城市环境中，进行大巴的运行和控制，并且实时反馈结果。总体上来看，我们的总体底座为基于city.obj文件构建的城市模型，城市模型本身包含了高大复杂建筑物、道路、街道装饰等等。在城市模型之外，我们构建了天空盒以显示天空效果，并且在城市外的低处构建了海面模型，在正上方的天空添加了云层模型以显示云层效果。我们在视野的正前方构建了大巴模型，我们可以通过鼠标、键盘控制大巴的动作，大巴可以在城市中运行，而且视野会随着鼠标的移动而进行180度自由的变换。但大巴超过城市边界或触碰到障碍物时，大巴会有相应的爆炸解体效果，随后运行结束。我们还加入了小车模型，使用连续渲染使其在道路上直线行驶。
  总体上看，本设计结合大部分我们所学过的技术，包括外界模型的导入和解析着色、基于变换的地物摆放和场景构建、光源设计和光照渲染、阴影渲染、基于边界检测的障碍物识别、基于法向量的模型网格平移和变换、基于时间计算的地物循环移动、天空盒设置等等。

2.配置方法
下载文件后，创建一个名为“workfinal2_”的文件夹用以存储文件
在该文件夹中继续加入两个文件夹，分别名为txx和vis2022work
txx文件夹中放入我在main中标注的几个.h文件即可


