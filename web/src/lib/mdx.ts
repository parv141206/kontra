import fs from "fs";
import path from "path";
import matter from "gray-matter";

export const DOCS_PATH = path.join(process.cwd(), "src/docs");

export function getDocFromSlug(slug: string[]) {
  const fullPath = path.join(DOCS_PATH, ...slug) + ".mdx";
  const source = fs.readFileSync(fullPath, "utf-8");
  const { content, data } = matter(source);

  return { content, metadata: data };
}

export function getAllDocSlugs(dir = ""): string[] {
  const fullPath = path.join(DOCS_PATH, dir);
  const entries = fs.readdirSync(fullPath, { withFileTypes: true });

  const slugs: string[] = [];

  for (const entry of entries) {
    if (entry.isDirectory()) {
      slugs.push(...getAllDocSlugs(path.join(dir, entry.name)));
    } else if (entry.name.endsWith(".mdx")) {
      const slug = path.join(dir, entry.name.replace(/\.mdx$/, ""));
      slugs.push(slug.replace(/\\/g, "/"));
    }
  }

  return slugs;
}
