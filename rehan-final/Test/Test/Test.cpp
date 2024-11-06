#include <GL/freeglut.h>
#include <iostream>
#include <fstream>

GLuint textureID;

// Function to load a BMP image
GLuint loadBMP(const char* filePath) {
    unsigned char header[54]; // BMP header is 54 bytes
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char* data;

    // Open the file
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
        return 0;
    }

    // Read the header
    file.read(reinterpret_cast<char*>(header), 54);

    // Extract image dimensions
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    // If the image size is missing, calculate it
    if (imageSize == 0) imageSize = width * height * 3; // 3 bytes per pixel (24 bits)
    if (dataPos == 0) dataPos = 54; // BMP data starts after header

    // Create a buffer to store the image data
    data = new unsigned char[imageSize];

    // Read the image data
    file.seekg(dataPos, std::ios::beg);
    file.read(reinterpret_cast<char*>(data), imageSize);
    file.close();

    // Generate a texture ID
    GLuint textureID;
    glGenTextures(1, &textureID);

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load the texture data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // Free the image data
    delete[] data;

    return textureID;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable 2D texturing
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Draw a textured quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
    glEnd();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers();
}

void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    // Load BMP texture
    textureID = loadBMP("bullet3.bmp");

    if (!textureID) {
        std::cerr << "Failed to load texture" << std::endl;
        exit(1);
    }
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Display BMP Image");

    // Initialize OpenGL
    initOpenGL();

    // Set display callback
    glutDisplayFunc(display);

    // Start the GLUT main loop
    glutMainLoop();

    return 0;
}
