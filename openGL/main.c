#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

int main(void){
    GLFWwindow* window;

    if(!glfwInit()){
        printf("error!\n");
        return -1;
    }

    window = glfwCreateWindow(800, 600, "window1", NULL, NULL);
    if(!window){
        printf("window error\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        printf("GLEW error\n");
        glfwTerminate();
        return -1;
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
    glEnd();

    
    
    while(!glfwWindowShouldClose(window)){
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}