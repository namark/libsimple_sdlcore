#ifndef SIMPLE_SDLCORE_INITIALIZER_H
#define SIMPLE_SDLCORE_INITIALIZER_H
#include <SDL2/SDL.h>
#include "simple/support/enum_flags_operators.hpp"

namespace simple::sdlcore
{

	enum class system_flag : uint32_t
	{
		nothing = 0,
		video = SDL_INIT_VIDEO,
		audio = SDL_INIT_AUDIO,
		input = SDL_INIT_EVENTS,
		haptic = SDL_INIT_HAPTIC,
		joystick = SDL_INIT_JOYSTICK,
		game_controller = SDL_INIT_GAMECONTROLLER,
		everything = SDL_INIT_EVERYTHING,
	};

	using ::operator|;
	using ::operator&;
	using ::operator^;
	using ::operator&&;

	// NOTE: wanted to use unique_ptr here, but couldn't find an easy way
	class initializer
	{
		public:
		initializer(system_flag = system_flag::everything);
		virtual ~initializer() noexcept;

		initializer(const initializer& other) = delete;
		initializer & operator=(const initializer& other) = delete;
		initializer(initializer&& other) noexcept;
		initializer & operator=(initializer&& other) noexcept;

		private:

		system_flag system;

	};

} // namespace simple::sdlcore

namespace simple::support
{
	template <>
	struct define_enum_flags_operators<simple::sdlcore::system_flag> : public std::true_type {};
} // namespace simple::support

#endif /* end of include guard */
