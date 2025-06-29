import React from "react";
import { CodeBlock } from "../CodeBlock";
import { Details, SubTitle } from "../text-utils";
import { Corner } from "../Corner";

export default function CustomizabilityShowcase() {
  const codeSnippet = String.raw`
  #include "../include/kontra.hpp"
  #include "../include/core/utils.hpp" 

  int main() {
      ...
      auto button1 = std::make_shared<Button>(
          "Set Message 1",
          [&]() { message = "Button 1 was clicked!"; },
          ButtonStyleBuilder()
          .set_color(ansi::FG_WHITE)
          .set_background_color(ansi::BG_BLUE)
          .set_color_active(ansi::FG_BLUE)
          .set_background_color_active(ansi::BG_BRIGHT_WHITE)
          .set_bold(true)
          .build()
      );
      ...
  }
  `;

  return (
    <div className="relative flex w-full flex-col md:flex-row">
      <div className="flex w-full flex-col gap-5 border-b border-dashed border-gray-600 p-7 md:w-1/2 md:border-e md:border-b-0">
        <SubTitle>Customizability</SubTitle>
        <Details className="flex flex-col gap-3">
          <p>
            Tweak every pixel - from colors and borders to boldness and
            behavior.
          </p>
          <p>
            Kontra hands you builder-style APIs for ultimate control. Not just
            usable - <b>custom-crafted</b>.
          </p>
        </Details>
      </div>

      <div className="flex w-full flex-col border-gray-700 md:w-1/2 md:border-s md:border-dashed">
        <CodeBlock code={codeSnippet} lang="c++" theme="ayu-dark" />
      </div>

      <div className="md:block">
        <Corner position="top-right" size="md" iconType="plus" />
      </div>
    </div>
  );
}
