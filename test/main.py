#!/usr/bin/python

from singdatshit import *

input_dir = "input"

def run_all_tests():
#   test_hertz_to_note()
#   test_parser_piano_wav()
  test_to_pdf()

def test_hertz_to_note():
  hertz_to_note = SimpleConverter.MusicalNote.hertz_to_note
  assert(hertz_to_note(2793.83) == ("F", 7))
  assert(hertz_to_note(2217.46) == ("C#", 7))
  assert(hertz_to_note(932.328) == ("A#", 5))
  assert(hertz_to_note(880) == ("A", 5))
  assert(hertz_to_note(622.254) == ("D#", 5))
  assert(hertz_to_note(466.164) == ("A#", 4))
  assert(hertz_to_note(440) == ("A", 4))
  assert(hertz_to_note(415.305) == ("G#", 4))
  assert(hertz_to_note(130.813) == ("C", 3))
  assert(hertz_to_note(123.471) == ("B", 2))
  assert(hertz_to_note(41.2034) == ("E", 1))

def test_parser_piano_wav():
  converter = SimpleConverter(1024, 1024)
#   print converter.parse("%s/810orig24to36.wav" % input_dir)
  files = [
    # "A220-oboe.wav", "A440-oboe.wav", "A880-oboe.wav",
#     "A1760-oboe.wav", "Canon-violin.wav", "Canon-violin-rerecord.wav",
#     "Canon-violin-rerecord-bgnoise.wav", "mark-test1.wav",
#     "mark-newworld.wav",
    "mark-bringhimhome.wav"
    ]
  for file in files:
    print file
    for n in converter.parse("%s/%s" % (input_dir, file)):
      print n #if n != None else None
#   for n in converter.parse("%s/A880.wav" % input_dir):
#     print n.note if n != None else None

def test_to_pdf():
  converter = SimpleConverter(1024, 1024)
  filename = "Canon-violin"
  parser_output = converter.parse("%s/%s.wav" % (input_dir, filename))
  text = SimpleConverter.to_pdf(parser_output)
  f = open("in/%s.lytex" % filename, "w")
  f.write(text)
  f.close()
  import subprocess
  subprocess.call("lilypond-book --output=out --pdf in/%s.lytex" % filename,
                  shell = True)
  subprocess.call("cd out; pdflatex %s" % filename, shell = True)

def main():
  run_all_tests()

if __name__ == "__main__":
  main()
