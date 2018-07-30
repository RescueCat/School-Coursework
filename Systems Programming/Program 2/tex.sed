#!/bin/sed -f

#these first
s/\\/\\verb+\\+/g
s/%/\\%/g
s/\^/\\^/g
s/--/-\\hspace{.01cm}-/g

#these last
1s/^/\\documentstyle[11pt]{article}\n\\begin{document} \n\\begin{center}{\\bf \n/
2s/$/} \\end{center}\n\\begin{description} \n/
$s/$/\n\\end{description}/
/^[A-Z]/ s/[A-Z][A-Z]*/\\item[&] \\hfill \\\\ /
/^       [-+]/ s/$/ \\\\/
