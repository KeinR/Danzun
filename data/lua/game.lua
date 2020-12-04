_dan = {
    eidc = 0,
    entityReg = {},
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
    id = int,
    patternSet = [
        {
            time = int,
            callback = function
        }
    ]

    -- These next ones are dependent on the type of
    -- entity hitbox (circle, rectangle, polygon).
    -- howerver, all of them will have:
    -- for representing their center coordinates

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
    trans = userdata, -- translation matrix for points

}

]]--

gh = {}

function gh.registerEntity(o)
    eidc = _dan.eidc + 1
    -- Protects against the unlikely.
    -- Will run out of memory before all integers
    -- are filled, so I think that we're fine
    while entities[_dan.eidc] ~= nil do
        _dan.eidc = _dan.eidc + 1
    end
    o.id = _dan.eidc
    _dan.entityReg[o.id] = o
    return o.id
end

function gh.testCollisions()
    for id,e in _dan.entityReg do
        e:logic(id);
    end

    game.testCollisions("player", "enemyBullets")
    game.testCollisions("player", "enemies")
    game.testCollisions("enemies", "playerBullets")
end

function hitHealth(self, other)
    self.health = self.health - other.damage
end
