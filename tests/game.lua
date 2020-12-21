
entities = {}

-- First thing that runs, before window
-- opens
function preInit()
    -- window.setTitle("DAnzun test")
    -- window.setSize(500, 700)
    -- loadingScreen = Image.new("load.jpg")
    -- clock = Clock.new();
end

-- This is looped over as init() blocks
function loadMain()
    
end

-- Stuff to do asynchronously while loadMain is running
function init()

end

function start()

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

    mat = Matrix.new()
    mat.width = 30
    mat.height = 30

    img = Image.new("sprites/bullet.png");

    conf = RenderConfig.new(img, mesh, shader);

    img = Image.new("sprites/ghost.png");

    entConf = RenderConfig.new(img, mesh, shader);


    bvars_data = {m = 4};

    bvars = PatternVars.new(bvars_data)

    -- script = Script.new(loadfile("test.dzs"))
    script = Script.new(loadfile("test.dzs"))

    playerImg = Image.new("sprites/charge.png");

    pyrConf = RenderConfig.new(playerImg, mesh, shader);




    game:spawnEntityFull(
        function(self, other)
            print ("player hit!")
        end,
        pyrConf,
        [[
            x := px;
            y := py;
        ]],
        {},
        {},
        0, 0,
        30, 30,
        false,
        "player", 0
    );


    -- for y=0,400,5 do
    --     game:spawnEntityFull(
    --         function(self, other)
    --             print ("something hit...")
    --         end,
    --         conf,
    --         [[
    --             if (t - ti < 5) {
    --                 x += sgn(px - x) * dt * 10;
    --             } else {
    --                 y += sgn(px - y) * dt * 10;
    --             }
    --         ]],
    --         {}, {},
    --         300, y,
    --         10, 10,
    --         false,
    --         "enemyBullets", 0
    --     );
    -- end
    -- for y=0,400,5 do
    --     game:spawnEntityFull(
    --         function(self, other)
    --             print ("something hit...")
    --         end,
    --         conf,
    --         [[
    --             if (t - ti < 5) {
    --                 x += sgn(px - x) * dt * 10;
    --             } else {
    --                 y += sgn(px - y) * dt * 10;
    --             }
    --         ]],
    --         {}, {},
    --         200, y,
    --         10, 10,
    --         false,
    --         "enemyBullets", 0
    --     );
    -- end

    magicCircleImg = Image.new("magic circle.png")

    effect = Effect.new(
        {},
        magicCircleEffect,
        1
    )

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
    end

end


function main() -- main(e)


    -- shader:use()
    -- mat:load()
    -- img:bind()
    -- mesh:render()

    -- conf:setup()
    -- mat:load()
    -- conf:render()

    -- bvars_data.m = bvars_data.m + 0.1

    -- bvars:push()

    -- script:run()

    -- shader:use()
    -- mat.x = player:getX();
    -- mat.y = player:getY();
    -- mat:load()
    -- playerImg:bind()
    -- mesh:render()

    game:testCollisions("player", "enemyBullets")
    game:testCollisions("enemies", "playerBullets")

end
