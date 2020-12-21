
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
    shader:setInt1("tex", 0)

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
