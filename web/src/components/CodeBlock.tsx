import { codeToHtml } from "shiki";
import { jetbrainsMono } from "~/fonts";

interface CodeBlockProps {
  code: string;
  lang: string;
  theme?: string;
  border?: boolean;
}

function normalizeCode(code: string): string {
  const lines = code.split("\n");
  while (lines.length && lines[0]!.trim() === "") {
    lines.shift();
  }

  while (lines.length && lines[lines.length - 1]!.trim() === "") {
    lines.pop();
  }
  return ["", ...lines, "", ""].join("\n");
}

export async function CodeBlock({
  code,
  lang = "c++",
  theme = "ayu-dark",
  border = false,
}: CodeBlockProps) {
  const cleanedCode = normalizeCode(code);

  const html = await codeToHtml(cleanedCode, {
    lang,
    theme,
    colorReplacements: {
      "#0b0e14": "#000000",
    },
    defaultColor: false,
    transformers: [
      {
        pre(node) {
          const style = (node.properties.style as string) || "";
          node.properties.style = style
            .replace(/font-family:[^;]+;?/, "")
            .trim();
        },
      },
    ],
  });

  return (
    <>
      <div
        className={`w-full ${border ? "my-3 border-l border-gray-700" : ""} font-jetbrains overflow-x-scroll md:overflow-x-auto`}
        dangerouslySetInnerHTML={{ __html: html }}
      />
    </>
  );
}
