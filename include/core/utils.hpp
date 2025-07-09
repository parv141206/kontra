/*****************************************************************//**
 * \file   utils.hpp
 * \brief  Normal utility functions! Enjoy!
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <memory>
#include <functional>

/**
 * @brief Applies a function to a `shared_ptr` target and returns the same pointer.
 * 
 * This utility is useful for inline configuration of shared components, allowing
 * you to mutate the object in a chained expression — perfect for layout trees.
 * 
 * @tparam T The type managed by the shared pointer.
 * @tparam F The callable type (e.g., lambda or function) that takes a reference to `T`.
 * 
 * @param ptr A `std::shared_ptr<T>` to the object you want to modify.
 * @param fn A function or lambda that takes a `T&` and performs changes directly.
 * @return The same `shared_ptr<T>` passed in, after applying the modification.
 * 
 * @note This does **not** create a copy. It directly modifies the pointed-to object.
 * 
 * ### Example
 * ```cpp
 * auto layout = std::make_shared<Flex>(
 *     FlexDirection::Row,
 * 
 *     chain(
 *         std::make_shared<List>(title_1, title_2),
 *         [](List& l) { l.set_gap(2); }
 *     ),
 * 
 *     chain(
 *         std::make_shared<List>(input_1, input_2),
 *         [](List& l) { l.set_gap(2); }
 *     )
 * );
 * ```
 */
template <typename T, typename F>
std::shared_ptr<T> chain(std::shared_ptr<T> ptr, F&& fn) {
    fn(*ptr);
    return ptr;
}

inline std::string repeat(const char* ch, int count) {
	std::string result;
	result.reserve(count * 3); 
	for (int i = 0; i < count; ++i) result += ch;
	return result;
}
