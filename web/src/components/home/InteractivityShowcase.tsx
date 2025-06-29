import React from "react";
import { CodeBlock } from "../CodeBlock";
import { Details, SubTitle } from "../text-utils";
import { Corner } from "../Corner";

export default function InteractivityShowcase() {
  const codeSnippet = String.raw`
  #include "../include/kontra.hpp"
  #include "../include/core/utils.hpp" 

  int main() {
      ...
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
      ...
  }
  `;

  return (
    <div className="relative flex w-full flex-col-reverse md:flex-row">
      <div className="flex w-full flex-col border-b border-dashed border-gray-700 md:w-1/2 md:border-r md:border-b-0">
        <CodeBlock code={codeSnippet} lang="c++" theme="ayu-dark" />
      </div>

      <div className="flex w-full flex-col gap-5 border-gray-600 p-7 md:w-1/2 md:border-l md:border-dashed">
        <SubTitle>Interactivity</SubTitle>
        <Details className="flex flex-col gap-3">
          <p>
            Hook into raw keypresses and map them to actions - no black-box
            magic, just clean C++ logic.
          </p>
          <p>
            Build apps that <b>feel alive</b> in the terminal - fast reactions,
            tight control, full interactivity.
          </p>
        </Details>
      </div>

      <div className="md:block">
        <Corner position="top-left" size="md" iconType="plus" />
      </div>
    </div>
  );
}
