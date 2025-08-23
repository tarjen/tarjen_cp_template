// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!
#import "@preview/zebraw:0.5.5": *
#let fonts = (
  serif: (
    "Libertinus Serif",
    "Times New Roman",
    "Source Han Serif SC",
    "Source Han Serif",
    "Noto Serif CJK SC",
    "SimSun",
    "Songti SC",
    "STSongti",
  ),
  sans-serif: (
    "Libertinus Sans",
    "Arial",
    "Source Han Sans SC",
    "Source Han Sans",
    "Noto Sans CJK SC",
    "SimHei",
    "Heiti SC",
    "STHeiti",
  ),
  monospace: (
    "DejaVu Sans Mono",
    "Courier New",
    "Menlo",
    "IBM Plex Mono",
    "Source Han Sans HW SC",
    "Source Han Sans HW",
    "Noto Sans Mono CJK SC",
    "SimHei",
    "Heiti SC",
    "STHeiti",
  ),
)

#let template(
  title: "",
  team: "",
  school: "",
  authors: (),
  logo: none,
  header: none,
  preview: false,
  commit: none,
  body,
) = {
  set document(author: authors, title: title)
  set text(font: fonts.serif, lang: "zh", region: "cn")

  show math.equation: set text(weight: 400)
  show raw: set text(font: fonts.monospace, lang: "zh", region: "cn")

  show: zebraw-init.with(fast-preview: preview)
  show: zebraw.with(
    indentation: 2,
    inset: (top: 0.3em, bottom: 0.3em),
    hanging-indent: true,
    ..zebraw-themes.zebra,
  )
  set page(
    flipped: true, 
    footer: [
      #set text(fill: gray, size: 10pt)
       #grid(
        columns: (1fr, 1fr),
        align(left)[
          #if preview [
            #text(red)[*Preview Build*]
           ] else {
            "Production Build" + (if commit != none { " - Commit " + commit } else { "" })
          }
        ],
        align(right)[Last update: #datetime.today().display("[month repr:short]. [day], [year]")]
       )
    ]
  )
  v(0.6fr)
  if logo != none {
    align(right, image(logo, width: 30%))
  }
  v(9.6fr)

  text(3.5em, weight: 700, title)
  v(8fr)
  text(2.5em, weight: 700, team)
  v(4fr)
  text(2em, weight: 700, emph(school))
  pad(top: 0.7em, right: 20%, grid(
    columns: (1fr,) * calc.min(3, authors.len()),
    gutter: 1em,
    ..authors.map(author => align(start, strong(author))),
  ))
  // Main body.

  counter(page).update(0)
  set par(justify: true)
  set text(size: 7pt)
  set page(
    columns: 3,
    header: header,
    footer: none,
    margin: (
      left: 2.5em,
      right: 2.5em,
      top: 3em,
      bottom: 2em,
    ),
  )
  set columns(gutter: 0.75em)
  // align(center, text(2em, weight: 700, title))
  body
}

#let import_code(path, lang: none, ..args) = {
  if lang == none {
    // Guess the language from the file extension.
    lang = path.split(".").last()
  }
  raw(read(path).trim(), lang: lang, block: true, ..args)
}

