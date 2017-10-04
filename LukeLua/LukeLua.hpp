#include <Stick/Path.hpp>
#include <Luanatic/Luanatic.hpp>
#include <Luke/Luke.hpp>

namespace lukeLua
{
    STICK_API inline void registerLuke(lua_State * _state, const stick::String & _namespace = "");

    namespace detail
    {
        inline stick::Int32 luaWindowOpen(lua_State * _state)
        {
            luke::Window * w = luanatic::convertToTypeAndCheck<luke::Window>(_state, 1);
            luke::WindowSettings * ws = luanatic::convertToTypeAndCheck<luke::WindowSettings>(_state, 2);
            luke::Window * shared = luanatic::convertToType<luke::Window>(_state, 3);
            luanatic::pushValueType<stick::Error>(_state, w->open(*ws, shared));
            return 1;
        }

        template<class EventT>
        inline stick::Int32 luaEventCallback(lua_State * _state)
        {
            luke::Window * w = luanatic::convertToTypeAndCheck<luke::Window>(_state, 1);

            if (!lua_isfunction(_state, 2))
                luanatic::detail::luaErrorWithStackTrace(_state, 2, "Function expected");

            luanatic::LuaValue luaCallback(_state, 2);
            w->addEventCallback([luaCallback, _state](const EventT & _e)
            {
                printf("CALLED IT BRO\n");
                //01. push callback function
                luaCallback.push();
                //02. push event
                luanatic::push<EventT>(_state, &_e);
                // //03. push entity
                // luanatic::push<brick::Entity>(_state, &_self);
                //04. call function
                lua_call(_state, 1, 0);
            });

            return 0;
        }
    }

