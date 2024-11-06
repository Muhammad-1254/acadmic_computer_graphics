#pragma once
#include <gl/glew.h>
#include <gl/gl.h>
#include <GL/freeglut.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

class Bullet1
{
public:
    GLuint textureID; // Texture ID for the bullet
    float bX, bY;    // Bullet position
    float rotationAngle; // Rotation angle for the bullet
    float is_fired = false;

    Bullet1(float x, float y, const std::string& textureFile);
    ~Bullet1();
    void render();
    void changePos(float dx, float dy);
    void setRotation(float angle);
    float get_x() const;
    float get_y() const;

    int textureWidth, textureHeight; // Dimensions of the texture
    void readBMP(const std::string& filename);
    void loadBMP(const std::string& filePath);
};

void Bullet1::loadBMP(const std::string& filePath) {
    unsigned char header[54]; // BMP header is 54 bytes
    unsigned int dataPos;
    unsigned int width, height;
    unsigned int imageSize;
    unsigned char* data;

    // Open the file
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "File could not be opened!" << std::endl;
        //return 0;
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
    //GLuint textureID;
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

    //return textureID;
}

void Bullet1::readBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening BMP file: " << filename << std::endl;
        return;
    }

    // Read BMP header (starting at byte 18 for width and height)
    file.seekg(18, std::ios::beg);
    file.read(reinterpret_cast<char*>(&textureWidth), sizeof(textureWidth));
    file.read(reinterpret_cast<char*>(&textureHeight), sizeof(textureHeight));

    // Calculate row size (rows are padded to 4-byte boundaries)
    int rowSize = (textureWidth * 3 + 3) & ~3;
    int imageSize = rowSize * textureHeight;

    // Allocate memory for pixel data
    std::vector<unsigned char> imageData(imageSize);

    // Read pixel data starting from byte 54
    file.seekg(54, std::ios::beg);
    file.read(reinterpret_cast<char*>(imageData.data()), imageSize);

    // Flip the image (BMP is stored bottom-up)
    std::vector<unsigned char> flippedData(imageSize);
    for (int i = 0; i < textureHeight; ++i) {
        std::memcpy(&flippedData[i * rowSize], &imageData[(textureHeight - i - 1) * rowSize], rowSize);
    }

    // Bind the texture
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // old
    //// Set texture parameters (important to avoid black texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    //new
    // Set texture parameters
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Specify the texture (with flipped data)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, flippedData.data());

    // Enable texturing
    glEnable(GL_TEXTURE_2D);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    file.close();

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}

Bullet1::Bullet1(float x, float y, const std::string& textureFile) : bX(x), bY(y), rotationAngle(0.0f) {
    
    readBMP(textureFile);
    //loadBMP(textureFile);

}

Bullet1::~Bullet1() {
    glDeleteTextures(1, &textureID);
}

//void Bullet1::render() {
//    // Save current transformation state
//    glPushMatrix();
//
//    // Translate to the bullet's position
//    glTranslatef(this->bX, this->bY, 0.0f);
//
//    // Translate to the center of the image to rotate around the center
//    float imageCenterX = textureWidth / 2.0f;
//    float imageCenterY = textureHeight / 2.0f;
//    glTranslatef(imageCenterX, imageCenterY, 0.0f);
//
//    // Apply the rotation around the Z-axis (for 2D rotation)
//    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
//
//    // Translate back to the original position
//    glTranslatef(-imageCenterX+5, -imageCenterY, 0.0f);
//
//    // Bind and draw the texture
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageCenterX, -imageCenterY);  // Bottom-left
//    glTexCoord2f(1.0f, 0.0f); glVertex2f(imageCenterX, -imageCenterY);   // Bottom-right
//    glTexCoord2f(1.0f, 1.0f); glVertex2f(imageCenterX, imageCenterY);    // Top-right
//    glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageCenterX, imageCenterY);   // Top-left
//    glEnd();
//
//    // Unbind texture
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//    // Restore the transformation state
//    glPopMatrix();
//}

void Bullet1::render() {
    glPushMatrix();

    // Translate to the bullet's position
    glTranslatef(this->bX, this->bY, 0.0f);

    // Translate to the center of the image to rotate around the center
    float imageCenterX = textureWidth / 2.0f;
    float imageCenterY = textureHeight / 2.0f;
    glTranslatef(imageCenterX, imageCenterY, 0.0f);

    // Apply the rotation around the Z-axis (for 2D rotation)
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);

    // Translate back to the original position
    glTranslatef(-imageCenterX + 5, -imageCenterY, 0.0f);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Draw a textured quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageCenterX, -imageCenterY);  // Bottom-left
    glTexCoord2f(1.0f, 0.0f); glVertex2f(imageCenterX, -imageCenterY);   // Bottom-right
    glTexCoord2f(1.0f, 1.0f); glVertex2f(imageCenterX, imageCenterY);    // Top-right
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageCenterX, imageCenterY);   // Top-left
    glEnd();

    // Disable texturing
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}
//void Bullet1::render() {
//    glEnable(GL_TEXTURE_2D);
//
//    // Save current transformation state
//    glPushMatrix();
//
//    // Translate to the bullet's position
//    glTranslatef(this->bX, this->bY, 0.0f);
//
//    // Translate to the center of the image to rotate around the center
//    float imageCenterX = textureWidth / 2.0f;
//    float imageCenterY = textureHeight / 2.0f;
//    glTranslatef(imageCenterX, imageCenterY, 0.0f);
//
//    // Apply the rotation around the Z-axis (for 2D rotation)
//    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
//
//    // Translate back to the original position
//    glTranslatef(-imageCenterX, -imageCenterY, 0.0f);
//
//    // Bind and draw the texture
//    glBindTexture(GL_TEXTURE_2D, textureID);
//    GLenum err = glGetError();
//    if (err != GL_NO_ERROR) {
//        std::cerr << "OpenGL Error before drawing: " << err << std::endl;
//    }
//
//    glBegin(GL_QUADS);
//    glTexCoord2f(0.0f, 0.0f); glVertex2f(-imageCenterX, -imageCenterY);  // Bottom-left
//    glTexCoord2f(1.0f, 0.0f); glVertex2f(imageCenterX, -imageCenterY);   // Bottom-right
//    glTexCoord2f(1.0f, 1.0f); glVertex2f(imageCenterX, imageCenterY);    // Top-right
//    glTexCoord2f(0.0f, 1.0f); glVertex2f(-imageCenterX, imageCenterY);   // Top-left
//    glEnd();
//
//    err = glGetError();
//    if (err != GL_NO_ERROR) {
//        std::cerr << "OpenGL Error after drawing: " << err << std::endl;
//    }
//
//    // Unbind texture
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//    // Restore the transformation state
//    glPopMatrix();
//
//    // Disable texturing
//    glDisable(GL_TEXTURE_2D);
//}

void Bullet1::changePos(float dx, float dy) {
    bX += dx;
    bY += dy;
}

void Bullet1::setRotation(float angle) {
    rotationAngle = angle;
}

float Bullet1::get_x() const {
    return bX;
}

float Bullet1::get_y() const {
    return bY;
}
