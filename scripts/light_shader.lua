addStage("shaders/light_shader.vert")
addStage("shaders/light_shader.frag")

setUniformLoc("baseTexture", 0)
setUniformLoc("cubeMap", 1)

uniform("diffuse", "vec3", { 0.4, 0.4, 0.4 })
uniform("specular", "vec3", { 0.2, 0.2, 0.2 })
uniform("shininess", "float", 0.2)