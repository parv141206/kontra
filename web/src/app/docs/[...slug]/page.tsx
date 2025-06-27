import { getAllDocSlugs } from "~/lib/mdx";
import { getDocFromSlug } from "~/lib/mdx";
import { MDXRemote } from "next-mdx-remote/rsc";
import { mdxComponents } from "~/components/MDXComponents";
import Sidebar from "~/components/Sidebar";

export default function DocPage({ params }: { params: { slug?: string[] } }) {
  const slug = params.slug ?? ["getting-started"];
  const fullSlug = slug.join("/");
  const { content } = getDocFromSlug(slug);

  const allSlugs = getAllDocSlugs();

  return (
    <div className="flex w-full">
      <Sidebar slugs={allSlugs} />
      <article className="prose prose-invert max-w-4xl px-6 py-10">
        <MDXRemote source={content} components={mdxComponents} />
      </article>
    </div>
  );
}
