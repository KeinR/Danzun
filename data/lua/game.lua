
function pause(seconds)
    coroutine.yield(seconds)
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

function BasicSprite.render(entity, s)

    s.shader:use()
    s.img:bind()

    mat = Matrix.new()
        mat.x = entity.x
        mat.y = entity.y
        mat.width = entity.width
        mat.height = entity.height
    mat:load()

    s.mesh:render()
end

