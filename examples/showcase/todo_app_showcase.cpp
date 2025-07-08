// ===================================================================
// KONTRA TUI: todo_app_showcase.cpp
//
// This version is syntactically correct and uses a clean, state-driven
// approach to building the UI.
// ===================================================================

#include "../include/kontra.hpp"
#include "../include/core/box.hpp"
#include "../include/core/utils.hpp"
#include <vector>
#include <string>
#include <memory>

enum class AppMode
{
    Navigating,
    Editing
};

int main()
{
    // --- 1. STATE MANAGEMENT ---
    std::vector<std::string> tasks;
    int selected_task = -1;
    AppMode current_mode = AppMode::Navigating;

    // --- 2. COMPONENT INITIALIZATION ---
    auto input_box = std::make_shared<InputBox>();
    input_box->set_label("Enter todo!");

    auto main_list = std::make_shared<List>();
    // These vectors will be populated by the update_ui function
    std::vector<std::shared_ptr<Text>> task_text_components;
    std::vector<std::shared_ptr<Button>> buttons;

    // --- 3. ACTIONS (Lambdas) ---
    // Define the application logic first. These will be captured by the UI update function.
    std::function<void()> add_task;
    std::function<void()> remove_task;
    std::function<void()> clear_tasks;

    // --- 4. UI UPDATE FUNCTION ---
    auto update_ui = [&]()
    {
        input_box->set_active(current_mode == AppMode::Editing);
        main_list->clear();
        task_text_components.clear();
        buttons.clear();

        auto header_text = std::make_shared<Text>([&]()
                                                  { return (current_mode == AppMode::Editing)
                                                               ? "EDITING | Enter: Add Task | Esc: Cancel"
                                                               : "NAVIGATION | i: Insert | j/k: Nav | d: Del | Mouse"; }, 
                                                  TextStyle(ansi::FG_WHITE, ansi::BG_DEFAULT, true));

        // --- REUSABLE BUTTON STYLES ---
        auto add_style = ButtonStyleBuilder()
            .set_inactive_style(StyleBuilder().set_color(ansi::FG_BLACK).set_background_color(ansi::BG_GREEN).set_bold(true).build())
            .set_active_style(StyleBuilder().set_color(ansi::FG_WHITE).set_background_color(ansi::BG_BRIGHT_GREEN).set_bold(true).build())
            .build();
        
        auto remove_style = ButtonStyleBuilder()
            .set_inactive_style(StyleBuilder().set_color(ansi::FG_WHITE).set_background_color(ansi::BG_RED).set_bold(true).build())
            .set_active_style(StyleBuilder().set_color(ansi::FG_WHITE).set_background_color(ansi::BG_BRIGHT_RED).set_bold(true).build())
            .build();
            
        auto clear_style = ButtonStyleBuilder()
            .set_inactive_style(StyleBuilder().set_color(ansi::FG_WHITE).set_background_color(ansi::BG_BRIGHT_BLACK).set_bold(true).build())
            .set_active_style(StyleBuilder().set_color(ansi::FG_BLACK).set_background_color(ansi::BG_WHITE).set_bold(true).build())
            .build();

        // --- Create buttons and apply the new styles ---
        auto add_button = std::make_shared<Button>(" Add ", add_task, add_style);
        auto remove_button = std::make_shared<Button>(" Remove ", remove_task, remove_style);
        auto clear_button = std::make_shared<Button>(" Clear All ", clear_tasks, clear_style);

        buttons = {add_button, remove_button, clear_button};

        auto button_bar = std::make_shared<Flex>(FlexDirection::Row, add_button, remove_button, clear_button);
        button_bar->set_gap(1);

        main_list->add(header_text);
        main_list->add(input_box);
        main_list->add(button_bar);

        for (size_t i = 0; i < tasks.size(); ++i)
        {
            auto style = (selected_task == static_cast<int>(i))
                             ? TextStyle(ansi::FG_BLACK, ansi::BG_BRIGHT_WHITE, true)
                             : TextStyle(ansi::FG_WHITE, "", false);
            auto txt = std::make_shared<Text>(tasks[i], style);
            main_list->add(txt);
            task_text_components.push_back(txt);
        }
    };

    // --- Now define the implementation of the actions ---
    add_task = [&]()
    {
        if (!input_box->get_text().empty())
        {
            tasks.push_back(input_box->get_text());
            input_box->set_text("");
            selected_task = tasks.size() - 1;
            current_mode = AppMode::Navigating;
            update_ui();
        }
    };
    remove_task = [&]()
    {
        if (selected_task >= 0 && selected_task < (int)tasks.size())
        {
            tasks.erase(tasks.begin() + selected_task);
            if (selected_task >= (int)tasks.size() && !tasks.empty())
            {
                selected_task = tasks.size() - 1;
            }
            else if (tasks.empty())
            {
                selected_task = -1;
            }
            update_ui();
        }
    };
    clear_tasks = [&]()
    {
        tasks.clear();
        selected_task = -1;
        update_ui();
    };

    update_ui(); // Initial UI draw

    // --- 5. LAYOUT ---
    main_list->set_gap(1);
    auto screen = std::make_shared<Screen>(
        chain(std::make_shared<Border>(
                  main_list,
                  BorderStyleBuilder()
                      .set_title("tOdO!!!")
                      .set_characters(BorderPreset::DOUBLE)
                      .set_title_alignment(TitleAlignment::Center)
                      .build()),
              [](Border &b)
              { b.set_padding(1); }));

    // --- 6. EVENT LOOP ---
    kontra::run(screen, [&](const InputEvent &event)
                {
        if (current_mode == AppMode::Editing) {
            if (event.type == EventType::KEY_PRESS) {
                switch (event.key) {
                case 13: add_task(); break;
                case 27: current_mode = AppMode::Navigating; update_ui(); break;
                default: input_box->handle_input(event.key); break;
                }
            }
        }
        else {
            switch (event.type) {
            case EventType::KEY_PRESS:
                switch (event.key) {
                case 'i': current_mode = AppMode::Editing; update_ui(); break;
                case 'd': remove_task(); break;
                case 'j': if (!tasks.empty() && selected_task < (int)tasks.size() - 1) { selected_task++; update_ui(); } break;
                case 'k': if (selected_task > 0) { selected_task--; update_ui(); } break;
                }
                break;
            case EventType::MOUSE_PRESS:
                if (buttons[0]->contains(event.mouse_x, event.mouse_y)) add_task();
                else if (buttons[1]->contains(event.mouse_x, event.mouse_y)) remove_task();
                else if (buttons[2]->contains(event.mouse_x, event.mouse_y)) clear_tasks();
                else {
                    for (size_t i = 0; i < task_text_components.size(); ++i) { if (task_text_components[i]->contains(event.mouse_x, event.mouse_y)) { selected_task = i; update_ui(); return; } }
                    if (input_box->contains(event.mouse_x, event.mouse_y)) { current_mode = AppMode::Editing; update_ui(); }
                }
                break;
            case EventType::MOUSE_SCROLL_UP:   main_list->scroll_up();   break;
            case EventType::MOUSE_SCROLL_DOWN: main_list->scroll_down(); break;
            default: break;
            }
        } });

    return 0;
}
