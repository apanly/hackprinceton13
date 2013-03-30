import sys
from math import log
from aubio import source, pitch

class GenericConverter(object):

  def __init__(self, win_s, hop_s):
    self.win_s = win_s
    self.hop_s = hop_s

  def _parse_(self, filename, samplerate):
    """
    concrete implementation of parse, to be overridden by subclasses
    """
    raise Exception("_parse unimplemented")

  def parse(self, filename, samplerate=60):
    """
    converts the filename to a representation of the music
    stored in filename

    @param filename the filename of the .wav file
    @param samplerate the sampling rate, in seconds
    """
    self._parse(filename, samplerate)

class SimpleConverter(GenericConverter):

  notes = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]
  _A4_ = 440 # Hz
  _A4Coord_ = 57
  steps_in_octave = 12

  class MusicalNote(object):
    def __init__(self, note, length):
      self.note = note
      self.length = length

    @classmethod
    def hertz_to_note(cls, hertz):
      """
      f_n = f_0 * (a)^n

      where f_0 = fixed frequency (A4 = 440 Hz)
      n = number of steps halfway from the fixed note
      f_n the frequency of the note n half steps away
      a = 2^(1/12)

      @return (note, octave) where note is the musical note and octave
              is the octave the musical note is in, as per scientific
              musical notation
      """
      steps_in_octave = SimpleConverter.steps_in_octave
      hertz = float(hertz)
      steps_away = steps_in_octave * log(hertz/SimpleConverter._A4_, 2)
      new_position = SimpleConverter._A4Coord_ + steps_away
      (index, octave) = (int(round(new_position % steps_in_octave)),
                         int(new_position / steps_in_octave))
      return SimpleConverter.notes[index], octave

  def __init__(self, win_s, hop_s):
    super(MyConvertDatShit, self).__init__(win_s, hop_s)

  def _parse_(self, filename, samplerate):
    s = source(filename, samplerate, self.hop_s)

    pitch_o = pitch("default", win_s, hop_s, samplerate)
    pitch_o.set_unit("midi")

    notes = []

    # total number of frames read
    total_frames = 0

    fixed_interval = total_frames / float(samplerate)
    while True:
      samples, read = s()
      pitch = pitch_o(samples)[0]
      note, octave = MusicalNote.hertz_to_note(pitch)

      notes += [SimpleConverter.MusicalNote(note + str(octave), fixed_interval)]

      if read < hop_s:
        break

    return notes
