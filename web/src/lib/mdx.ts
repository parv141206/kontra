import fs from "fs";
import path from "path";
import matter from "gray-matter";

export const DOCS_PATH = path.join(process.cwd(), "src/docs");

function stripNumericPrefix(name: string): string {
  return name.replace(/^\d+\./, "");
}

export function getDocFromSlug(slug: string[]) {
  const slugMap = getAllDocSlugs();
  const fullSlug = slug.join("/");
  const realSlug = slugMap[fullSlug];

  if (!realSlug) {
    throw new Error(`No doc found for slug: ${fullSlug}`);
  }

  const filePath = path.join(DOCS_PATH, realSlug) + ".mdx";
  const source = fs.readFileSync(filePath, "utf-8");
  const { content, data } = matter(source);

  return {
    content,
    metadata: data,
  };
}

export function getAllDocSlugs(dir = ""): Record<string, string> {
  const fullPath = path.join(DOCS_PATH, dir);
  const entries = fs.readdirSync(fullPath, { withFileTypes: true });

  const slugMap: Record<string, string> = {};

  const files = entries
    .filter((entry) => entry.isFile() && entry.name.endsWith(".mdx"))
    .sort((a, b) => a.name.localeCompare(b.name, undefined, { numeric: true }));

  const folders = entries
    .filter((entry) => entry.isDirectory())
    .sort((a, b) => a.name.localeCompare(b.name));

  for (const file of files) {
    const nameWithoutExt = file.name.replace(/\.mdx$/, "");
    const strippedSlug = stripNumericPrefix(nameWithoutExt);
    const userSlug = path.join(dir, strippedSlug).replace(/\\/g, "/");
    const realPath = path.join(dir, nameWithoutExt).replace(/\\/g, "/");

    slugMap[userSlug] = realPath;
  }

  for (const folder of folders) {
    const nested = getAllDocSlugs(path.join(dir, folder.name));
    Object.assign(slugMap, nested);
  }

  return slugMap;
}
