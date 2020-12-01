
Ghost = {
    pos = vec2.new{x = 0, y = 0},
    vel = vec2.new{x = 0, y = 0},
    radius = 10,
    patternSet = [
        {
            time = 0,
            callback = function(h)
                
            end
        }
    ]
}

function Ghost:new(o)
    o = o or {}
    setmetatable(o, self)
    self.__index = self
    game.regEnemy(self)
    return o
end

function Ghost:delete()
    game.clearEnemy(self)
end

function hit(damage)
    
end

function Ghost:logic(deltaTime)
    game.regCollision()
    if deltaTime % 50 == 0 then
        game.addBullet("basic", 50, 50, 0, {vx = 5, vy = 4}, patternSet)
    end

end

function Ghost:render()
    game.renderSprite("ghost", pos)
end

