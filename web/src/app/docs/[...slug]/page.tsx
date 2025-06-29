import { getAllDocSlugs } from "~/lib/mdx";
import { getDocFromSlug } from "~/lib/mdx";
import { MDXRemote } from "next-mdx-remote/rsc";
import { mdxComponents } from "~/components/MDXComponents";
import Sidebar from "~/components/Sidebar";
import PreviousAndNext from "~/components/PreviousAndNext";

export default function DocPage({ params }: { params: { slug?: string[] } }) {
  const params_ = params;
  const slug = params_.slug ?? ["getting-started"];
  const { content } = getDocFromSlug(slug);

  const slugMap = getAllDocSlugs();
  const allSlugs = Object.keys(slugMap);

  return (
    <div className="mx-auto flex max-w-7xl flex-1">
      <Sidebar slugs={allSlugs} />
      <article className="prose prose-invert flex max-w-4xl flex-1 flex-col justify-between px-6 py-10">
        <div>
          <MDXRemote source={content} components={mdxComponents} />
        </div>
        <PreviousAndNext slug={slug} />
      </article>
    </div>
  );
}
