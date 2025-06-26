#include "../include/kontra.hpp"
#include "../include/core/utils.hpp"
#include <string>
#include <vector>
#include <memory>
#include <sstream>

int main() {
    ansi::clear_screen();
    std::cout << "\033[2J\033[H";

    std::vector<std::string> stack;
    int push_count = 1;

    auto list = std::make_shared<List>();

    auto refresh_list = [&]() {
        list->clear();
        for (const auto& item : stack) {
            list->add(std::make_shared<Text>(item));
        }
        };

    auto push_button = std::make_shared<Button>(
        "Push",
        [&]() {
            std::ostringstream oss;
            oss << "Item " << push_count++;
            stack.push_back(oss.str());
            refresh_list();
        },
        ButtonStyleBuilder()
        .set_background_color(ansi::BG_BLACK)
        .set_background_color_active(ansi::BG_BLUE)
        .set_color(ansi::FG_WHITE)
        .set_color_active(ansi::FG_BLACK)
        .set_bold(true)
        .build()
    );
    push_button->set_active(true);

    auto pop_button = std::make_shared<Button>(
        "Pop",
        [&]() {
            if (!stack.empty()) {
                stack.pop_back();
                refresh_list();
            }
        },
        ButtonStyleBuilder()
        .set_background_color(ansi::BG_BLACK)
        .set_background_color_active(ansi::BG_BLUE)
        .set_color(ansi::FG_WHITE)
        .set_color_active(ansi::FG_BLACK)
        .set_bold(true)
        .build()
    );
    pop_button->set_active(false);

    auto layout = std::make_shared<Border>(
        std::make_shared<Flex>(
            FlexDirection::Row,
            list,
            std::make_shared<List>(
                push_button,
                pop_button
            )
        )
    );

    std::shared_ptr<Button> active_button = push_button;

    auto screen = std::make_shared<Screen>(layout);
    kontra::run(screen, [&](char ch) {
        if (ch == 17) exit(0); // Ctrl+Q
        if (ch == '\t') { // TAB 
            if (active_button == push_button) {
                push_button->set_active(false);
                pop_button->set_active(true);
                active_button = pop_button;
            }
            else {
                pop_button->set_active(false);
                push_button->set_active(true);
                active_button = push_button;
            }
        }
        if (ch == '\n' || ch == '\r') {
            active_button->click();
        }
        });

    return 0;
}