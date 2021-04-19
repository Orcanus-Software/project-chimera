#include <vttpch.h>

#include "Model.h"

namespace Chimera {
    Model::Model(const float * vertices, int& verticesSize, const int * indices, int& indicesSize) 
    {
        vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .end();

        vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices, verticesSize), vertexLayout);
        indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indices, indicesSize));
    }

    Model::~Model() {}

    void Model::bind() 
    {
        bgfx::setVertexBuffer(0, vertexBuffer);
        bgfx::setIndexBuffer(indexBuffer);
    }
}