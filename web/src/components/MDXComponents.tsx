import type { MDXComponents } from "mdx/types";
import type { ComponentPropsWithoutRef } from "react";
import { CodeBlock } from "./CodeBlock";
import Image from "next/image";

export const mdxComponents: MDXComponents = {
  h1: (props: ComponentPropsWithoutRef<"h1">) => (
    <h1
      className="mb-6 text-4xl leading-tight font-bold text-green-200 md:text-5xl"
      {...props}
    />
  ),
  h2: (props: ComponentPropsWithoutRef<"h2">) => (
    <h2
      className="mt-10 mb-4 text-3xl leading-snug font-semibold text-gray-200 md:text-3xl"
      {...props}
    />
  ),
  h3: (props: ComponentPropsWithoutRef<"h3">) => (
    <h3
      className="mt-8 mb-2 text-2xl font-semibold text-gray-300 md:text-2xl"
      {...props}
    />
  ),
  h4: (props: ComponentPropsWithoutRef<"h4">) => (
    <h4 className="mt-6 mb-2 text-xl font-medium md:text-2xl" {...props} />
  ),
  h5: (props: ComponentPropsWithoutRef<"h5">) => (
    <h5 className="mt-4 mb-2 text-lg font-medium md:text-xl" {...props} />
  ),
  h6: (props: ComponentPropsWithoutRef<"h6">) => (
    <h6
      className="mt-2 mb-1 text-base font-medium tracking-wide text-gray-400 uppercase"
      {...props}
    />
  ),
  img: (props: ComponentPropsWithoutRef<"img">) => {
    const { src, alt, width, height, className } = props;

    if (typeof src !== "string") return null;

    return (
      <Image
        src={src}
        alt={alt ?? ""}
        width={width ? +width : 500}
        height={height ? +height : 300}
        className={`my-4 rounded ${className ?? ""}`}
      />
    );
  },
  p: (props: ComponentPropsWithoutRef<"p">) => (
    <p className="mb-4 leading-relaxed text-gray-300" {...props} />
  ),
  a: (props: ComponentPropsWithoutRef<"a">) => (
    <a
      className="text-green-400 underline underline-offset-2 transition-colors duration-200 hover:text-green-300"
      target="_blank"
      rel="noopener noreferrer"
      {...props}
    />
  ),
  ul: (props: ComponentPropsWithoutRef<"ul">) => (
    <ul
      className="mb-4 list-outside list-disc space-y-2 pl-6 text-gray-300"
      {...props}
    />
  ),

  ol: (props: ComponentPropsWithoutRef<"ol">) => (
    <ol
      className="mb-4 list-inside list-decimal space-y-2 text-gray-300"
      {...props}
    />
  ),
  li: (props: ComponentPropsWithoutRef<"li">) => (
    <li className="leading-[1.7] break-words text-gray-300" {...props} />
  ),
  blockquote: (props: ComponentPropsWithoutRef<"blockquote">) => (
    <blockquote
      className="my-6 border-l-4 border-green-500 pl-4 text-gray-400 italic"
      {...props}
    />
  ),
  pre: (props: ComponentPropsWithoutRef<"pre">) => (
    <pre
      className="my-4 overflow-x-auto rounded bg-gray-900 p-4 text-sm text-white"
      {...props}
    />
  ),
  code: (props: ComponentPropsWithoutRef<"code">) => (
    <code
      className="rounded-sm bg-gray-800 px-1 py-[0.1rem] font-mono text-green-300"
      {...props}
    />
  ),
  table: (props: ComponentPropsWithoutRef<"table">) => (
    <div className="my-6 w-full overflow-x-auto rounded border border-gray-700">
      <table
        className="w-full table-auto text-left text-sm text-gray-300"
        {...props}
      />
    </div>
  ),
  thead: (props: ComponentPropsWithoutRef<"thead">) => (
    <thead className="bg-gray-800 text-gray-100" {...props} />
  ),
  tbody: (props: ComponentPropsWithoutRef<"tbody">) => <tbody {...props} />,
  tr: (props: ComponentPropsWithoutRef<"tr">) => (
    <tr className="border-b border-gray-700" {...props} />
  ),
  th: (props: ComponentPropsWithoutRef<"th">) => (
    <th className="px-4 py-2 font-semibold" {...props} />
  ),
  td: (props: ComponentPropsWithoutRef<"td">) => (
    <td className="px-4 py-2" {...props} />
  ),
  hr: () => <hr className="my-8 border-dashed border-gray-600" />,
  CodeBlock,
};
