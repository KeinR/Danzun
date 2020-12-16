
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
    -- scene.one.init()
    img = Image.new("load.jpg")
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
    mat.x = 50
    mat.y = 50
    mat.width = 100
    mat.height = 100

    bltImg = Image.new("sprites/bullet.png");

    conf = RenderConfig.new(bltImg, mesh, shader);

    game:spawnEntityFull(
        function(other)
            print ("nice hit!")
        end,
        conf,
        [[
            x := x + dt * 10;
            # y += dt * 100;
        ]],
        {},
        50, 50,
        100, 100,
        false
    );
end


function main() -- main(e)


    -- shader:use()
    -- mat:load()
    -- img:bind()
    -- mesh:render()

    -- conf:setup()
    -- mat:load()
    -- conf:render()

end
