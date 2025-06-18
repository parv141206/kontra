/*****************************************************************//**
 * \file   border.hpp
 * \brief  Simply a border around other components.
 * 
 * \author parv141206
 * \date   June 2025
 *********************************************************************/
#pragma once;
#include <vector>
#include "component.hpp"

class Border : public Component {
    std::vector<std::unique_ptr<Component>> children;
public:
    template <typename... T>
    Border(T&&... comps) {
        (children.emplace_back(std::make_unique<T>(std::forward<T>(comps))), ...);
    }
    virtual void render(int x, int y, int w, int h) const override;
};