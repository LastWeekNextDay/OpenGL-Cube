//
// Created by LastWeek on 24/12/2023.
//

#include "CubeObject.h"

CubeObject::CubeObject(float scl) {
    scale = scl;
    float val = 0.5f * scale;

    // Front face
    face_vertices[0][0] = vector3D<GLfloat>(-val, -val, val);
    face_vertices[0][1] = vector3D<GLfloat>(val, -val, val);
    face_vertices[0][2] = vector3D<GLfloat>(val, val, val);
    face_vertices[0][3] = vector3D<GLfloat>(-val, val, val);

    // Back face
    face_vertices[1][0] = vector3D<GLfloat>(-val, -val, -val);
    face_vertices[1][1] = vector3D<GLfloat>(val, -val, -val);
    face_vertices[1][2] = vector3D<GLfloat>(val, val, -val);
    face_vertices[1][3] = vector3D<GLfloat>(-val, val, -val);

    // Left face
    face_vertices[2][0] = vector3D<GLfloat>(-val, -val, -val);
    face_vertices[2][1] = vector3D<GLfloat>(-val, -val, val);
    face_vertices[2][2] = vector3D<GLfloat>(-val, val, val);
    face_vertices[2][3] = vector3D<GLfloat>(-val, val, -val);

    // Right face
    face_vertices[3][0] = vector3D<GLfloat>(val, -val, -val);
    face_vertices[3][1] = vector3D<GLfloat>(val, -val, val);
    face_vertices[3][2] = vector3D<GLfloat>(val, val, val);
    face_vertices[3][3] = vector3D<GLfloat>(val, val, -val);

    // Top face
    face_vertices[4][0] = vector3D<GLfloat>(-val, val, -val);
    face_vertices[4][1] = vector3D<GLfloat>(val, val, -val);
    face_vertices[4][2] = vector3D<GLfloat>(val, val, val);
    face_vertices[4][3] = vector3D<GLfloat>(-val, val, val);

    // Bottom face
    face_vertices[5][0] = vector3D<GLfloat>(-val, -val, -val);
    face_vertices[5][1] = vector3D<GLfloat>(val, -val, -val);
    face_vertices[5][2] = vector3D<GLfloat>(val, -val, val);
    face_vertices[5][3] = vector3D<GLfloat>(-val, -val, val);

    // Set all faces to white
    for (auto & face_color : face_colors) {
        face_color = vector3D<float>(1.0f, 1.0f, 1.0f);
    }
}

float CubeObject::getScale() const {
    return scale;
}

void CubeObject::setScale(float scl) {
    for (auto & vertice : face_vertices) {
        for (auto & vector : vertice){
            vector /= scale;
            vector *= scl;
        }
    }
    scale = scl;
}

void CubeObject::draw() {
    glBegin(GL_QUADS);
    int face_index = 0;
    for (auto & vertice : face_vertices) {
        glColor3f(face_colors[face_index][0],
                  face_colors[face_index][1],
                  face_colors[face_index][2]);
        for (auto & vector : vertice){
            glVertex3f(vector.x, vector.y, vector.z);
        }
        face_index++;
    }
    glEnd();
}

vector3D<float> CubeObject::getRandomColor() {
    vector3D<float> color{};
    std::seed_seq seed{std::chrono::system_clock::now().time_since_epoch().count()};
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    for (int i = 0; i < 3; ++i) {
        color[i] = distribution(generator);
    }
    return color;
}

bool CubeObject::isDrawingFaceColors() const {
    return drawFaceColors;
}

void CubeObject::setDrawFaceColors(bool shouldDrawFaceColors) {
    if (drawFaceColors == shouldDrawFaceColors)
        return;
    drawFaceColors = shouldDrawFaceColors;
    if (!drawFaceColors)
        clearFaceColors();
    else
        if (!areFacesColored())
            randomizeFaceColors();
}

void CubeObject::randomizeFaceColors() {
    if (drawFaceColors){
        for (auto & face_color : face_colors) {
            face_color = getRandomColor();
        }
    }
}

bool CubeObject::areFacesColored() const {
    for (auto & face_color : face_colors) {
        if (face_color.x != 1.0f || face_color.y != 1.0f || face_color.z != 1.0f)
            return true;
    }
    return false;
}

void CubeObject::clearFaceColors() {
    for (auto & face_color : face_colors) {
        face_color = vector3D<float>(1.0f, 1.0f, 1.0f);
    }
}


