sprite = lh.loadShader{
    name = "sprite",
    vert = "sprite.vert",
    frag = "sprite.frag"
}
-- shader.__index = shader
-- shader.setUniformInt(sprite, "tex", 0)
-- setmetatable(sprite, shader)
sprite:setInt("tex", 0)

text = lh.loadShader{
    name = "text",
    vert = "text.vert",
    frag = "text.frag"
}
text:set("atlas", 0)

-- engine.setDefaultShader(sprite)
