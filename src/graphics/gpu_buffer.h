#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace graphics {
    class GpuBuffer {
    public:
        virtual ~GpuBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;
    protected:
        uint32_t id;
    };

    class ArrayBuffer : GpuBuffer {
    public:
        ArrayBuffer();
        ~ArrayBuffer() override;

        ArrayBuffer(const ArrayBuffer&) = delete;
        ArrayBuffer(ArrayBuffer&&) = delete;
        ArrayBuffer& operator=(const ArrayBuffer&) = delete;
        ArrayBuffer& operator=(ArrayBuffer&&) = delete;

        void bind() const override;
        void unbind() const override;

        void set_data(int offset, std::size_t size, const void *data);
    };

    class VertexBuffer : GpuBuffer {
    public:
        struct VertexAttribute {
            int amount;
            int type;
            std::size_t size_type;
            bool normalized;
        };

        VertexBuffer(const VertexBuffer&) = delete;
        VertexBuffer(VertexBuffer&&) = delete;
        VertexBuffer& operator=(const VertexBuffer&) = delete;
        VertexBuffer& operator=(VertexBuffer&&) = delete;

        explicit VertexBuffer(int total_size);
        ~VertexBuffer() override;

        void bind() const override;
        void unbind() const override;

        void add_vertex_attribute(const VertexAttribute &attribute);
    private:
        std::size_t total_size;
        std::size_t current_size;

        std::vector<VertexAttribute> vertex_attributes;
    };

    class SharedDataBuffer : GpuBuffer {
    public:
        int offset = 0;
        std::size_t size;

        SharedDataBuffer(int binding_block, std::size_t size);
        ~SharedDataBuffer() override;

        SharedDataBuffer(const SharedDataBuffer&) = delete;
        SharedDataBuffer(SharedDataBuffer&&) = delete;
        SharedDataBuffer& operator=(const SharedDataBuffer&) = delete;
        SharedDataBuffer& operator=(SharedDataBuffer&&) = delete;

        void set_data(int format_size, std::size_t size, const void *data);
        void reset();
        void set_offset(int offset);

        void bind() const override;
        void unbind() const override;
    };
}
