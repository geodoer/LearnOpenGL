// glad(OpenGL address), 帮助我们从驱动动态链接文件中检索函数指针（支持跨平台）
// glad.h中包含了OpenGL头文件（如GL/gl.h），因此要放在前面，防止其他第三方库依赖gl.h
#include <glad/glad.h>
// Graphics Library Framework, 帮助我们创建窗口（支持跨平台）和OpenGL上下文
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // https://www.glfw.org/docs/latest/window.html#window_hints
    // ------------------------------
    glfwInit(); //初始化GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //告诉GLFW，我们使用的OpenGL版本是3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //核心模式

#ifdef __APPLE__
    //如果是Mac OS X系统，还需要这行代码，这些配置才能起作用
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); //通知GLFW将我们窗口的上下文设置为当前线程的主上下文了
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    //调用任何OpenGL函数之前，需要初始化GLAD
    // ---------------------------------------
    //传入用来加载系统相关的OpenGL函数指针地址的函数
    //GLFW给我们的是glfwGetProcAddress，它根据我们编译的系统定义了正确的函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // render loop
    // 我们可不希望只绘制一个图像之后我们的应用程序就立即退出并关闭窗口，因此需要一个while循环
    //  也可称之为渲染循环（Render Loop）
    // -----------
    while (!glfwWindowShouldClose(window)) //检查GLFW是否被要求退出
    {
        // input
        // -----
        processInput(window);

        //渲染指令
        //...

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window); //交换颜色缓冲，将绘制完的帧图像显示在屏幕上
        glfwPollEvents();   //检查事件、更新窗口状态，并调用相应的回调函数
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // 释放GLFW所用到的资源
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// 当用户改变窗口大小的时候，视口也应该被调整，因此要对窗口注册一个回调函数
//  每当窗口大小被调整时，此函数都会被调用。当然，窗口第一次显示时，也会被调用
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    // 渲染之前还有一个重要的事情要做，必须要告诉OpenGL渲染窗口的尺寸大小，即视口
    //   如此OpenGL才知道怎样根据窗口大小显示数据和坐标
    glViewport(0, 0, width, height);
    // 前两个参数控制窗口左下角的位置；后两个参数控制渲染窗口的宽度和高度（像素单位）
    //  OpenGL会将[-1,1]范围内的坐标映射到(0, 800)和(0, 600)上
}
