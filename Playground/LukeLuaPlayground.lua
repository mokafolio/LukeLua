local ws = WindowSettings()
ws:setResizeable(true)

local window = Window()

-- window:addMouseMoveCallback(function(_e)
--     print("MouseMove", _e:x(), _e:y())
-- end)

window:addMouseDownCallback(function(_e)
    print("MouseDown", _e:x(), _e:y())
    if _e:button() == MouseButton.Left then
        print("LEEEEFT")
    end
end)

window:addMouseUpCallback(function(_e)
    print("MouseUp", _e:x(), _e:y())
end)

window:addKeyDownCallback(function(_e)
    print("KeyDown", _e:key())
    if _e:key() == KeyCode.A then
        print("ITS AN A BABY")
    end
end)

window:addKeyDownCallback(function(_e)
    print("KeyUp", _e:key())
end)

window:addWindowMoveCallback(function(_e)
    print("Window Moved", _e:x(), _e:y())
end)

window:addWindowResizeCallback(function(_e)
    print("Window Resized", _e:width(), _e:height())
end)

window:addWindowIconifyCallback(function(_e)
    print("Window Iconified")
end)

window:addWindowRestoreCallback(function(_e)
    print("Window Restored")
end)

window:addWindowFocusCallback(function(_e)
    print("Window Focussed")
end)

window:addWindowLostFocusCallback(function(_e)
    print("Window Lost Focus")
end)

local err = window:open(ws)
if err then
    print("Error: ", err.message)
else
    while not window:shouldClose() do

        pollEvents()
    end
end