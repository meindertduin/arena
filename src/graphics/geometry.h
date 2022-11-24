#pragma once

#include <glm/glm.hpp>
#include "gpu_buffer.h"
#include "mesh.h"
#include "rect.h"
#include "../global.h"
#include "../graphics/graphic_options.h"

namespace graphics {
    class GpuPlane : public IRenderAble {
    public:
        GpuPlane();

        void render() const override;

        void set_from_rect(const IRect &rect) {
            auto gl_rect = convert_to_gl_rect(rect);
            vertices[0].pos = { gl_rect.position().x(), gl_rect.position().y() + gl_rect.size().height() };
            vertices[1].pos = { gl_rect.position().x(), gl_rect.position().y() };
            vertices[2].pos = { gl_rect.position().x() + gl_rect.size().width(), gl_rect.position().y() };
            vertices[3].pos = { gl_rect.position().x(), gl_rect.position().y() + gl_rect.size().height() };
            vertices[4].pos = { gl_rect.position().x() + gl_rect.size().width(), gl_rect.position().y() };
            vertices[5].pos = { gl_rect.position().x() + gl_rect.size().width(), gl_rect.position().y() + gl_rect.size().height() };

            this->array_buffer.set_data(0, sizeof(Vertex) * 6, vertices);
        }

        void set_pos_and_size(const glm::vec2 &pos, const glm::vec2 &size) {
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