#ifndef SIMPLE_SDLCORE_UTILS_HPP
#define SIMPLE_SDLCORE_UTILS_HPP

#include <stdexcept>
#include <string>
#include <memory>
#include <utility>
#include <cassert>
#include <SDL2/SDL.h>

#include "simple/support/range.hpp"
#include "simple/geom/vector.hpp"

namespace simple::sdlcore::utils
{

	template <typename Type>
	inline bool check_error(Type&& pointer)
	{
		return (nullptr == pointer);
	}

	inline bool check_error(int error_code)
	{
		return 0 != error_code;
	}

	inline bool check_error(bool error)
	{
		return error;
	}

	template <typename Type>
	inline void throw_error(Type&& error)
	{
		using namespace std::literals;
		if ( check_error(std::forward<Type>(error)) )
			throw std::runtime_error("SDL_ERROR: "s + SDL_GetError());
	}

	template <typename SDL_Object, typename DeleterType = void(*)(SDL_Object*)>
	class object_wrapper
	{

		public:
		bool operator==(const object_wrapper& other) const noexcept { return _guts == other._guts; }
		bool operator!=(const object_wrapper& other) const noexcept { return !(*this == other); }


		protected:
		using Deleter = DeleterType;
		using object_ptr = std::unique_ptr<SDL_Object, Deleter>;
		using pointer = typename object_ptr::pointer;

		private:
		object_ptr _guts;

		protected:

		object_wrapper(pointer guts)
			: _guts(guts)
		{
			throw_error(_guts.get());
		}

		object_wrapper(pointer guts, Deleter deleter)
			: _guts(guts, deleter)
		{
			throw_error(_guts.get());
		}

		const object_ptr& guts() const
		{
			assert((nullptr != _guts) && "simple::sdlcore::object_wrapper must not be null");
			return _guts;
		}

		friend std::hash<object_wrapper>;

	};

	template <typename Rect>
	using rect_range_t = support::range<geom::vector<decltype(std::declval<Rect>().x), 2>>;

	template <typename Rect>
	inline Rect to_rect(const rect_range_t<Rect>& r) noexcept
	{
		Rect rect;
		rect.x = r.lower().x();
		rect.y = r.lower().y();
		auto size = r.upper() - r.lower();
		rect.w = size.x();
		rect.h = size.y();
		return rect;
	}

} // namespace simple::sdlcore::utils

namespace std
{
	template <typename T>
	struct hash<simple::sdlcore::utils::object_wrapper<T>>
	{
		std::size_t operator()(const simple::sdlcore::utils::object_wrapper<T>& object) const
		{
			using std::hash;
			return hash(object._guts);
		}
	};

} // namespace std
#endif /* end of include guard */
