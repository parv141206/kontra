import { getAllDocSlugs, getDocFromSlug } from "~/lib/mdx";
import Sidebar from "~/components/Sidebar";
import PreviousAndNext from "~/components/PreviousAndNext";
import { Suspense } from "react";
import MDXRenderer from "~/components/MDXRenderer";
import DocSkeleton from "~/components/DocSkeleton";
import { notFound } from "next/navigation";
import type { Metadata } from "next";
import { formatSlugToTitle } from "~/lib/utils";

export async function generateMetadata({
  params,
}: {
  params: { slug?: string[] };
}): Promise<Metadata> {
  const slug = params?.slug ?? ["getting-started"];

  try {
    const doc = getDocFromSlug(slug);

    // eslint-disable-next-line @typescript-eslint/no-unsafe-argument
    const title = formatSlugToTitle(doc.metadata.title ?? slug.join(" "));
    const description =
      doc.metadata.description ??
      "Kontra documentation for building Terminal UIs.";
    const ogImageSlug = slug.join("-");

    return {
      title: `${title} - Kontra Docs`,
      description,
      openGraph: {
        title: `${title} - Kontra Docs`,
        description,
        url: `https://kontralib.vercel.app/docs/${slug.join("/")}`,
        images: [
          {
            url: `https://kontralib.vercel.app/og/${ogImageSlug}.png`,
            width: 1200,
            height: 630,
            alt: `${title} - Kontra Docs`,
          },
        ],
      },
      twitter: {
        card: "summary_large_image",
        title: `${title} - Kontra Docs`,
        description,
        images: [`https://kontralib.vercel.app/og/${ogImageSlug}.png`],
      },
    };
  } catch (e) {
    console.error("Metadata generation failed", e);
    return {
      title: "Kontra Docs",
      description: "Kontra - Terminal UI framework documentation.",
    };
  }
}
export default async function DocPage({
  params,
}: {
  params: { slug?: string[] };
}) {
  const slug = params?.slug ?? ["getting-started"];
  const slugMap = getAllDocSlugs();
  const allSlugs = Object.keys(slugMap);

  let doc;
  try {
    doc = getDocFromSlug(slug);
  } catch (error) {
    console.log(error);
    notFound();
  }

  return (
    <main className="mx-auto flex max-w-7xl flex-1 flex-col md:flex-row">
      <Sidebar slugs={allSlugs} />
      <article className="prose prose-invert flex max-w-4xl flex-1 flex-col justify-between px-6 py-10">
        <Suspense fallback={<DocSkeleton />}>
          <MDXRenderer slug={slug} />
        </Suspense>
        <PreviousAndNext slug={slug} />
        <script
          type="application/ld+json"
          dangerouslySetInnerHTML={{
            __html: JSON.stringify({
              "@context": "https://schema.org",
              "@type": "TechArticle",
              headline: doc.metadata.title,
              description: doc.metadata.description,
              author: {
                "@type": "Person",
                name: "Parv",
              },
              publisher: {
                "@type": "Organization",
                name: "Kontra",
                logo: {
                  "@type": "ImageObject",
                  url: "https://kontra.vercel.app/favicon.ico",
                },
              },
              mainEntityOfPage: {
                "@type": "WebPage",
                "@id": `https://kontralib.vercel.app/docs/${slug.join("/")}`,
              },
            }),
          }}
        />
      </article>
    </main>
  );
}
