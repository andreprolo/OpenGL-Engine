#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <assimp/Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Engine/Shader/Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    window = glfwCreateWindow(1000, 1000, "OpenGL - Engine", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        printf("Failed to init GLEW\n");

        glfwTerminate();        
        return -1;
    }

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    unsigned int EBO;
    glGenBuffers(1, &EBO);    

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    Shader engineShader("assets/shaders/shader.vs", "assets/shaders/shader.fs");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    float xOffset = -0.3f;
    float yOffset = 0.2f;
    float xSpeed = 0.006f;
    float ySpeed = 0.005f;

    glm::vec3 rgb = glm::vec3(1.0f, 0.0f, 0.0f);    

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("assets/wall.jpg", &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "FAILED TO LOAD TEXTURE" << std::endl;
    }

    stbi_image_free(data);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        engineShader.use();
        //engineShader.setFloat("xOffset", xOffset);
        //engineShader.setFloat("yOffset", yOffset);
        //engineShader.setVec3Float("customColor", rgb);

        xOffset += sin(xSpeed);
        yOffset += sin(ySpeed);

        if (xOffset < -(1 - 0.05f) || xOffset > 1 - 0.05f) {
            xSpeed *= -1.2f;

            rgb.x = static_cast <float> (rand() / static_cast<float> (RAND_MAX));
            rgb.y = static_cast <float> (rand() / static_cast<float> (RAND_MAX));
            rgb.z = static_cast <float> (rand() / static_cast<float> (RAND_MAX));
        }

        if (yOffset < -(1 - 0.05f) || yOffset > 1 - 0.05f) {
            ySpeed *= -1.2f;
            
            rgb.x = static_cast <float> (rand() / static_cast<float> (RAND_MAX));
            rgb.y = static_cast <float> (rand() / static_cast<float> (RAND_MAX));
            rgb.z = static_cast <float> (rand() / static_cast<float> (RAND_MAX));
        }

        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
