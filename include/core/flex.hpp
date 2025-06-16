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

class Flex : public Component {
    std::vector<std::unique_ptr<Component>> children;
    FlexDirection direction;
public:
    template <typename... T>
    Flex(FlexDirection dir, T&&... comps) : direction(dir) {
        (children.emplace_back(std::make_unique<T>(std::forward<T>(comps))), ...);
    }
    virtual void render(int x, int y, int w, int h) const override;
};