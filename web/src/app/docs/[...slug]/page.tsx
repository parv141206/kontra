import { getAllDocSlugs, getDocFromSlug } from "~/lib/mdx";
import Sidebar from "~/components/Sidebar";
import PreviousAndNext from "~/components/PreviousAndNext";
import { Suspense } from "react";
import MDXRenderer from "~/components/MDXRenderer";
import DocSkeleton from "~/components/DocSkeleton";
import { notFound } from "next/navigation";

export default async function DocPage({
  params,
}: {
  params: { slug?: string[] };
}) {
  const slug = params?.slug ?? ["getting-started"];
  const slugMap = getAllDocSlugs();
  const allSlugs = Object.keys(slugMap);
  try {
    getDocFromSlug(slug);
  } catch (error) {
    console.log(error);
    notFound();
  }
  return (
    <div className="mx-auto flex max-w-7xl flex-1 flex-col md:flex-row">
      <Sidebar slugs={allSlugs} />
      <article className="prose prose-invert flex max-w-4xl flex-1 flex-col justify-between px-6 py-10">
        <Suspense fallback={<DocSkeleton />}>
          <MDXRenderer slug={slug} />
        </Suspense>
        <PreviousAndNext slug={slug} />
      </article>
    </div>
  );
}
