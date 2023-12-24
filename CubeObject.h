//
// Created by LastWeek on 24/12/2023.
//

#ifndef OPENGL_PROJ_CUBEOBJECT_H
#define OPENGL_PROJ_CUBEOBJECT_H

#include "gl.h"
#include <vector.h>
#include <random>
#include <chrono>


class CubeObject {
private:
    vector3D<GLfloat> face_vertices[6][4]{};
    vector3D<GLfloat> face_colors[6]{};
    float scale = 1;
    bool drawFaceColors = false;
public:
    explicit CubeObject(float scl = 1);
    ~CubeObject() = default;

    float getScale() const;
    void setScale(float scl);

    bool isDrawingFaceColors() const;
    void setDrawFaceColors(bool shouldDrawFaceColors);

    bool areFacesColored() const;

    void draw();

    void randomizeFaceColors();
    void clearFaceColors();
private:
    vector3D<float> getRandomColor();
};


#endif //OPENGL_PROJ_CUBEOBJECT_H
