
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
    -- require("scenes.manifest")
    -- require("shaders.manifest")
    -- require("sprites.manifest")
    -- require("stages.manifest")
    -- require("stages.enemies.Ghost")

    -- ghost = Image.new("sprites/ghost.png")
    -- bullet = Image.new("sprites/bullet.png")

    -- -- gameBuffer = Framebuffer.new{
    -- --     width = 300,
    -- --     height = 300,
    -- --     channels = 4
    -- -- }

    -- player = {
    --     x = 300,
    --     y = 300,
    --     radius = 25 / 2,
    --     speed = 100,
    --     shotTimer = Timer.new(clock, 0.6),
    --     logic = function(h)
    --         local value = deltaTime * h.speed
    --         local up = window.keyDown("up");
    --         local down = window.keyDown("down");
    --         local left = window.keyDown("left");
    --         local right = window.keyDown("right");
    --         local shoot = window.keyDown("z");
    --         local bomb = window.keyDown("x");
    --         if (down ~= up) and (left ~= right) then
    --             value = value * math.sqrt(2) / 2
    --         end
    --         if window.keyDown("up") then
    --             h.y = h.y - value
    --         end
    --         if window.keyDown("down") then
    --             h.y = h.y + value
    --         end
    --         if window.keyDown("right") then
    --             h.x = h.x + value
    --         end
    --         if window.keyDown("left") then
    --             h.x = h.x - value
    --         end
    --         if window.keyDown("z") and h.shotTimer:done() then
    --             h.shotTimer:reset()
    --             gh.registerEntity{
    --                 x = h.x,
    --                 y = h.y - 30,
    --                 logic = function(h)
    --                     game.regCircleCol(h._id, "playerBullets", h.x, h.y, 10)
    --                     bullet:render{
    --                         x = h.x,
    --                         y = h.y,
    --                         width = 20,
    --                         height = 20,
    --                     }
    --                 end,
    --                 hit = function(h, o)
    --                     gh.removeEntity(h._id)
    --                 end,
    --                 patternSet = Pattern.new{
    --                     0,
    --                     function(h)
    --                         h.y = h.y - deltaTime * 10
    --                     end
    --                 }
    --             }
    --         end
    --         if window.keyDown("x") then
    --             -- h.x = h.x - value
    --         end
    --     end,
    --     render = function(h)
    --         ghost:render{
    --             x = h.x,
    --             y = h.y,
    --             width = ghost:getWidth(),
    --             height = ghost:getHeight(),
    --         }
    --     end
    -- }

    -- testPattern = {
    --     0,
    --     function(h)
    --         h.x = h.x + h.v.x * deltaTime
    --         h.y = h.y + h.v.y * deltaTime
    --     end
    -- }

    -- schedule = Schedular.new{
    --     1, function()
    --         Ghost.new(testPattern, {
    --             x = 40,
    --             y = 40,
    --             v = {x = 5, y = 30},
    --         })
    --         Ghost.new(
    --             {0, function(h, t)
    --                 local m = 100
    --                 h.x = 50 + m * math.cos(t + math.pi) + m
    --                 h.y = 40 + m * math.sin(t + math.pi) + m * t / 4
    --             end,

    --             }
    --         , {
    --             x = 50,
    --             y = 40,
    --             v = {x = -5, y = 30},
    --         })
    --     end,
    -- }

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
end


function main() -- main(e)

    -- print("foo");

    shader:use()
    mat:load()
    img:bind()
    mesh:render()


    -- sprite:use()


    -- clock:advance(deltaTime)

    -- CALLBACK ID, group name, x (center), y (center), radius
    -- testEntity.patternSet:call(testEntity);
    -- testEntity2.patternSet:call(testEntity2);

    -- game.resetGroups()
    -- game.regCircleCol(testEntity._id, "player", testEntity.x, testEntity.y, testEntity.radius)
    -- game.regCircleCol(testEntity2._id, "enemyBullets", testEntity2.x, testEntity2.y, testEntity2.radius)
    -- print("id 1 = " .. testEntity._id)
    -- print("id 2 = " .. testEntity2._id)
    -- game.testCollisions("player", "enemyBullets")

    -- game.resetGroups()
    -- gh.testCollisions()
    -- player:logic()

    -- window.setFramebuffer(gameBuffer)
    -- scene.one.main(e)

    -- gameBuffer:render{
    --     x = 10,
    --     y = 10,
    --     width = 300,
    --     height = 300
    -- }

    -- window.setDefaultFramebuffer()


    -- loadingScreen:render{
    --     x = 40.4234,
    --     y = 90,
    --     width = 300,
    --     height = 300
    -- }

    -- player:render()

    -- schedule:call()

end
