// ===================================================================
// KONTRA TUI: todo_app_showcase.cpp
//
// This application combines all core Kontra components to create a
// functional and good-looking TODO list application.
//
// It demonstrates:
// - A clean separation of application state and UI components.
// - A central `update_task_list` function to sync state with the UI.
// - A dynamic list of `Text` components with conditional styling.
// - A horizontal `Flex` layout for a row of buttons.
// - A vertical `List` layout for the main application structure.
// - Simplified keyboard controls for a good user experience.
// ===================================================================

#include "../include/kontra.hpp"
#include "../include/core/utils.hpp"
#include <vector>
#include <string>
#include <memory>

int main() {
    // --- 1. STATE MANAGEMENT ---
    std::vector<std::string> tasks;
    int selected_task = -1;

    // --- 2. COMPONENT INITIALIZATION ---
    auto input_box = std::make_shared<InputBox>();
    input_box->set_active(true);
    auto task_list = std::make_shared<List>();

    // --- 3. CORE LOGIC ---
    auto update_task_list = [&]() {
        task_list->clear();
        for (size_t i = 0; i < tasks.size(); ++i) {
            auto style = (selected_task == static_cast<int>(i))
                ? TextStyle(ansi::FG_BLACK, ansi::BG_YELLOW, true)
                : TextStyle(ansi::FG_WHITE, ansi::BG_BLACK, false);

            auto txt = std::make_shared<Text>(tasks[i], style);
            task_list->add(txt);
        }
        };

    // --- 4. ACTIONS (BUTTONS) ---
    auto add_button = std::make_shared<Button>("Add ('1')", [&]() {
        if (!input_box->get_text().empty()) {
            tasks.push_back(input_box->get_text());
            selected_task = tasks.size() - 1;
            update_task_list();
        }
        }, ButtonStyleBuilder().set_background_color(ansi::BG_GREEN).set_color(ansi::FG_BLACK).set_bold(true).build());

    auto remove_button = std::make_shared<Button>("Remove ('2')", [&]() {
        if (selected_task >= 0 && selected_task < tasks.size()) {
            tasks.erase(tasks.begin() + selected_task);
            if (selected_task >= tasks.size() && !tasks.empty()) {
                selected_task = tasks.size() - 1;
            }
            else if (tasks.empty()) {
                selected_task = -1;
            }
            update_task_list();
        }
        }, ButtonStyleBuilder().set_background_color(ansi::BG_RED).set_color(ansi::FG_WHITE).set_bold(true).build());

    auto clear_button = std::make_shared<Button>("Clear All ('3')", [&]() {
        tasks.clear();
        selected_task = -1;
        update_task_list();
        }, ButtonStyleBuilder().set_background_color(ansi::BG_BRIGHT_BLACK).set_color(ansi::FG_WHITE).set_bold(true).build());

    update_task_list();

    // --- 5. LAYOUT ---
    auto main_content = std::make_shared<List>(
        std::make_shared<Text>("TODO List | Nav: j/k", TextStyle(ansi::FG_WHITE, ansi::BG_BLUE, true)),
        std::make_shared<Input>(input_box),
        std::make_shared<Flex>(FlexDirection::Row, add_button, remove_button, clear_button),
        task_list
    );
    main_content->set_gap(1);

    auto bordered_layout = std::make_shared<Border>(main_content);
    bordered_layout->set_padding(1);

    auto screen = std::make_shared<Screen>(bordered_layout);

    // --- 6. EVENT LOOP ---
    kontra::run(screen, [&](char ch) {
        if (ch == 17) exit(0); // Ctrl+Q

        switch (ch) {
        case '1': add_button->click(); break;
        case '2': remove_button->click(); break;
        case '3': clear_button->click(); break;
        case 'j': // Down
            if (!tasks.empty() && selected_task < tasks.size() - 1) {
                selected_task++;
                update_task_list();
            }
            break;
        case 'k': // Up
            if (selected_task > 0) {
                selected_task--;
                update_task_list();
            }
            break;
        default:
            input_box->handle_input(ch);
            break;
        }
        });

    return 0;
}