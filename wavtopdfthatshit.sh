#!/usr/bin/python

import sys
from singdatshit import *

converter = SimpleConverter(1024, 1024)
if len(sys.argv) != 2:
    sys.exit(-1)

filename = sys.argv[1]

parser_output = converter.parse("input/%s.wav" % (filename))
text = SimpleConverter.to_pdf(parser_output)
f = open("in/%s.lytex" % filename, "w")
f.write(text)
f.close()
import subprocess
subprocess.call("lilypond-book --output=out --pdf in/%s.lytex" % filename,
                shell = True)
subprocess.call("cd out; pdflatex %s" % filename, shell = True)
subprocess.call("convert out/%s.pdf out/%s.png" % (filename, filename), shell = True)

