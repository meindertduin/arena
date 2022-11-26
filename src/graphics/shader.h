#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../platform/platform.h"
#include "../core/path.h"
#include "../assets/resource.h"

namespace graphics {
    constexpr int MATRICES_BLOCK_BINDING = 0;
    constexpr int LIGHTS_BLOCK_BINDING = 1;

    enum class ShaderType {
        Vertex,
        Fragment,
    };

    class Shader : public assets::Resource {
    public:
        explicit Shader(const Path &path);
        ~Shader();

        Shader(const Shader &other) = delete;
        Shader(Shader &&other) = delete;

        Shader& operator=(const Shader &other) = delete;
        Shader& operator=(Shader &&other) = delete;

        [[nodiscard]] constexpr ALWAYS_INLINE uint32_t id() const { return m_id; }

        // TODO make these functions private
        void load(std::size_t size, char *data) override;
        void unload() override { }
    private:
        uint32_t m_id{};
        ShaderType m_type;
    };

    class ShaderProgram  {
    public:
        struct ShaderProgramData {
            std::string vertex_shader_path;
            std::string frag_shader_path;
        };

        std::shared_ptr<Shader> m_vertex_shader;
        std::shared_ptr<Shader> m_fragment_shader;

        explicit ShaderProgram(const std::string &path);
        ~ShaderProgram();

        void use() const;
        void link() const;

        void set_property(const std::string& property_name, int) const;
        void set_property(const std::string& property_name, float) const;
        void set_property(const std::string& property_name, glm::vec3&&) const;
        void set_property(const std::string& property_name, glm::vec4&&) const;
        void set_property(const std::string& property_name, glm::mat4&&) const;
        void set_property(const std::string& property_name, const glm::vec3&) const;
        void set_property(const std::string& property_name, const glm::vec4&) const;
        void set_property(const std::string& property_name, const glm::mat4&) const;

        void set_uniform_loc(const std::string& name, int index) const;
    private:
        uint32_t id{};
        uint32_t program;
    };
}
