import { getDocFromSlug } from "~/lib/mdx";
import { MDXRemote } from "next-mdx-remote/rsc";
import { mdxComponents } from "~/components/MDXComponents";

export default async function MDXRenderer({ slug }: { slug: string[] }) {
  const { content } = getDocFromSlug(slug);
  return <MDXRemote source={content} components={mdxComponents} />;
}
