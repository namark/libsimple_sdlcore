#include "simple/support/enum.hpp"
#include "initializer.h"
#include "utils.hpp"

using namespace simple::sdlcore;

using simple::support::to_integer;

bool initializer::exists(system_flag system) noexcept
{
	auto sdl_system = to_integer(system);
	return SDL_WasInit(sdl_system) == sdl_system;
}

initializer::~initializer() noexcept
{
	SDL_QuitSubSystem(to_integer(system));
	if(exists(system_flag::nothing))
		SDL_Quit();
}

initializer::initializer(system_flag system) : system(system)
{
	utils::throw_error( SDL_InitSubSystem(to_integer(system)) );
}

initializer::initializer(initializer&& other) noexcept : system(other.system)
{
	other.system = system_flag::nothing;
}

initializer & initializer::operator=(initializer&& other) noexcept
{
	system = other.system;
	other.system = system_flag::nothing;
	return *this;
}

