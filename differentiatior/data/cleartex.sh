#!/bin/sh
outputdir=$2
texname=$(basename $1)

outputpath="$2/$texname"

pdflatex -output-directory=$2 $1 #> /dev/null
rm "$outputpath".aux
rm "$outputpath".log
xdg-open "$outputpath".pdf