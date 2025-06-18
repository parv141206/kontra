/*****************************************************************//**
 * \file   flex.hpp
 * \brief  A Flex component that arranges its children in a row or column.
 * It acts as a container for other components, allowing them to be laid out.
 * 
 * todo: Obviously adding more features like spacing, alignment, etc. would be useful.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once
#include "component.hpp"
#include <vector>

enum class FlexDirection {
    Row,
    Column
};

/**
 * 
 * WARNING
 * 
 * The following code is enough to give you brain damage. This is some "modern C++" shit.
 * 
 * Before scrolling, be mentally prepared.
 * 
 * This was changed alot, and at this moment, if it works, god knows how. This file is heavily vibe coded (brings a shame but well, it is what it is)
 * 
 * .
 */


class Flex : public Component {
	std::vector<std::shared_ptr<Component>> children;
	FlexDirection direction;

public:
	template <typename... T>
	Flex(FlexDirection dir, T&&... comps)
		: direction(dir) {
		addComponents(std::forward<T>(comps)...);
	}

	Flex(FlexDirection dir, std::vector<std::shared_ptr<Component>>&& comps)
		: direction(dir), children(std::move(comps)) {
	}

	void add(std::shared_ptr<Component> comp) {
		children.push_back(std::move(comp));
	}
	void clear() {
		children.clear();
	}

	virtual void render(int x, int y, int w, int h) const override;

private:
	template <typename First, typename... Rest>
	void addComponents(First&& first, Rest&&... rest) {
		children.push_back(std::forward<First>(first));
		addComponents(std::forward<Rest>(rest)...);
	}

	void addComponents() {}
};