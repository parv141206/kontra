import { CodeBlock } from "../CodeBlock";
import { Corner } from "../Corner";
import { Details, SubSubTitle, SubTitle } from "../text-utils";

export default function UtilityShowcase() {
  const codeSnippet = String.raw`
    inline constexpr const char* RESET = "\033[0m";
    inline constexpr const char* BOLD = "\033[1m";
    inline constexpr const char* DIM = "\033[2m";
    inline constexpr const char* ITALIC = "\033[3m";
    inline constexpr const char* UNDERLINE = "\033[4m";
    inline constexpr const char* INVERSE = "\033[7m";
    inline constexpr const char* STRIKETHROUGH = "\033[9m";
    ...
    inline constexpr const char* FG_BLACK = "\033[30m";
    inline constexpr const char* FG_RED = "\033[31m";
    inline constexpr const char* FG_GREEN = "\033[32m";
    inline constexpr const char* FG_YELLOW = "\033[33m";
    ...
    inline constexpr const char* BG_BLACK = "\033[40m";
    inline constexpr const char* BG_RED = "\033[41m";
    inline constexpr const char* BG_GREEN = "\033[42m";
    inline constexpr const char* BG_YELLOW = "\033[43m";
    ...
  `;

  return (
    <div className="relative flex w-full flex-col-reverse md:flex-row">
      <div className="flex w-full flex-col border-b border-dashed border-gray-700 md:w-1/2 md:border-r md:border-b-0">
        <CodeBlock code={codeSnippet} lang="c++" theme="ayu-dark" />
        <SubSubTitle className="border border-dashed border-gray-700 p-3 text-center">
          And many more!
        </SubSubTitle>
      </div>

      <div className="flex w-full flex-col gap-5 border-gray-600 p-7 md:w-1/2 md:border-l md:border-dashed">
        <SubTitle>Hardcore Utilities</SubTitle>
        <Details className="flex flex-col gap-3">
          <p>Kontra ships with a Swiss army knife of styling tools.</p>
          <p>Tweak, theme, and supercharge your TUI components with ease.</p>
          <p>No macros. No bloat. Just raw control and clean C++.</p>
        </Details>
      </div>

      <div className="md:block">
        <Corner position="top-left" size="md" iconType="plus" />
      </div>
    </div>
  );
}
