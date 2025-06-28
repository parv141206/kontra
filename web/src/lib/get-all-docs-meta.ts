import fs from "fs";
import path from "path";
import matter from "gray-matter";
import { DOCS_PATH } from "./mdx";

export function getAllDocsMeta(dir = "", baseSlug: string[] = []) {
  const fullPath = path.join(DOCS_PATH, dir);
  const entries = fs.readdirSync(fullPath, { withFileTypes: true });

  let slugs: { slug: string[]; title: string }[] = [];

  for (const entry of entries) {
    if (entry.isDirectory()) {
      const sub = getAllDocsMeta(path.join(dir, entry.name), [
        ...baseSlug,
        stripPrefix(entry.name),
      ]);
      slugs = [...slugs, ...sub];
    } else if (entry.name.endsWith(".mdx")) {
      const rawSlug = entry.name.replace(/\.mdx$/, "");
      const cleanSlug = stripPrefix(rawSlug);
      const filePath = path.join(fullPath, entry.name);
      const fileContent = fs.readFileSync(filePath, "utf8");
      const { data } = matter(fileContent);

      slugs.push({
        slug: [...baseSlug, cleanSlug],
        title: data.title ?? cleanSlug,
      });
    }
  }

  slugs.sort((a, b) => {
    const aPrefix = getNumericPrefix(a.slug.at(-1) ?? "");
    const bPrefix = getNumericPrefix(b.slug.at(-1) ?? "");
    return aPrefix - bPrefix;
  });

  return slugs;
}

function stripPrefix(str: string) {
  return str.replace(/^\d+\./, "");
}

function getNumericPrefix(str: string) {
  const match = /^(\d+)\./.exec(str);
  return match ? parseInt(match[1]!, 10) : Infinity;
}
