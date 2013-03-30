import sys
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

  def parse(self, filename, samplerate=44100):
    """
    converts the filename to a representation of the music
    stored in filename
    
    @param filename the filename of the .wav file
    @param samplerate the sampling rate, in seconds
    """
    return self._parse_(filename, samplerate)

class SimpleConverter(GenericConverter):

  #duration = { 1 : 
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
      steps_away = int(round(steps_in_octave * log(hertz/SimpleConverter._A4_)))
      new_position = SimpleConverter._A4Coord_ + steps_away
      (index, octave) = new_position % steps_in_octave, new_position / steps_in_octave
      return SimpleConverter.notes[index], octave

    def __repr__(self):
      return "MusicalNote(%r, %r)" % (self.note, self.length)
  
  def __init__(self, win_s, hop_s):
    super(MyConvertDatShit, self).__init__(win_s, hop_s)

  def _parse_(self, filename, samplerate):
    s = source(filename, samplerate, self.hop_s)
    
    pitch_o = pitch("default", self.win_s, self.hop_s, samplerate)
    pitch_o.set_unit("midi")

    tempo_o = tempo("default", self.win_s, self.hop_s, samplerate)
    delay = 4. * self.hop_s

    notes = []

    # total number of frames read
    total_frames = 0

    samplerate = float(samplerate)
    previous_samples = []

    while read < hop_s:
      samples, read = s()
      pitch = pitch_o(samples)[0]
      is_beat = tempo_o(samples)

      # BUG: doesn't work if sample starts on beat FIRST
      if is_beat:
        this_beat = int(total_frames - delay + is_beat[0] * hop_s)
        average = sum(previous_samples)/len(previous_samples)
        note, octave = SimpleConverter.MusicalNote.hertz_to_note(average)
        notes += [(note, octave, total_frames/samplerate)]
        previous_samples = []

      # don't want to add otherwise because higher chance at transition zone
      else:
        previous_samples += [pitch]

      total_frames += read

    notes = [SimpleConverter.MusicalNote(note[0] + str(note[1]), note[2]) \
             for note in notes]

    return notes
