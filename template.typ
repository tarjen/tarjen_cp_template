// The project function defines how your document looks.
// It takes your content and some metadata and formats it.
// Go ahead and customize it to your liking!

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

#let project(
  title: "",
  authors: (),
  logo: none,
  twoside: false,
  body,
) = {
  // Set the document's basic properties.
  set document(author: authors, title: title)
  set text(font: fonts.serif, lang: "zh", region: "cn")
  set page(margin: if twoside {
    (inside: 2.8cm, outside: 2.5cm)
  } else {
    auto
  })
  show math.equation: set text(weight: 400)

  // Title page.
  // The page can contain a logo if you pass one with `logo: "logo.png"`.
  v(0.6fr)
  if logo != none {
    align(right, image(logo, width: 60%))
  }
  v(9.6fr)

  text(2em, weight: 700, title)

  // Author information.
  pad(top: 0.7em, right: 20%, grid(
    columns: (1fr,) * calc.min(3, authors.len()),
    gutter: 1em,
    ..authors.map(author => align(start, strong(author))),
  ))

  v(2.4fr)
  pagebreak(weak: true, to: if twoside {
    "odd"
  })


  // Table of contents.
  set page(numbering: "I", number-align: center)
  counter(page).update(1)
  outline(depth: 3, indent: 2em)
  pagebreak(weak: true, to: if twoside {
    "odd"
  })


  // Main body.
  set par(justify: true)

  set page(numbering: "1", number-align: center)
  counter(page).update(1)
  body
}


#let wf_trd(
  title: "",
  authors: (),
  logo: none,
  header: none,
  body,
) = {
  set document(author: authors, title: title)
  set text(font: fonts.serif, lang: "zh", region: "cn")

  show math.equation: set text(weight: 400)

  set page(flipped: true, margin: (
    left: 1.5cm,
    right: 0.5cm,
    top: 0.5cm,
    bottom: 0.5cm,
  ))
  v(0.6fr)
  if logo != none {
    align(right, image(logo, width: 30%))
  }
  v(9.6fr)

  text(2em, weight: 700, title)
  pad(top: 0.7em, right: 20%, grid(
    columns: (1fr,) * calc.min(3, authors.len()),
    gutter: 1em,
    ..authors.map(author => align(start, strong(author))),
  ))
  // Main body.

  counter(page).update(0)
  set par(justify: true)
  set text(size: 8pt)
  set page(
    columns: 3,
    header: header,
  )
  set columns(gutter: 10pt)

  align(center, text(2em, weight: 700, title))
  outline(depth: 1, indent: 2em)
  body
}


#let import_code(path, lang: none, ..args) = {
  show raw.where(block: true): code => {
    show raw.line: line => {
      box(stack(
        dir: ltr,
        box(width: 0em, align(right, text(fill: gray)[#line.number])),
        h(1em),
        line.body,
      ))
    }
    code
  }
  if lang == none {
    // Guess the language from the file extension.
    lang = path.split(".").last()
  }
  raw(read(path), lang: lang, block: true, ..args)
}

