
Ghost = {
    x = 0,
    y = 0,
    v = {x = 0, y = 0},
    radius = 25 / 2
}

Ghost.__index = Ghost

function Ghost.new(pattern, o)
    o = o or {}
    o.patternSet = Pattern.new(pattern)
    setmetatable(o, Ghost)
    gh.registerEntity(o)
    return o
end

function Ghost:logic()
    game.regCircleCol(self._id, "enemies", self.x, self.y, self.radius)
    self:render()
end

function Ghost:render()
    ghost:render{
        x = self.x,
        y = self.y,
        width = ghost:getWidth(),
        height = ghost:getHeight(),
    }
end

function Ghost:hit(o)
    gh.removeEntity(self._id)
end

