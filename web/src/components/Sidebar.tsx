"use client";

import { useState, useMemo } from "react";
import { usePathname } from "next/navigation";
import Link from "next/link";
import { RiMenu3Fill } from "react-icons/ri";
import { formatSlugToTitle } from "~/lib/utils";

type SidebarProps = {
  slugs: string[];
};

export default function Sidebar({ slugs }: SidebarProps) {
  const pathname = usePathname();
  const [isExpanded, setIsExpanded] = useState(false);
  const [searchQuery, setSearchQuery] = useState("");

  // eslint-disable-next-line react-hooks/exhaustive-deps
  const tree: Record<string, string[]> = {};
  for (const slug of slugs) {
    const [root, ...rest] = slug.split("/");
    const restPath = rest.join("/");
    tree[root!] ??= [];
    if (restPath) tree[root!]!.push(restPath);
  }

  const filteredTree = useMemo(() => {
    if (!searchQuery) return tree;
    const q = searchQuery.toLowerCase();
    const filtered: Record<string, string[]> = {};
    for (const [root, children] of Object.entries(tree)) {
      const matchedChildren = children.filter((c) =>
        c.toLowerCase().includes(q),
      );
      if (root.toLowerCase().includes(q) || matchedChildren.length > 0) {
        filtered[root] = matchedChildren;
      }
    }
    return filtered;
  }, [tree, searchQuery]);

  const renderSlug = (
    slug: string,
    basePath = "",
    depth = 0,
    isFolder = false,
  ) => {
    const fullSlug = basePath ? `${basePath}/${slug}` : slug;
    const href = `/docs/${fullSlug}`;
    const isActive = pathname === href;
    const padding = { paddingLeft: `${depth * 1.25}rem` };

    if (isFolder) {
      return (
        <li
          key={fullSlug}
          style={padding}
          className="py-2 text-sm font-semibold tracking-wide text-gray-300 uppercase"
        >
          {formatSlugToTitle(slug)}
        </li>
      );
    }

    return (
      <li key={fullSlug} style={padding}>
        <Link
          href={href}
          className={`block rounded px-3 py-1.5 transition ${
            isActive
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
    <div className="sticky top-24 z-20 w-full self-start border-r border-dashed border-gray-600 p-4 backdrop-blur-3xl md:w-fit">
      <aside className="bg-with-noise w-full rounded border border-gray-700 px-4 py-3 md:w-64 md:border-none md:bg-transparent md:px-0">
        <div className="mb-2 flex items-center justify-between md:mb-4 md:border-b md:border-dashed md:border-gray-600 md:pb-2">
          <div className="text-lg font-bold text-gray-100">Docs</div>
          <button
            onClick={() => setIsExpanded((prev) => !prev)}
            className="md:hidden"
          >
            <RiMenu3Fill
              className={`transition-transform ${isExpanded ? "rotate-90" : ""}`}
            />
          </button>
        </div>

        <div
          className={`grid transition-all duration-300 ease-in-out md:block ${
            isExpanded
              ? "max-h-[30vh] grid-rows-[1fr] opacity-100"
              : "max-h-0 grid-rows-[0fr] opacity-0"
          } md:max-h-[80vh] md:opacity-100`}
        >
          <div className="overflow-y-auto">
            <input
              type="text"
              placeholder="Search..."
              value={searchQuery}
              onChange={(e) => setSearchQuery(e.target.value)}
              className="mb-3 w-full rounded border border-gray-600 bg-black px-2 py-1 text-sm text-gray-200 placeholder:text-gray-400 md:hidden"
            />

            <ul className="flex flex-col text-sm">
              {Object.entries(filteredTree).map(([root, children]) => {
                const hasChildren = children.length > 0;
                return (
                  <div key={root}>
                    {hasChildren
                      ? renderSlug(root, "", 0, true)
                      : renderSlug(root)}
                    {hasChildren &&
                      children
                        .sort()
                        .map((childSlug) => renderSlug(childSlug, root, 1))}
                  </div>
                );
              })}
            </ul>
          </div>
        </div>
      </aside>
    </div>
  );
}
