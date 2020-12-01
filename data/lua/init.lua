
-- types = {
--     IMAGE = 0,
--     ASEPRITE = 1
-- }

-- lh = {}

-- function lh.loadSprite(o)
--     local file = engine.getPath(o.file)
--     if o.type == nil or o.type == types.IMAGE then
--         return engine.loadImage(o.name, file)
--     elseif o.type == types.ASEPRITE then
--         return engine.loadAseprite(o.name, file)
--     end
-- end

-- function lh.loadShader(o)
--     return engine.loadShader(
--         o.name,
--         engine.getPath(o.vert),
--         engine.getPath(o.frag)
--     )
-- end


-- Defined natively
-- Image = {}
-- Image.__index = Image
-- function Image.new(path)
--     r = {}
--     setmetatable(r, Image)
--     r.handle = resource.loadImage(path)
-- end


