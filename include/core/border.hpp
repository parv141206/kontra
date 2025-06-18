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

#pragma once
#include <vector>
#include <memory>
#include "component.hpp"

class Border : public Component {
    std::vector<std::shared_ptr<Component>> children;

public:
    template <typename... T>
    Border(T&&... comps) {
        addComponents(std::forward<T>(comps)...);
    }

    virtual void render(int x, int y, int w, int h) const override;

private:
    void addComponent(const std::shared_ptr<Component>& comp) {
        children.push_back(comp);
    }

    void addComponent(std::shared_ptr<Component>&& comp) {
        children.push_back(std::move(comp));
    }

    template <typename First, typename... Rest>
    void addComponents(First&& first, Rest&&... rest) {
        addComponent(std::forward<First>(first));
        addComponents(std::forward<Rest>(rest)...);
    }

    void addComponents() {} // base case
};
