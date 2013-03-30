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

  notes = ["C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"]
  notenames = ["c", "cis", "d", "dis", "e", "f", "fis", "g", "gis", "a", "ais", "b"]

  _A4_ = 440 # Hz
  _A4Coord_ = 57
  steps_in_octave = 12

  class MusicalNote(object):
    def __init__(self, note, length):
      self.note = note
      self.length = length

    def __repr__(self):
      return "MusicalNote(%r, %r)" % (self.note, self.length)

    @classmethod
    def coord_to_note(cls, coord):
      steps_in_octave = SimpleConverter.steps_in_octave
      coord = int(round(coord))
      (index, octave) = (coord % steps_in_octave,
                         coord / steps_in_octave)
      return SimpleConverter.notes[index], octave

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
      from math import log
      if 0.0 == hertz:
        return (None, None)
      steps_in_octave = SimpleConverter.steps_in_octave
      hertz = float(hertz)
      steps_away = int(round(steps_in_octave * log(hertz/SimpleConverter._A4_, 2)))
      new_position = SimpleConverter._A4Coord_ + steps_away
      (index, octave) = (new_position % steps_in_octave,
                         new_position / steps_in_octave)
      return SimpleConverter.notes[index], octave

    @classmethod
    def note_to_hilbert(cls, musical_note):
      if note == None: return None
      assert(type(note) == MusicalNote)

      octave = int(musical_note.note[-1])
      note = musical_note.note[:-1]
      index = list.index(MusicalNote.notes, note)

      # Unimplemented feature
      # return MusicalNote.notenames + str(musical_note.length)
#       return MusicalNote.notenames + "'" * octave + str(4)
      return MusicalNote.notenames + "'" * octave + str(musical_note.length)

    @classmethod
    def get_durations(cls, notes, endtime):
      durations = []
      for i in xrange(0, len(notes) - 1):
        (note, octave, start) = notes[i]
        (snote, soctave, sstart) = notes[i + 1]
        durations += [sstart - start]
      (note, octave, start) = notes[-1]
      durations += [endtime - start]
      return durations

    @classmethod
    def clamp(cls, x, lo, hi):
      return min(max(x, lo), hi)

    @classmethod
    def get_mul(cls, eighth_note, duration):
      from math import log
      mul = SimpleConverter.MusicalNote.clamp(2 ** round(log(duration,
                                                             eighth_note)),
                                              1, 8)
      return mul

    @classmethod
    def get_types(cls, durations):
      sorted_durations = sorted(durations)
      mean_errors = []
      for eighth_note in sorted_durations:
        errors = []
        for duration in sorted_durations:
          mul = SimpleConverter.MusicalNote.get_mul(eighth_note, duration)
          errors += [abs(duration - eighth_note * mul)]
        mean_errors += [sum(errors) / len(errors)]
      eighth_note = sorted_durations[mean_errors.index(min(mean_errors))]
      types = []
      for duration in sorted_durations:
        mul = SimpleConverter.MusicalNote.get_mul(eighth_note, duration)
        types += [int(round(8 / mul))]
      return (types, eighth_note)


  def __init__(self, win_s, hop_s):
    super(SimpleConverter, self).__init__(win_s, hop_s)

  def _parse_(self, filename, samplerate):
    from aubio import source, pitch, tempo
    s = source(filename, samplerate, self.hop_s)

    pitch_o = pitch("default", self.win_s, self.hop_s, samplerate)
    pitch_o.set_unit("midi")

    tempo_win_s = self.win_s / 2
    tempo_hop_s = self.hop_s / 2
    s2 = source(filename, samplerate, tempo_hop_s)

    tempo_o = tempo("default", tempo_win_s, tempo_hop_s, samplerate)
    delay = 4. * tempo_hop_s

    notes = []

    # total number of frames read
    total_frames = 0

    samplerate = float(samplerate)
    previous_samples = []

    read = self.hop_s
    while read >= self.hop_s:
      samples, read = s()
      pitch = pitch_o(samples)[0]

      # go through the finer steps for beat detection
      for iter in xrange(self.hop_s/tempo_hop_s):
        samples2, read2 = s2()

        # if no more stuff to read
        if read < tempo_hop_s:
          break

        # hopefully this work
        is_beat = tempo_o(samples2)

        # BUG: doesn't work if sample starts on beat FIRST
        if is_beat:
          this_beat = int(total_frames - delay + is_beat[0] * tempo_hop_s)
          average = sum(previous_samples)/len(previous_samples)
          note, octave = SimpleConverter.MusicalNote.coord_to_note(average)
          notes += [(note, octave, total_frames/samplerate)]
          previous_samples = []
          break

      # don't want to add otherwise because higher chance at transition zone
#       elif 0 != pitch:
      if abs(pitch) > 0.1:
        previous_samples += [pitch]

      total_frames += read

    durations = \
        SimpleConverter.MusicalNote.get_durations(notes,
                                                  total_frames / samplerate)
    (types, eighth_note) = SimpleConverter.MusicalNote.get_types(durations)

    notes = [SimpleConverter.MusicalNote(notes[i][0] + str(notes[i][1]),
                                         types[i]) \
             for i in xrange(len(notes))]

    return notes

  @classmethod
  def to_pdf(cls, notes):
    """
    warning: does not check whether everything is a MusicalNote
    """
    notes_notation = [MusicalNote.note_to_hilbert(note) for note in notes]
    doc = \
"""
\documentclass{article}
\begin{document}
\begin{lilypond}
{
""" + " ".join(notes_notation) + \
"""
}
\end{lilypond}
\end{document}
"""

    return doc
