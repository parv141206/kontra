import { codeToHtml } from "shiki";

interface CodeBlockProps {
  code: string;
  lang: string;
  theme?: string;
}

export async function CodeBlock({
  code,
  lang,
  theme = "github-dark",
}: CodeBlockProps) {
  const html = await codeToHtml(code, {
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
