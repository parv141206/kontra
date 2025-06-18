#include "../include/kontra.hpp"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    TextStyle titleStyle(ansi::FG_BLACK, ansi::BG_GREEN, true, true);

    auto title = std::make_shared<Text>("France", titleStyle);

    auto list = std::make_shared<Flex>(FlexDirection::Column);
    auto borderedList = std::make_shared<Border>(list);

    auto layout = std::make_shared<Flex>(FlexDirection::Row, title, borderedList);
    auto borderedLayout = std::make_shared<Border>(layout);

    Screen ui(borderedLayout);

    for (int tick = 1; tick <= 5; ++tick) {
        list->clear();

        for (int i = 0; i < tick; ++i) {
            list->add(std::make_shared<Text>("idli " + std::to_string(i)));
        }

        ui.render(1, 1, 100, 95);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    return 0;
}
