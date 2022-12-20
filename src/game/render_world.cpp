#include "render_world.h"
#include "map.h"

#include "../entity/camera.h"

#include "../global.h"
#include "../graphics/graphic_options.h"

#include "../graphics/light.h"
#include "../graphics/skybox.h"
#include "../graphics/renderer.h"

#include "scene.h"

namespace game {
    class RenderWorldImpl : public RenderWorld {
    public:
        RenderWorldImpl(Scene &scene, graphics::Renderer &renderer)
            : m_camera{global.graphic_options->size().width(), global.graphic_options->size().height()},
            m_scene{scene},
            m_renderer{renderer}
        {
            graphics::DirLight dir_light;
            dir_light.direction = { 0, -1.0f, -1.0f };
            dir_light.ambient = {0.05f, 0.05f, 0.05f};
            dir_light.diffuse = {0.8f, 0.8f, 0.8f};
            m_dir_lights.push_back(dir_light);

            graphics::PointLight pointLight;
            pointLight.position = { 2.0f, 2.0f, 0 };
            pointLight.ambient = {0.2f, 0.2f, 0.2f};
            pointLight.diffuse = {0.8f, 0.8f, 0.8f};
            pointLight.specular = {0.5f, 0.5f, 0.5f};
            pointLight.constant = 0.5f;
            pointLight.linear = 0.09f;
            pointLight.quadratic = 0.032f;

            m_point_lights.push_back(pointLight);

            this->m_map = std::make_unique<Map>();
        }

        void update() override {
            auto components = m_scene.ecs()->get_component_array<entity::ECStaticModel>()->values();

            for (auto component : components) {
                auto entity = component->entity;
                auto &ec_static_renderer = entity.get<entity::ECStaticModel>();
                auto &transform = entity.get<entity::ECTransform>();

                if (ec_static_renderer.model()->state() == graphics::MODEL_HIDDEN) {
                    continue;
                }

                m_renderer.render(*this, ec_static_renderer.model().get(), transform);
            }
        }

        constexpr ALWAYS_INLINE entity::Camera& camera() override { return m_camera; }
        constexpr ALWAYS_INLINE std::vector<graphics::DirLight>& dir_lights() override { return m_dir_lights; }
        constexpr ALWAYS_INLINE std::vector<graphics::PointLight>& point_lights() override { return m_point_lights; }
        constexpr ALWAYS_INLINE std::unique_ptr<Map>& map() override { return m_map; }
        constexpr ALWAYS_INLINE graphics::Skybox& skybox() override { return m_skybox; }
    private:
        Scene &m_scene;
        graphics::Renderer& m_renderer;

        entity::Camera m_camera;

        std::vector<graphics::DirLight> m_dir_lights;
        std::vector<graphics::PointLight> m_point_lights;

        graphics::Skybox m_skybox;
        std::unique_ptr<Map> m_map;
    };

    std::unique_ptr<RenderWorld> RenderWorld::create(Scene &scene, graphics::Renderer &renderer) {
        return std::make_unique<RenderWorldImpl>(scene, renderer);
    }
}
