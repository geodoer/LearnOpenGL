// glad(OpenGL address), �������Ǵ�������̬�����ļ��м�������ָ�루֧�ֿ�ƽ̨��
// glad.h�а�����OpenGLͷ�ļ�����GL/gl.h�������Ҫ����ǰ�棬��ֹ����������������gl.h
#include <glad/glad.h>
// Graphics Library Framework, �������Ǵ������ڣ�֧�ֿ�ƽ̨����OpenGL������
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
    glfwInit(); //��ʼ��GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  //����GLFW������ʹ�õ�OpenGL�汾��3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //����ģʽ

#ifdef __APPLE__
    //�����Mac OS Xϵͳ������Ҫ���д��룬��Щ���ò���������
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
    glfwMakeContextCurrent(window); //֪ͨGLFW�����Ǵ��ڵ�����������Ϊ��ǰ�̵߳�����������
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    //�����κ�OpenGL����֮ǰ����Ҫ��ʼ��GLAD
    // ---------------------------------------
    //������������ϵͳ��ص�OpenGL����ָ���ַ�ĺ���
    //GLFW�����ǵ���glfwGetProcAddress�����������Ǳ����ϵͳ��������ȷ�ĺ���
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // render loop
    // ���ǿɲ�ϣ��ֻ����һ��ͼ��֮�����ǵ�Ӧ�ó���������˳����رմ��ڣ������Ҫһ��whileѭ��
    //  Ҳ�ɳ�֮Ϊ��Ⱦѭ����Render Loop��
    // -----------
    while (!glfwWindowShouldClose(window)) //���GLFW�Ƿ�Ҫ���˳�
    {
        // input
        // -----
        processInput(window);

        //��Ⱦָ��
        //...

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window); //������ɫ���壬���������֡ͼ����ʾ����Ļ��
        glfwPollEvents();   //����¼������´���״̬����������Ӧ�Ļص�����
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // �ͷ�GLFW���õ�����Դ
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
// ���û��ı䴰�ڴ�С��ʱ���ӿ�ҲӦ�ñ����������Ҫ�Դ���ע��һ���ص�����
//  ÿ�����ڴ�С������ʱ���˺������ᱻ���á���Ȼ�����ڵ�һ����ʾʱ��Ҳ�ᱻ����
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    // ��Ⱦ֮ǰ����һ����Ҫ������Ҫ��������Ҫ����OpenGL��Ⱦ���ڵĳߴ��С�����ӿ�
    //   ���OpenGL��֪���������ݴ��ڴ�С��ʾ���ݺ�����
    glViewport(0, 0, width, height);
    // ǰ�����������ƴ������½ǵ�λ�ã�����������������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����ص�λ��
    //  OpenGL�Ὣ[-1,1]��Χ�ڵ�����ӳ�䵽(0, 800)��(0, 600)��
}
