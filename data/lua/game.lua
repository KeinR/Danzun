_dan = {
    eidc = 0,
    entityReg = {},
    removeQueue = {},
    defaults = {
        mesh = Mesh.new{
            -- Simple quad
            vertices =
            {-1, -1, 0, 0,
            -1, 1, 0, 1,
            1, 1, 1, 1,
            1, -1, 1, 0},
            indices =
            {0, 1, 2,
            0, 2, 3},
            params = {
                {
                    size = 2,
                    stride = 4,
                    offset = 0
                },
                {
                    size = 2,
                    stride = 4,
                    offset = 2
                }
            }
        }
    }
}

--[[

Entity prototype:

entity = {
    logic = function,
    hit = function,
    _id = int, -- internal
    _begin = number, -- internal
    patternSet = [
        int, -- time
        function, -- callback
        ...
    ]

    -- These next ones are dependent on the type of
    -- entity hitbox (circle, polygon).

    -- Circle
    radius = number,
    x = number, -- center
    y = number -- center

    -- Polygon
    points = [
        -- Each point of the polygon, with the center reference being (0, 0)
        -- Min 3 to be valid
        {x = number, y = number},
        {x = number, y = number},
        {x = number, y = number},
        ...
    ]
    x = number, -- x translation
    y = number, -- y translation
    scale = number, -- scaling done to points before translation

}

]]--

gh = {}

function gh.registerEntity(o)
    eidc = _dan.eidc + 1
    -- Protects against the unlikely.
    -- Will run out of memory before all integers
    -- are filled, so I think that we're fine
    while _dan.entityReg[_dan.eidc] ~= nil do
        _dan.eidc = _dan.eidc + 1
    end
    o._id = _dan.eidc
    _dan.entityReg[o._id] = o
    return o._id
end

function gh.removeEntity(id)
    -- table.remove(_dan.entityReg, id)
    table.insert(_dan.removeQueue, id)
end

function gh.testCollisions()
    for i,v in pairs(_dan.removeQueue) do
        _dan.entityReg[v] = nil
    end
    _dan.removeQueue = {}
    for id,e in pairs(_dan.entityReg) do
        e.patternSet:call(e);
    end
    for id,e in pairs(_dan.entityReg) do
        e:logic(id);
    end

    game.testCollisions("player", "enemyBullets")
    game.testCollisions("player", "enemies")
    game.testCollisions("enemies", "playerBullets")
end

function hitHealth(self, other)
    self.health = self.health - other.damage
end


Pattern = {}
Pattern.__index = Pattern

function Pattern.new(p)
    local result = {
        data = p,
        currentIndex = 1,
        switchTime = game.getTime() + p[1]
    }
    setmetatable(result, Pattern);
    return result
end

function Pattern:check()
    -- NOTE: things will break if the time interval is too small
    if game.getTime() > self.switchTime then
        -- if currentIndex + 2 <= #data then
        --     currentIndex = currentIndex + 2
        -- else
        --     currentIndex = 1
        -- end
        -- switchTime = game.getTime() + data[currentIndex]
        if self.currentIndex + 2 <= #self.data then
            self.currentIndex = self.currentIndex + 2
            self.switchTime = game.getTime() + self.data[self.currentIndex]
        end
    end
end

function Pattern:call(handle)
    self:check()
    self.data[self.currentIndex+1](handle)
end



Clock = {
    time = 0,
    deltaTime = 0
}
Clock.__index = Clock

function Clock.new(o)
    if o == nil then
        o = {}
    end
    setmetatable(o, Clock);
    return o
end

function Clock:advance(seconds)
    self.time = self.time + seconds
    self.deltaTime = seconds
end

Timer = {}
Timer.__index = Timer

function Timer.new(clock, length)
    local result = {
        clock = clock,
        length = length,
        endTime = 0,
    }
    setmetatable(result, Timer)
    return result
end

function Timer:reset()
    self.endTime = self.clock.time + self.length
end

function Timer:done()
    return self.clock.time > self.endTime
end


Schedular = {}
Schedular.__index = Schedular

function Schedular.new(p)
    local result = {
        data = p,
        currentIndex = 1,
        switchTime = game.getTime() + p[1]
    }
    setmetatable(result, Schedular);
    return result
end

function Schedular:call(handle)
    if game.getTime() > self.switchTime then
        if self.currentIndex <= #self.data then
            self.switchTime = game.getTime() + self.data[self.currentIndex]
            self.data[self.currentIndex+1](handle)
            self.currentIndex = self.currentIndex + 2
        end
    end
end
