import Link from "next/link";
import { ArrowLeft, ArrowRight } from "lucide-react";
import { getAllDocsMeta } from "~/lib/get-all-docs-meta";
import { formatSlugToTitle } from "~/lib/utils";

type Props = {
  slug: string[];
};

export default function PreviousAndNext({ slug }: Props) {
  const allDocs = getAllDocsMeta();

  const currentIndex = allDocs.findIndex(
    (doc) => doc.slug.join("/") === slug.join("/"),
  );

  const prev = allDocs[currentIndex - 1];
  const next = allDocs[currentIndex + 1];

  return (
    <div className="text-muted-foreground mt-16 flex w-full flex-col gap-4 border-t border-dashed border-gray-600 pt-8 text-sm md:flex-row md:justify-between">
      {prev ? (
        <Link
          href={`/docs/${prev.slug.join("/")}`}
          className="group inline-flex items-center gap-1 text-left hover:text-white"
        >
          <ArrowLeft className="h-4 w-4 opacity-70 transition group-hover:-translate-x-1" />
          {formatSlugToTitle(prev.title)}
        </Link>
      ) : (
        <div />
      )}

      {next ? (
        <Link
          href={`/docs/${next.slug.join("/")}`}
          className="group ml-auto inline-flex items-center gap-1 text-right hover:text-white"
        >
          {formatSlugToTitle(next.title)}
          <ArrowRight className="h-4 w-4 opacity-70 transition group-hover:translate-x-1" />
        </Link>
      ) : (
        <div />
      )}
    </div>
  );
}
