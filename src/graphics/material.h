#pragma once

#include <glm/glm.hpp>

namespace graphics {
    struct Material {
        Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float shininess) :
            ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) { }

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        bool reflects { false };
        float shininess;
    };
}
