"use client";

import Link from "next/link";
import { usePathname } from "next/navigation";
import { formatSlugToTitle } from "~/lib/utils";

type SidebarProps = {
  slugs: string[];
};

export default function Sidebar({ slugs }: SidebarProps) {
  const pathname = usePathname();

  const tree: Record<string, string[]> = {};
  for (const slug of slugs) {
    const [root, ...rest] = slug.split("/");
    const restPath = rest.join("/");
    tree[root!] ??= [];
    if (restPath) tree[root!]!.push(restPath);
  }

  const renderSlug = (
    slug: string,
    basePath = "",
    depth = 0,
    isFolder = false,
  ) => {
    const fullSlug = basePath ? `${basePath}/${slug}` : slug;

    const padding = { paddingLeft: `${depth * 1.25}rem` };

    if (isFolder) {
      return (
        <li
          key={fullSlug}
          style={padding}
          className="py-3 tracking-wide text-gray-300 uppercase"
        >
          {formatSlugToTitle(slug)}
        </li>
      );
    }

    const href = `/docs/${fullSlug}`;
    const active = pathname === href;

    return (
      <li key={fullSlug} style={padding}>
        <Link
          href={href}
          className={`block rounded px-3 py-1.5 transition ${
            active
              ? "border border-dashed border-gray-600 text-green-400"
              : "text-gray-400 hover:text-white"
          }`}
        >
          {formatSlugToTitle(slug)}
        </Link>
      </li>
    );
  };

  return (
    <aside className="sticky top-24 w-full self-start border-r border-dashed border-gray-600 p-4 md:w-64">
      <ul className="flex flex-col text-sm">
        {Object.entries(tree).map(([root, children]) => {
          const hasChildren = children.length > 0;

          return (
            <div key={root}>
              {hasChildren ? renderSlug(root, "", 0, true) : renderSlug(root)}{" "}
              {hasChildren &&
                children
                  .sort()
                  .map((childSlug) => renderSlug(childSlug, root, 1))}
            </div>
          );
        })}
      </ul>
    </aside>
  );
}
