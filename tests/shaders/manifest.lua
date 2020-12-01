sprite = Shader.new("shaders/sprite.vert", "shaders/sprite.frag");
sprite:setInt("tex", 0)

text = Shader.new("shaders/text.vert", "shaders/text.frag");
text:setInt("atlas", 0)
