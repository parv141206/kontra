/*****************************************************************//**
 * \file   screen.hpp
 * \brief  All components are rendered on a screen.
 * The screen simply calls the render function of each component recursively.
 * Also clears the screen before rendering.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include "component.hpp"

class Screen : public Component {
	std::vector<std::shared_ptr<Component>> children;

public:
	template <typename... T>
	Screen(T&&... comps) {
		(children.emplace_back(std::forward<T>(comps)), ...);
	}

	/**
	 * @brief Renders the input box at the specified position and size.
	 * @param x The x-coordinate of the input box's position.
	 * @param y The y-coordinate of the input box's position.
	 * @param w The width of the input box.
	 * @param h The height of the input box.
	 */
	void render(int x, int y, int w, int h) const override;
};