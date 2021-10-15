#include "common.h"
#include "bgfx_utils.h"
#include <bx/rng.h>
#include <map>
#include <iostream>
#include "Game.h"


namespace
{


class TDsEngine : public entry::AppI {
public:
    TDsEngine(const char* _name, const char* _description, const char* _url) :
        entry::AppI(_name, _description, _url)
    {}

    void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override {
        Game::instance().initWindow(_argc, _argv, _width, _height);
        Game::instance().load();
    }

    int shutdown() override
    {
        Game::instance().unload();
        Game::instance().close();

        return 0;
    }

	bool update() override
	{
        return Game::instance().loop();
	}
};


} // namespace

ENTRY_IMPLEMENT_MAIN(
    TDsEngine,
    "TDsEngine",
    "Creation of a Doom Like with a ball as weapon",
    "https://github.com/JorisSAN/TDsEngine"
);