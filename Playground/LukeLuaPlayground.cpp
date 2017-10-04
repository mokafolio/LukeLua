#include <Stick/Error.hpp>
#include <LukeLua/LukeLua.hpp>
#include <Stick/FileUtilities.hpp>

using namespace stick;

int main(int _argc, const char * _args[])
{
    lua_State * state = luanatic::createLuaState();
    STICK_ASSERT(luanatic::HasValueTypeConverter<stick::Error>::value);
    printf("DA ER NAME %s\n", typeid(nullptr).name());
    {
        luanatic::initialize(state);
        luanatic::openStandardLibraries(state);
        lukeLua::registerLuke(state);
        printf("POST REGISTER\n");
        luanatic::addPackagePath(state, "../../Playground/?.lua");
    }
    auto script = loadTextFile("../../Playground/LukeLuaPlayground.lua").ensure();
    auto error = luanatic::execute(state, script);
    if (error)
    {
        printf("%s\n", error.message().cString());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
