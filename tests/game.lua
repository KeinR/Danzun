

require("nice")


-- First thing that runs, before window
-- opens
function preInit()
    window:setTitle("Danzun test")
    window:setSize(500, 700)
    game:setSize(500 * 2, 700 * 2)
    -- loadingScreen = Image.new("load.jpg")
end

-- This is looped over as init() blocks
function loadMain()
    
end

-- Stuff to do asynchronously while loadMain is running
function init()

end

function start()

    player.speed = 150

    mesh = Mesh.new()
    mesh:setVertices{
        -1, -1, 0, 0,
        -1, 1, 0, 1,
        1, 1, 1, 1,
        1, -1, 1, 0
    }
    mesh:setIndices{
        0, 1, 2,
        0, 2, 3
    }
    mesh:setParam(0, 2, 4, 0)
    mesh:setParam(1, 2, 4, 2)
    shader = Shader.new("shaders/sprite.vert", "shaders/sprite.frag")
    shader:setInt("tex", 0)

    circleShader = Shader.new("shaders/circle.vert", "shaders/circle.frag");
    circleShader:setInt("tex", 0)
    circleShader:setFloat("color", 1, 1, 1, 1)

    textShader = Shader.new("shaders/text.vert", "shaders/text.frag");
    textShader:setInt("atlas", 0)
    textShader:setFloat("color", 0, 0, 0, 1)

    mat = Matrix.new()
    mat.width = 30
    mat.height = 30

    img = Image.new("sprites/bullet.png");

    conf = BasicSprite.new(img, mesh, shader);

    img = Image.new("sprites/ghost.png");

    entConf = BasicSprite.new(img, mesh, shader);


    bvars_data = {m = 4};

    bvars = PatternVars.new(bvars_data)

    script = Script.new(loadfile("test.dzs"))

    playerImg = Image.new("sprites/charge.png");

    playerRenderFunc = function(e)
        shader:use()
        Matrix.new(e):load()
        playerImg:bind()
        mesh:render()
    end

    pyrConf = Element.new(playerRenderFunc, nil)


    font = BffFont.new("consolas18.bff")


    local e = Entity.new(
        function(self, other)
            -- print ("player hit!")
        end,
        pyrConf,
        [[
            x := px;
            y := py;
        ]]
    );
    e:regCircle("player")
    e.width = 40
    e.height = 40



    magicCircleImg = Image.new("magic circle.png")

    effect = Effect.new(1, magicCircleEffect, nil)

    effectPattern = Pattern.new([[
        x := px;
        y := py;
        height -= dt * 10;
        width -= dt * 10;
        rotation += dt;
        if (height < 100) {
            done := true;
        }
    ]])
    effectPattern.width = 150
    effectPattern.height = 150
    effectPattern.rotation = 0

    effect:spawn(effectPattern)

    player.x = 100
    player.y = 100

    game.gcInterval = 1
    game.running = true

    engine.vSync = false
    engine.maxFPS = 60


    lazarShadar = Shader.new("shaders/lazer.vert", "shaders/lazer.frag");
    lazarBeamElement = Element.new(
        function (e)
            lazarShadar:use()
            lazarShadar:setFloat("color", 0.2, game:getTime() % 1, 0.2, 1)
            Matrix.new(e):load()
            mesh:render()

            -- print("px = " .. player.x)
            -- print("py = " .. player.y)
        end,
        nil
    )
    zapCounter = 0
    lazarBeam = Entity.new(
        function(self, other)
            print ("ZAP!")
        end,
        lazarBeamElement,
        [[
            rotation += dt;
            if (t - st > 0.5) {
                display := not(display);
                tangible := not(tangible);
                st := t;
            }
        ]]
    )

    lazarBeam.x = 200
    lazarBeam.y = 400
    lazarBeam.width = 30
    lazarBeam.height = 300
    lazarBeam.rotation = 1
    lazarBeam.pivotX = 0
    lazarBeam.pivotY = 150
    lazarBeam:regPolygon("enemyBullets", {
        -1, -1,
        -1, 1,
        1, 1,
        1, -1
    })



    music = Sound.openStream("test.ogg")
    print("Statis...")
    if not music.failed then
        print("Music loaded successfuly")
        music:play()
    else
        print("Failed to load music...")
    end

    bulletShotSound = Sound.loadFile("effect.wav")
    if not bulletShotSound.failed then
        print("Effect loaded successfuly")
        bulletShotSound:play()
    else
        print("Failed to load effect...")
    end


end

function magicCircleEffect(m, lst)
    for i,o in ipairs(lst) do

        o:run()

        local vertices = {
            -- x, y, tex x, tex y
            -- (counter clockwise)
        }
        local indices = {}
        -- Generate annulus
        local iterations = 60
        local step = 2 * math.pi / iterations
        local texStep = 1 / iterations
        -- Next two MUST add up to 1
        local radius = 0.6
        local thickness = 0.4
        local stride = 4
        local totalVertices = iterations * 2
        for i=0,iterations do
            -- Vertices

            local radians = step * i
            local ix = radius * math.cos(radians)
            local iy = radius * math.sin(radians)
            -- Could replace r + t with 1
            local ox = (radius + thickness) * math.cos(radians)
            local oy = (radius + thickness) * math.sin(radians)
            local ixt = i * texStep
            local iyt = 0
            local oxt = ixt
            local oyt = 1
            -- Positional
            table.insert(vertices, ix)
            table.insert(vertices, iy)
            -- Texture
            table.insert(vertices, ixt)
            table.insert(vertices, iyt)
            -- Positional
            table.insert(vertices, ox)
            table.insert(vertices, oy)
            -- Texture
            table.insert(vertices, oxt)
            table.insert(vertices, oyt)

            -- Indices

            local tv = i * 2

            -- Inner (close, far, next close)
            table.insert(indices, tv)
            table.insert(indices, (tv+1) % totalVertices)
            table.insert(indices, (tv+2) % totalVertices)

            -- Inner (next close, far, next far)
            table.insert(indices, (tv+2) % totalVertices)
            table.insert(indices, (tv+1) % totalVertices)
            table.insert(indices, (tv+3) % totalVertices)

        end

        local m = Mesh.new()
        m:setVertices(vertices)
        m:setIndices(indices)
        m:setParam(0, 2, 4, 0)
        m:setParam(1, 2, 4, 2)
        local mat = Matrix.new()
        mat.x = o.x
        mat.y = o.y
        mat.width = o.width
        mat.height = o.height
        mat.rotation = o.rotation

        circleShader:use()
        mat:load()
        magicCircleImg:bind()
        m:render()



        local text = "MAGIC CIRCLE"

        local fmat = Matrix.new()
        fmat.x = o.x
        fmat.y = o.y - 10
        fmat.width = font:getStrWidth(text)
        fmat.height = font:getHeight()

        local fm = font:makeMesh(text)

        textShader:use()
        fmat:load()
        font:bind()
        fm:render()
    end

end


function main()

    script:run()

    game:testCollisions("player", "enemyBullets")
    game:testCollisions("enemies", "playerBullets")

end
