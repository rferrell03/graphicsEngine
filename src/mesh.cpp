#include "mesh.h"

Mesh::Mesh(const float* vertices, size_t size, const VertexLayout& layout){
    vertexCount = static_cast<int>(size / (5 * sizeof(float)));
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);


    for (const auto& attrib : layout.attributes) {
        glVertexAttribPointer(attrib.index, attrib.size, GL_FLOAT, GL_FALSE, layout.stride, (void*) attrib.offset);
        glEnableVertexAttribArray(attrib.index);
    }

    glBindVertexArray(0);
}


void Mesh::draw() const{
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}