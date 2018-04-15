#include "simple/support/enum.hpp"
#include "initializer.h"
#include "utils.hpp"

using namespace simple::sdlcore;

using simple::support::to_integer;

initializer::~initializer() noexcept
{
	SDL_QuitSubSystem(to_integer(system));
}

initializer::initializer(system_flag system) : system(system)
{
	utils::throw_error( SDL_InitSubSystem(to_integer(system)) );
}

initializer::initializer(initializer&& other) noexcept : system(other.system)
{
	other.system= system_flag::nothing;
}

initializer & initializer::operator=(initializer&& other) noexcept
{
	system = other.system;
	other.system = system_flag::nothing;
	return *this;
}

