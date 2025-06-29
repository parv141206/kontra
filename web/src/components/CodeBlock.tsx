import { codeToHtml } from "shiki";

interface CodeBlockProps {
  code: string;
  lang: string;
  theme?: string;
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
}: CodeBlockProps) {
  const cleanedCode = normalizeCode(code);

  const html = await codeToHtml(cleanedCode, {
    lang,
    theme,
  });

  return (
    <div
      className="w-full overflow-x-scroll md:overflow-x-auto"
      dangerouslySetInnerHTML={{ __html: html }}
    />
  );
}
