#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>

#include "gpu_buffer.h"

namespace graphics {
    constexpr int MAX_DIR_LIGHTS = 4;
    constexpr int MAX_POINT_LIGHTS = 8;

    constexpr int DIR_LIGHT_STD140_SIZE = 64;
    constexpr int POINT_LIGHT_STD140_SIZE = 112;

    class Light {
    public:
        virtual void setData(SharedDataBuffer &buffer) = 0;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    class DirLight : public Light {
    public:
        DirLight() {  }
        ~DirLight() {  }
        void set_data(SharedDataBuffer &buffer) {
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(direction));
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(ambient));
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(diffuse));
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(specular));
        }

        glm::vec3 direction;
    };

    class PointLight : public Light {
    public:
        PointLight() {  }
        ~PointLight() {  }
        void set_data(SharedDataBuffer &buffer) {
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(position));
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(ambient));
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(diffuse));
            buffer.set_data(sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(specular));

            buffer.set_data(16, sizeof(float), &constant);
            buffer.set_data(16, sizeof(float), &linear);
            buffer.set_data(16, sizeof(float), &quadratic);
        }

        glm::vec3 position;
        float constant;
        float linear;
        float quadratic;
    };
}
