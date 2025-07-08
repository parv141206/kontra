# This file is only processed if KONTRA_BUILD_EXAMPLES is ON.

function(add_kontra_example name source)
    add_executable(${name} ${source})
    target_link_libraries(${name} PRIVATE kontra)
endfunction()

add_kontra_example(run_main                    main.cpp)
add_kontra_example(run_text_example            text_example.cpp)
add_kontra_example(run_border_example          border_example.cpp)
add_kontra_example(run_button_example          button_example.cpp)
add_kontra_example(run_checkbox_example        checkbox_example.cpp)
add_kontra_example(run_flex_example            flex_example.cpp)
add_kontra_example(run_input_box_example       input_box_example.cpp)
add_kontra_example(run_list_example            list_example.cpp)
add_kontra_example(run_todo_showcase           showcase/todo_app_showcase.cpp)
