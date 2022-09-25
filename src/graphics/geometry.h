#pragma once

#include <glm/glm.hpp>
#include "gpu_buffer.h"
#include "mesh.h"

namespace graphics {
    class GpuPlane : public Renderable {
    public:
        GpuPlane();

        void render() const override;
        void set_size_and_position(const glm::vec2 &size, const glm::vec2 &pos) {
            vertices[0].pos = { pos.x, pos.y + size.y };
            vertices[1].pos = { pos.x, pos.y };
            vertices[2].pos = { pos.x + size.x, pos.y };
            vertices[3].pos = { pos.x, pos.y + size.y };
            vertices[4].pos = { pos.x + size.x, pos.y };
            vertices[5].pos = { pos.x + size.x, pos.y + size.y };

            this->array_buffer.set_data(0, sizeof(Vertex) * 6, vertices);
        }
    private:
        struct Vertex {
            glm::vec2 pos;
            glm::u16vec2 textcoords;
        };

        Vertex vertices[6] = {
                {{xpos, ypos + height}, {0x0000, 0x0000}},
                {{xpos, ypos}, {0x0000, 0xFFFF}},
                {{xpos + width, ypos}, {0xFFFF, 0xFFFF}},
                {{xpos, ypos + height}, {0x0000, 0x0000}},
                {{xpos + width, ypos}, {0xFFFF, 0xFFFF}},
                {{xpos + width, ypos + height}, {0xFFFF, 0x0000}},
        };

        float width{0};
        float height{0};
        float xpos{0};
        float ypos{0};

        VertexBuffer vertex_buffer { sizeof(Vertex) };
        ArrayBuffer array_buffer;
    };
}