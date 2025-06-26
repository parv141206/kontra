#include "../include/kontra.hpp"
#include "../include/core/utils.hpp"
#include <vector>
#include <string>
#include <memory>

int main() {
    //=========================================================================
    // 1. STATE MANAGEMENT
    //=========================================================================
    // All application data is stored in simple C++ variables. The UI will
    // be a reflection of this state.
    std::vector<std::string> tasks;
    int selected_task = -1; // -1 means no task is selected.

    //=========================================================================
    // 2. COMPONENT INITIALIZATION
    //=========================================================================
    // Create shared pointers to all the components that make up our UI.

    // The text box for user input. It's set as active by default.
    auto input_box = std::make_shared<InputBox>();
    input_box->set_active(true);

    // The list that will visually hold our tasks. It starts empty.
    auto task_list = std::make_shared<List>();

    //=========================================================================
    // 3. CORE LOGIC: THE UPDATE FUNCTION
    //=========================================================================
    // This is the most important function. It synchronizes the UI with the
    // current state. It's called every time the data (tasks vector) changes.
    auto update_task_list = [&]() {
        // First, clear the visual list completely.
        task_list->clear();

        // Re-populate the visual list from the `tasks` vector.
        for (size_t i = 0; i < tasks.size(); ++i) {
            // Dynamically choose a style based on whether the task is selected.
            auto style = (selected_task == static_cast<int>(i))
                ? TextStyle(ansi::FG_BLACK, ansi::BG_YELLOW, true, false) // Highlighted style
                : TextStyle(ansi::FG_WHITE, "", false, false);             // Default style

            // Create a new Text component for each task. The lambda ensures the
            // text updates if the underlying data were to change.
            auto txt = std::make_shared<Text>([&, i] { return tasks[i]; }, style);
            task_list->add(txt);
        }
        };

    //=========================================================================
    // 4. DEFINE ACTIONS (BUTTONS)
    //=========================================================================
    // Each button is given a lambda function that modifies the application
    // state and then calls `update_task_list()` to reflect the change.

    auto add_button = std::make_shared<Button>(
        "Add ('1')",
        [&]() {
            std::string task = input_box->get_text();
            if (!task.empty()) {
                tasks.push_back(task);
                selected_task = tasks.size() - 1; // Auto-select the new task.
                update_task_list();
            }
        },
        ButtonStyleBuilder().set_background_color(ansi::BG_GREEN).set_color(ansi::FG_BLACK).set_bold(true).build()
    );

    auto remove_button = std::make_shared<Button>(
        "Remove ('2')",
        [&]() {
            if (selected_task >= 0 && selected_task < static_cast<int>(tasks.size())) {
                tasks.erase(tasks.begin() + selected_task);
                if (selected_task >= static_cast<int>(tasks.size()) && !tasks.empty()) {
                    selected_task = tasks.size() - 1;
                }
                else if (tasks.empty()) {
                    selected_task = -1;
                }
                update_task_list();
            }
        },
        ButtonStyleBuilder().set_background_color(ansi::BG_RED).set_color(ansi::FG_WHITE).set_bold(true).build()
    );

    auto clear_button = std::make_shared<Button>(
        "Clear All ('3')",
        [&]() {
            tasks.clear();
            selected_task = -1;
            update_task_list();
        },
        ButtonStyleBuilder().set_background_color(ansi::BG_BLACK).set_color(ansi::FG_WHITE).set_bold(true).build()
    );

    // Initial population of the list when the app starts.
    update_task_list();

    //=========================================================================
    // 5. DEFINE THE LAYOUT
    //=========================================================================
    // Components are nested inside containers to build the UI structure.
    // The `List` component is the correct choice for the main container, as it
    // stacks elements vertically and respects each child's preferred height.
    auto main_content = std::make_shared<List>(
        std::make_shared<Text>("TODO List | Nav: j/k", TextStyle(ansi::FG_WHITE, ansi::BG_BLUE, true, false)),
        std::make_shared<Input>(input_box),
        // A Flex(Row) is correct here for a horizontal button layout.
        std::make_shared<Flex>(
            FlexDirection::Row,
            add_button,
            remove_button,
            clear_button
        ),
        task_list // The dynamic list of tasks is the last element.
    );
    main_content->set_gap(1); // Add a 1-line gap between main elements.

    // Wrap the entire layout in a border for a polished look.
    auto bordered = std::make_shared<Border>(main_content);
    bordered->set_padding(2);

    // The Screen is the root component that owns the entire layout.
    auto screen = std::make_shared<Screen>(bordered);


    //=========================================================================
    // 6. THE EVENT LOOP
    //=========================================================================
    // `kontra::run` starts the application. The provided lambda handles all
    // keyboard input. This example uses a simple `switch` statement for clarity.
    kontra::run(screen, [&](char ch) {
        if (ch == 17) exit(0); // Ctrl+Q to exit.

        switch (ch) {
        case '1':
            add_button->click();
            break;
        case '2':
            remove_button->click();
            break;
        case '3':
            clear_button->click();
            break;
        case 'j': // Move selection down
            if (!tasks.empty() && selected_task < static_cast<int>(tasks.size()) - 1) {
                selected_task++;
                update_task_list();
            }
            break;
        case 'k': // Move selection up
            if (selected_task > 0) {
                selected_task--;
                update_task_list();
            }
            break;
        default:
            // Any other character is treated as input for the text box.
            input_box->handle_input(ch);
            break;
        }
        });

    return 0;
}