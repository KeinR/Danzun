
Basic = {
    pos = vec2.new{x = 0, y = 0},
    vel = vec2.new{x = 0, y = 0},
    radius = 10,
}

function Basic:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    regShotCollision(self)
    return o
end

