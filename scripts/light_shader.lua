addStage("shaders/light_shader.vert")
addStage("shaders/light_shader.frag")

setUniformLoc("baseTexture", 0)
setUniformLoc("cubeMap", 1)

uniform("material.ambient", "vec3", { 0.4, 0.4, 0.4 })
uniform("material.diffuse", "vec3", { 0.4, 0.4, 0.4 })
uniform("material.specular", "vec3", { 0.2, 0.2, 0.2 })
uniform("material.shininess", "float", 0.2)