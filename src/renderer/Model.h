#include <vttpch.h>

namespace Chimera {
    class Model {
    private:
        bgfx::VertexBufferHandle vertexBuffer;
        bgfx::IndexBufferHandle indexBuffer;
        bgfx::VertexLayout vertexLayout;
    public:
        Model(const float * vertices, int& verticesSize, const int * indices, int& indicesSize);
        ~Model();

        void bind();
    };
}