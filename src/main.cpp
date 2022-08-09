#include <stdio.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/glad.h>

int main () {
    glfwInit();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
       printf("Couldnt setup GLAD\n");
   }

    printf("Hello\n");
    return 0;
}
