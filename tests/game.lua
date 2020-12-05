
-- First thing that runs, before window
-- opens
function preInit()
    window.setTitle("DAnzun test")
    window.setSize(500, 700)
    loadingScreen = Image.new("load.jpg")
end

-- This is looped over as init() is called
function loadMain(deltaTime)
    
end

-- Stuff to do asynchronously while loadMain is running
function init()
    require("scenes.manifest")
    require("shaders.manifest")
    require("sprites.manifest")
    require("stages.manifest")

    ghost = Image.new("sprites/ghost.png")

    -- gameBuffer = Framebuffer.new{
    --     width = 300,
    --     height = 300,
    --     channels = 4
    -- }
    testEntity = {
        x = 0,
        y = 0,
        v = {x = 10, y = 10},
        radius = 25 / 2,
        logic = function(h)
            ghost:render{
                x = h.x,
                y = h.y,
                width = ghost:getWidth(),
                height = ghost:getHeight(),
            }
        end,
        hit = function(h)
            print("Have hit!!")
        end,
        patternSet = Pattern.new{
            0,
            function(h)
                h.x = h.x + h.v.x * deltaTime
                h.y = h.y + h.v.y * deltaTime
            end
        }
    }

    testEntity2 = {
        x = 150,
        y = 150,
        v = {x = -10, y = -10},
        radius = 25 / 2,
        logic = function(h)
            ghost:render{
                x = h.x,
                y = h.y,
                width = ghost:getWidth(),
                height = ghost:getHeight(),
            }
        end,
        hit = function(h)
            print("Have hit!!")
        end,
        patternSet = Pattern.new{
            0,
            function(h)
                h.x = h.x + h.v.x * deltaTime
                h.y = h.y + h.v.y * deltaTime
            end
        }
    }

end

function start()
    -- scene.one.init()
    gh.registerEntity(testEntity);
    gh.registerEntity(testEntity2);
end

function main() -- main(e)


    -- CALLBACK ID, group name, x (center), y (center), radius
    testEntity.patternSet:call(testEntity);
    testEntity2.patternSet:call(testEntity2);
    game.resetGroups()
    game.regCircleCol(testEntity._id, "player", testEntity.x, testEntity.y, testEntity.radius)
    game.regCircleCol(testEntity2._id, "enemyBullets", testEntity2.x, testEntity2.y, testEntity2.radius)
    -- print("id 1 = " .. testEntity._id)
    -- print("id 2 = " .. testEntity2._id)
    game.testCollisions("player", "enemyBullets")

    -- window.setFramebuffer(gameBuffer)
    -- scene.one.main(e)

    -- gameBuffer:render{
    --     x = 10,
    --     y = 10,
    --     width = 300,
    --     height = 300
    -- }

    -- window.setDefaultFramebuffer()

    sprite:use()

    loadingScreen:render{
        x = 40.4234,
        y = 90,
        width = 300,
        height = 300
    }

    testEntity2:logic()
    testEntity:logic()
end
