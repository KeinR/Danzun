
-- First thing that runs, before window
-- opens
function preInit()
    window.setTitle("DAnzun test")
    window.setSize(500, 700)
    loadingScreen = Image.new("load.jpg")
end

-- This is looped over as init() is called
function loadMain(deltaTime)
    window.renderToSelf()
    loadingScreen.render{
        x = 40,
        y = 90,
        width = 300,
        height = 300
    }
end

-- Stuff to do asynchronously while loadMain is running
function init()
    require("game.scenes.manifest")
    require("game.shaders.manifest")
    require("game.sprites.manifest")
    require("game.stages.manifest")

    gameBuffer = Framebuffer.new{
        width = 300,
        height = 300,
        channels = 4
    }
end

function start()
    scene.one.init()
end

function main(e)
    window.setFramebuffer(gameBuffer)
    scene.one.main(e)

    gameBuffer:render{
        x = 10,
        y = 10,
        width = 300,
        height = 300
    }

    window.setDefaultFramebuffer()
end
