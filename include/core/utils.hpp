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
 * \brief Applies a function to a shared pointer target and returns the same pointer.
 *
 * \tparam T The type of the object managed by the shared pointer.
 * \tparam F The type of the callable (e.g., lambda or function) that accepts a reference to T.
 * \param ptr A shared pointer to the object to be modified.
 * \param fn A function or lambda that takes a reference to T and performs modifications.
 * \return The same shared pointer passed in, after applying the modification.
 *
 * \note This does not create a copy. It directly modifies the pointed-to object.
 *
 * \code
 * auto layout = std::make_shared<Flex>(
 *     FlexDirection::Row,
 *     chain(std::make_shared<List>(title_1, title_2), [](List& l) { l.set_gap(2); }),
 *     chain(std::make_shared<List>(input_1, input_2), [](List& l) { l.set_gap(2); })
 * );
 * \endcode
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
