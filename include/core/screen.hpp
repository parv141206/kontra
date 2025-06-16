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
	std::vector<std::unique_ptr<Component>> children;

public:
	template <typename... T>
	Screen(T&&... comps) {
		(children.emplace_back(std::make_unique<T>(std::forward<T>(comps))), ...);
	}

	void render(int x, int y, int w, int h) const override;
};