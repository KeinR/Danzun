
types = {
    IMAGE = 0,
    ASEPRITE = 1
}

lh = {}

function lh:execFile(path)
    func = loadFile(engine.getPath(path))
    func()
end

function lh:execStr(str)
    func = load(str)
    func()
end

function lh:addStage(o)

end

function lh:loadSprite(o)
    file = engine.getPath(o.file)
    if o.type == nil || o.type == type.IMAGE then
        engine.loadImage(o.name, file)
    elseif o.type == type.ASEPRITE then
        engine.loadAseprite(o.name, file)
    end
end

function lh:loadShader(o)
    return engine.loadShader(
        o.name,
        engine.getPath(o.vert),
        engine.getPath(o.frag)
    )
end
