#!/usr/bin/python

from singdatshit import *

def run_all_tests():
  test_hertz_to_note()

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

def main():
  run_all_tests()

if __name__ == "__main__":
  main()
