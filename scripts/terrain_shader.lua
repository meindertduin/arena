addStage("shaders/terrain.vert")
addStage("shaders/terrain.frag")

uniform("material.ambient", "vec3", { 0.4, 0.4, 0.4 })
uniform("material.diffuse", "vec3", { 0.4, 0.4, 0.4 })
uniform("material.specular", "vec3", { 0.2, 0.2, 0.2 })
uniform("material.shininess", "float", 0.2)