    inline void registerLuke(lua_State * _state, const stick::String & _namespace)
    {
        using namespace luanatic;
        using namespace luke;
        using namespace stick;

        LuaValue g = globalsTable(_state);
        LuaValue namespaceTable = g;
        if (!_namespace.isEmpty())
        {
            auto tokens = path::segments(_namespace, '.');
            for (const String & token : tokens)
            {
                LuaValue table = namespaceTable.findOrCreateTable(token);
                namespaceTable = table;
            }
        }

        //register Keys
        LuaValue keyCodeTable = namespaceTable.findOrCreateTable("KeyCode");
        keyCodeTable["Unknown"].set(KeyCode::Unknown);
        keyCodeTable["A"].set(KeyCode::A);
        keyCodeTable["B"].set(KeyCode::B);
        keyCodeTable["C"].set(KeyCode::C);
        keyCodeTable["D"].set(KeyCode::D);
        keyCodeTable["E"].set(KeyCode::E);
        keyCodeTable["F"].set(KeyCode::F);
        keyCodeTable["G"].set(KeyCode::G);
        keyCodeTable["H"].set(KeyCode::H);
        keyCodeTable["I"].set(KeyCode::I);
        keyCodeTable["J"].set(KeyCode::J);
        keyCodeTable["K"].set(KeyCode::K);
        keyCodeTable["L"].set(KeyCode::L);
        keyCodeTable["M"].set(KeyCode::M);
        keyCodeTable["N"].set(KeyCode::N);
        keyCodeTable["O"].set(KeyCode::O);
        keyCodeTable["P"].set(KeyCode::P);
        keyCodeTable["Q"].set(KeyCode::Q);
        keyCodeTable["R"].set(KeyCode::R);
        keyCodeTable["S"].set(KeyCode::S);
        keyCodeTable["T"].set(KeyCode::T);
        keyCodeTable["U"].set(KeyCode::U);
        keyCodeTable["V"].set(KeyCode::V);
        keyCodeTable["W"].set(KeyCode::W);
        keyCodeTable["X"].set(KeyCode::X);
        keyCodeTable["Y"].set(KeyCode::Y);
        keyCodeTable["Z"].set(KeyCode::Z);
        keyCodeTable["One"].set(KeyCode::One);
        keyCodeTable["Two"].set(KeyCode::Two);
        keyCodeTable["Three"].set(KeyCode::Three);
        keyCodeTable["Four"].set(KeyCode::Four);
        keyCodeTable["Five"].set(KeyCode::Five);
        keyCodeTable["Six"].set(KeyCode::Six);
        keyCodeTable["Seven"].set(KeyCode::Seven);
        keyCodeTable["Eight"].set(KeyCode::Eight);
        keyCodeTable["Nine"].set(KeyCode::Nine);
        keyCodeTable["Return"].set(KeyCode::Return);
        keyCodeTable["Escape"].set(KeyCode::Escape);
        keyCodeTable["Delete"].set(KeyCode::Delete);
        keyCodeTable["Tab"].set(KeyCode::Tab);
        keyCodeTable["Space"].set(KeyCode::Space);
        keyCodeTable["Subtract"].set(KeyCode::Subtract);
        keyCodeTable["Equal"].set(KeyCode::Equal);
        keyCodeTable["LeftBracket"].set(KeyCode::LeftBracket);
        keyCodeTable["RightBracket"].set(KeyCode::RightBracket);
        keyCodeTable["Backslash"].set(KeyCode::Backslash);
        keyCodeTable["WorldOne"].set(KeyCode::WorldOne);
        keyCodeTable["Semicolon"].set(KeyCode::Semicolon);
        keyCodeTable["Apostrophe"].set(KeyCode::Apostrophe);
        keyCodeTable["GraveAccent"].set(KeyCode::GraveAccent);
        keyCodeTable["Comma"].set(KeyCode::Comma);
        keyCodeTable["Period"].set(KeyCode::Period);
        keyCodeTable["Slash"].set(KeyCode::Slash);
        keyCodeTable["CapsLock"].set(KeyCode::CapsLock);
        keyCodeTable["F1"].set(KeyCode::F1);
        keyCodeTable["F2"].set(KeyCode::F2);
        keyCodeTable["F3"].set(KeyCode::F3);
        keyCodeTable["F4"].set(KeyCode::F4);
        keyCodeTable["F5"].set(KeyCode::F5);
        keyCodeTable["F6"].set(KeyCode::F6);
        keyCodeTable["F7"].set(KeyCode::F7);
        keyCodeTable["F8"].set(KeyCode::F8);
        keyCodeTable["F9"].set(KeyCode::F9);
        keyCodeTable["F10"].set(KeyCode::F10);
        keyCodeTable["F11"].set(KeyCode::F11);
        keyCodeTable["F12"].set(KeyCode::F12);
        keyCodeTable["F13"].set(KeyCode::F13);
        keyCodeTable["F14"].set(KeyCode::F14);
        keyCodeTable["F15"].set(KeyCode::F15);
        keyCodeTable["F16"].set(KeyCode::F16);
        keyCodeTable["Caret"].set(KeyCode::Caret);
        keyCodeTable["LeftControl"].set(KeyCode::LeftControl);
        keyCodeTable["LeftShift"].set(KeyCode::LeftShift);
        keyCodeTable["LeftAlt"].set(KeyCode::LeftAlt);
        keyCodeTable["LeftCommand"].set(KeyCode::LeftCommand);
        keyCodeTable["RightControl"].set(KeyCode::RightControl);
        keyCodeTable["RightShift"].set(KeyCode::RightShift);
        keyCodeTable["RightAlt"].set(KeyCode::RightAlt);
        keyCodeTable["RightCommand"].set(KeyCode::RightCommand);
        keyCodeTable["Right"].set(KeyCode::Right);
        keyCodeTable["Left"].set(KeyCode::Left);
        keyCodeTable["Down"].set(KeyCode::Down);
        keyCodeTable["Up"].set(KeyCode::Up);
        keyCodeTable["Help"].set(KeyCode::Help);
        keyCodeTable["ForwardDelete"].set(KeyCode::ForwardDelete);
        keyCodeTable["Mute"].set(KeyCode::Mute);
        keyCodeTable["VolumeUp"].set(KeyCode::VolumeUp);
        keyCodeTable["VolumeDown"].set(KeyCode::VolumeDown);
        keyCodeTable["KPDivide"].set(KeyCode::KPDivide);
        keyCodeTable["KPMultiply"].set(KeyCode::KPMultiply);
        keyCodeTable["KPSubtract"].set(KeyCode::KPSubtract);
        keyCodeTable["KPAdd"].set(KeyCode::KPAdd);
        keyCodeTable["KPReturn"].set(KeyCode::KPReturn);
        keyCodeTable["KPOne"].set(KeyCode::KPOne);
        keyCodeTable["KPTwo"].set(KeyCode::KPTwo);
        keyCodeTable["KPThree"].set(KeyCode::KPThree);
        keyCodeTable["KPFour"].set(KeyCode::KPFour);
        keyCodeTable["KPFive"].set(KeyCode::KPFive);
        keyCodeTable["KPSix"].set(KeyCode::KPSix);
        keyCodeTable["KPSeven"].set(KeyCode::KPSeven);
        keyCodeTable["KPEight"].set(KeyCode::KPEight);
        keyCodeTable["KPNine"].set(KeyCode::KPNine);
        keyCodeTable["KPZero"].set(KeyCode::KPZero);
        keyCodeTable["KPDecimal"].set(KeyCode::KPDecimal);
        keyCodeTable["KPEqual"].set(KeyCode::KPEqual);
        keyCodeTable["KPComma"].set(KeyCode::KPComma);

        //register key events
        ClassWrapper<Event> eventCW("Event");
        eventCW.
        addMemberFunction("name", LUANATIC_FUNCTION(&Event::name)).
        addMemberFunction("eventTypeID", LUANATIC_FUNCTION(&Event::eventTypeID)).
        addMemberFunction("stopPropagation", LUANATIC_FUNCTION(&Event::stopPropagation)).
        addMemberFunction("propagationStopped", LUANATIC_FUNCTION(&Event::propagationStopped));
        namespaceTable.registerClass(eventCW);

        ClassWrapper<KeyEvent> keyEventCW("KeyEvent");
        keyEventCW.
        addMemberFunction("key", LUANATIC_FUNCTION(&KeyEvent::key)).
        addMemberFunction("scancode", LUANATIC_FUNCTION(&KeyEvent::scancode));
        namespaceTable.registerClass(keyEventCW);

        ClassWrapper<KeyDownEvent> keyDownEventCW("KeyDownEvent");
        keyDownEventCW.
        addBase<KeyEvent>().
        addBase<Event>().
        addMemberFunction("isRepeat", LUANATIC_FUNCTION(&KeyDownEvent::isRepeat));
        namespaceTable.registerClass(keyDownEventCW);

        ClassWrapper<KeyUpEvent> keyUpEventCW("KeyUpEvent");
        keyUpEventCW.
        addBase<KeyEvent>().
        addBase<Event>();
        namespaceTable.registerClass(keyUpEventCW);

        //register mouse buttons
        LuaValue mouseButtonTable = namespaceTable.findOrCreateTable("MouseButton");
        mouseButtonTable["Left"].set(MouseButton::Left);
        mouseButtonTable["Right"].set(MouseButton::Right);
        mouseButtonTable["Middle"].set(MouseButton::Middle);
        mouseButtonTable["Button3"].set(MouseButton::Button3);
        mouseButtonTable["Button4"].set(MouseButton::Button4);
        mouseButtonTable["Button5"].set(MouseButton::Button5);
        mouseButtonTable["Button6"].set(MouseButton::Button6);
        mouseButtonTable["Button7"].set(MouseButton::Button7);
        mouseButtonTable["None"].set(MouseButton::None);

        //register MouseState
        ClassWrapper<MouseState> mouseStateCW("MouseState");
        mouseStateCW.
        addMemberFunction("x", LUANATIC_FUNCTION(&MouseState::x)).
        addMemberFunction("y", LUANATIC_FUNCTION(&MouseState::y)).
        addMemberFunction("isButtonDown", LUANATIC_FUNCTION(&MouseState::isButtonDown)).
        addMemberFunction("buttonBitMask", LUANATIC_FUNCTION(&MouseState::buttonBitMask));
        namespaceTable.registerClass(mouseStateCW);

        //register mouse events
        ClassWrapper<MouseEvent> mouseEventCW("MouseEvent");
        mouseEventCW.
        addMemberFunction("x", LUANATIC_FUNCTION(&MouseEvent::x)).
        addMemberFunction("y", LUANATIC_FUNCTION(&MouseEvent::y)).
        addMemberFunction("button", LUANATIC_FUNCTION(&MouseEvent::button)).
        addMemberFunction("mouseState", LUANATIC_FUNCTION(&MouseEvent::mouseState));
        namespaceTable.registerClass(mouseEventCW);

        ClassWrapper<MouseScrollEvent> mouseScrollEventCW("MouseScrollEvent");
        mouseScrollEventCW.
        addBase<Event>().
        addBase<MouseEvent>().
        addMemberFunction("scrollX", LUANATIC_FUNCTION(&MouseScrollEvent::scrollX)).
        addMemberFunction("scrollY", LUANATIC_FUNCTION(&MouseScrollEvent::scrollY));
        namespaceTable.registerClass(mouseScrollEventCW);

        ClassWrapper<MouseMoveEvent> mouseMoveEventCW("MouseMoveEvent");
        mouseMoveEventCW.
        addBase<Event>().
        addBase<MouseEvent>();
        namespaceTable.registerClass(mouseMoveEventCW);

        ClassWrapper<MouseDragEvent> mouseDragEventCW("MouseDragEvent");
        mouseDragEventCW.
        addBase<Event>().
        addBase<MouseEvent>();
        namespaceTable.registerClass(mouseDragEventCW);

        ClassWrapper<MouseDownEvent> mouseDownEventCW("MouseDownEvent");
        mouseDownEventCW.
        addBase<Event>().
        addBase<MouseEvent>();
        namespaceTable.registerClass(mouseDownEventCW);

        ClassWrapper<MouseUpEvent> mouseUpEventCW("MouseUpEvent");
        mouseUpEventCW.
        addBase<Event>().
        addBase<MouseEvent>();
        namespaceTable.registerClass(mouseUpEventCW);

        //register DisplayMode
        ClassWrapper<DisplayMode> displayModeCW("DisplayMode");
        displayModeCW.
        addMemberFunction("width", LUANATIC_FUNCTION(&DisplayMode::width)).
        addMemberFunction("height", LUANATIC_FUNCTION(&DisplayMode::height)).
        addMemberFunction("redBits", LUANATIC_FUNCTION(&DisplayMode::redBits)).
        addMemberFunction("greenBits", LUANATIC_FUNCTION(&DisplayMode::greenBits)).
        addMemberFunction("blueBits", LUANATIC_FUNCTION(&DisplayMode::blueBits)).
        addMemberFunction("refreshRate", LUANATIC_FUNCTION(&DisplayMode::refreshRate));
        namespaceTable.registerClass(displayModeCW);

        //register Display
        ClassWrapper<Display> displayCW("Display");
        displayCW.
        addMemberFunction("setDisplayMode", LUANATIC_FUNCTION(&Display::setDisplayMode)).
        addMemberFunction("currentDisplayMode", LUANATIC_FUNCTION(&Display::currentDisplayMode)).
        addMemberFunction("findBestDisplayMode", LUANATIC_FUNCTION(&Display::findBestDisplayMode)).
        addMemberFunction("displayModes", LUANATIC_FUNCTION(&Display::displayModes)).
        addMemberFunction("isValidDisplayMode", LUANATIC_FUNCTION(&Display::isValidDisplayMode)).
        addMemberFunction("isValid", LUANATIC_FUNCTION(&Display::isValid)).
        addMemberFunction("x", LUANATIC_FUNCTION(&Display::x)).
        addMemberFunction("y", LUANATIC_FUNCTION(&Display::y)).
        addStaticFunction("mainDisplay", LUANATIC_FUNCTION(&Display::mainDisplay)).
        addStaticFunction("displays", LUANATIC_FUNCTION(&Display::displays));
        namespaceTable.registerClass(displayCW);

        //register WindowSettings
        ClassWrapper<WindowSettings> windowSettingsCW("WindowSettings");
        windowSettingsCW.
        addConstructor<>().
        addConstructor("new").
        addMemberFunction("setResizeable", LUANATIC_FUNCTION(&WindowSettings::setResizeable)).
        addMemberFunction("setDecorated", LUANATIC_FUNCTION(&WindowSettings::setDecorated)).
        addMemberFunction("setTitle", LUANATIC_FUNCTION(&WindowSettings::setTitle)).
        addMemberFunction("setPosition", LUANATIC_FUNCTION(&WindowSettings::setPosition)).
        addMemberFunction("setSize", LUANATIC_FUNCTION(&WindowSettings::setSize)).
        addMemberFunction("setDisplay", LUANATIC_FUNCTION(&WindowSettings::setDisplay)).
        addMemberFunction("setSampleCount", LUANATIC_FUNCTION(&WindowSettings::setSampleCount)).
        addMemberFunction("setColorPrecision", LUANATIC_FUNCTION(&WindowSettings::setColorPrecision)).
        addMemberFunction("setAlphaPrecision", LUANATIC_FUNCTION(&WindowSettings::setAlphaPrecision)).
        addMemberFunction("setDepthPrecision", LUANATIC_FUNCTION(&WindowSettings::setDepthPrecision)).
        addMemberFunction("setStencilPrecision", LUANATIC_FUNCTION(&WindowSettings::setStencilPrecision)).
        addMemberFunction("setDepthPrecision", LUANATIC_FUNCTION(&WindowSettings::setDepthPrecision)).
        addMemberFunction("isResizeable", LUANATIC_FUNCTION(&WindowSettings::isResizeable)).
        addMemberFunction("isDecorated", LUANATIC_FUNCTION(&WindowSettings::isDecorated)).
        addMemberFunction("display", LUANATIC_FUNCTION(&WindowSettings::display)).
        addMemberFunction("title", LUANATIC_FUNCTION(&WindowSettings::title)).
        addMemberFunction("x", LUANATIC_FUNCTION(&WindowSettings::x)).
        addMemberFunction("y", LUANATIC_FUNCTION(&WindowSettings::y)).
        addMemberFunction("width", LUANATIC_FUNCTION(&WindowSettings::width)).
        addMemberFunction("height", LUANATIC_FUNCTION(&WindowSettings::height)).
        addMemberFunction("sampleCount", LUANATIC_FUNCTION(&WindowSettings::sampleCount)).
        addMemberFunction("colorPrecision", LUANATIC_FUNCTION(&WindowSettings::colorPrecision)).
        addMemberFunction("alphaPrecision", LUANATIC_FUNCTION(&WindowSettings::alphaPrecision)).
        addMemberFunction("depthPrecision", LUANATIC_FUNCTION(&WindowSettings::depthPrecision)).
        addMemberFunction("stencilPrecision", LUANATIC_FUNCTION(&WindowSettings::stencilPrecision));
        namespaceTable.registerClass(windowSettingsCW);

        //register Window
        ClassWrapper<Window> windowCW("Window");
        windowCW.
        addConstructor<>().
        addConstructor("new").
        addMemberFunction("open", detail::luaWindowOpen).
        addMemberFunction("close", LUANATIC_FUNCTION(&Window::close)).
        addMemberFunction("move", LUANATIC_FUNCTION(&Window::move)).
        addMemberFunction("moveToCenter", LUANATIC_FUNCTION(&Window::moveToCenter)).
        addMemberFunction("show", LUANATIC_FUNCTION(&Window::show)).
        addMemberFunction("hide", LUANATIC_FUNCTION(&Window::hide)).
        addMemberFunction("resize", LUANATIC_FUNCTION(&Window::resize)).
        addMemberFunction("maximize", LUANATIC_FUNCTION(&Window::maximize)).
        addMemberFunction("focus", LUANATIC_FUNCTION(&Window::focus)).
        addMemberFunction("enableRenderContext", LUANATIC_FUNCTION(&Window::enableRenderContext)).
        addMemberFunction("disableRenderContext", LUANATIC_FUNCTION(&Window::disableRenderContext)).
        addMemberFunction("enterFullscreen", LUANATIC_FUNCTION_OVERLOAD(Error(Window::*)(const Display &), &Window::enterFullscreen)).
        addMemberFunction("enterFullscreen", LUANATIC_FUNCTION_OVERLOAD(Error(Window::*)(const DisplayMode &, const Display &), &Window::enterFullscreen)).
        addMemberFunction("enterFullscreen", LUANATIC_FUNCTION_OVERLOAD(Error(Window::*)(Float32, Float32, const Display &), &Window::enterFullscreen)).
        addMemberFunction("exitFullscreen", LUANATIC_FUNCTION(&Window::exitFullscreen)).
        addMemberFunction("setVerticalSync", LUANATIC_FUNCTION(&Window::setVerticalSync)).
        addMemberFunction("hideCursor", LUANATIC_FUNCTION(&Window::hideCursor)).
        addMemberFunction("showCursor", LUANATIC_FUNCTION(&Window::showCursor)).
        addMemberFunction("setTitle", LUANATIC_FUNCTION(&Window::setTitle)).
        addMemberFunction("swapBuffers", LUANATIC_FUNCTION(&Window::swapBuffers)).
        addMemberFunction("shouldClose", LUANATIC_FUNCTION(&Window::shouldClose)).
        addMemberFunction("isVisible", LUANATIC_FUNCTION(&Window::isVisible)).
        addMemberFunction("isFocussed", LUANATIC_FUNCTION(&Window::isFocussed)).
        addMemberFunction("isFullscreen", LUANATIC_FUNCTION(&Window::isFullscreen)).
        addMemberFunction("settings", LUANATIC_FUNCTION(&Window::settings)).
        addMemberFunction("isCursorVisible", LUANATIC_FUNCTION(&Window::isCursorVisible)).
        addMemberFunction("verticalSync", LUANATIC_FUNCTION(&Window::verticalSync)).
        addMemberFunction("title", LUANATIC_FUNCTION(&Window::title)).
        addMemberFunction("display", LUANATIC_FUNCTION(&Window::display)).
        addMemberFunction("backingScaleFactor", LUANATIC_FUNCTION(&Window::backingScaleFactor)).
        addMemberFunction("width", LUANATIC_FUNCTION(&Window::width)).
        addMemberFunction("height", LUANATIC_FUNCTION(&Window::height)).
        addMemberFunction("widthInPixels", LUANATIC_FUNCTION(&Window::widthInPixels)).
        addMemberFunction("heightInPixels", LUANATIC_FUNCTION(&Window::heightInPixels)).
        addMemberFunction("x", LUANATIC_FUNCTION(&Window::x)).
        addMemberFunction("y", LUANATIC_FUNCTION(&Window::y)).
        addMemberFunction("addMouseMoveCallback", detail::luaEventCallback<MouseMoveEvent>).
        addMemberFunction("addMouseUpCallback", detail::luaEventCallback<MouseUpEvent>).
        addMemberFunction("addMouseDownCallback", detail::luaEventCallback<MouseDownEvent>).
        addMemberFunction("addMouseDragCallback", detail::luaEventCallback<MouseDragEvent>).
        addMemberFunction("addKeyDownCallback", detail::luaEventCallback<KeyDownEvent>).
        addMemberFunction("addKeyUpCallback", detail::luaEventCallback<KeyUpEvent>).
        addMemberFunction("addWindowMoveCallback", detail::luaEventCallback<WindowMoveEvent>).
        addMemberFunction("addWindowResizeCallback", detail::luaEventCallback<WindowResizeEvent>).
        addMemberFunction("addWindowFocusCallback", detail::luaEventCallback<WindowFocusEvent>).
        addMemberFunction("addWindowLostFocusCallback", detail::luaEventCallback<WindowLostFocusEvent>).
        addMemberFunction("addWindowIconifyCallback", detail::luaEventCallback<WindowIconifyEvent>).
        addMemberFunction("addWindowRestoreCallback", detail::luaEventCallback<WindowRestoreEvent>);
        namespaceTable.registerClass(windowCW);

        //register Window settings
        ClassWrapper<WindowMoveEvent> windowMoveEventCW("WindowMoveEvent");
        windowMoveEventCW.
        addBase<Event>().
        addMemberFunction("x", LUANATIC_FUNCTION(&WindowMoveEvent::x)).
        addMemberFunction("y", LUANATIC_FUNCTION(&WindowMoveEvent::y));
        namespaceTable.registerClass(windowMoveEventCW);

        ClassWrapper<WindowResizeEvent> windowResizeEventCW("WindowResizeEvent");
        windowResizeEventCW.
        addBase<Event>().
        addMemberFunction("width", LUANATIC_FUNCTION(&WindowResizeEvent::width)).
        addMemberFunction("height", LUANATIC_FUNCTION(&WindowResizeEvent::height));
        namespaceTable.registerClass(windowResizeEventCW);

        ClassWrapper<WindowFocusEvent> windowFocusEventCW("WindowFocusEvent");
        windowFocusEventCW.
        addBase<Event>();
        namespaceTable.registerClass(windowFocusEventCW);

        ClassWrapper<WindowLostFocusEvent> windowLostFocusEventCW("WindowLostFocusEvent");
        windowLostFocusEventCW.
        addBase<Event>();
        namespaceTable.registerClass(windowLostFocusEventCW);

        ClassWrapper<WindowIconifyEvent> windowIconifyEventCW("WindowIconifyEvent");
        windowIconifyEventCW.
        addBase<Event>();
        namespaceTable.registerClass(windowIconifyEventCW);

        ClassWrapper<WindowRestoreEvent> windowRestoreEventCW("WindowRestoreEvent");
        windowRestoreEventCW.
        addBase<Event>();
        namespaceTable.registerClass(windowRestoreEventCW);

        namespaceTable.registerFunction("pollEvents", LUANATIC_FUNCTION(&pollEvents));
    }
}
