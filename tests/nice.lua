
function pause(seconds)
    coroutine.yield(seconds)
end

function lEntityMat(entity)
    Matrix.new(entity):load()
end


BasicSprite = {}

function BasicSprite.new(img, mesh, shader)
    local res = {
        img = img,
        mesh = mesh,
        shader = shader
    }
    local wrapper = Element.new(BasicSprite.render, res)
    return wrapper
end

function BasicSprite:render(entity)

    self.shader:use()
    self.img:bind()

    mat = Matrix.new()
        mat.x = entity.x
        mat.y = entity.y
        mat.width = entity.width
        mat.height = entity.height
    mat:load()

    self.mesh:render()
end


-- For use by Animation
Frame = {}

function Frame.new(img, coords, shader, duration)
    local res = {
        img = img,
        mesh = Mesh.new(),
        shader = shader,
        duration = duration -- In seconds
    }

    res.mesh:setVertices{
        -1, -1, coords[1], coords[2],
        -1, 1, coords[3], coords[4],
        1, 1, coords[5], coords[6],
        1, -1, coords[7], coords[8]
    }
    res.mesh:setIndices{
        0, 1, 2,
        0, 2, 3
    }
    res.mesh:setParam(0, 2, 4, 0)
    res.mesh:setParam(1, 2, 4, 2)

    return res;
end


Animation = {}

-- Length of frames must be at least 1
function Animation.new(frames)
    local res = {
        frames = frames,
        index = 1,
        frameEnd = game:getTime() + frames[1].duration
    }

    local wrapper = Element.new(Animation.render, res)
    return wrapper
end

function Animation:render(e)
    local skips = 0 -- Prevent possible near-infinate loop from short frames
    while game:getTime() >= self.frameEnd and skips < 100 do
        if self.index < #self.frames then
            -- Advance
            self.index = self.index + 1
        else
            -- Loop
            self.index = 1
        end
        self.frameEnd = self.frameEnd + self.frames[self.index].duration
        skips = skips + 1
    end

    local f = self.frames[self.index];
    f.shader:use()
    f.img:bind()
    f.mesh:render()
end
