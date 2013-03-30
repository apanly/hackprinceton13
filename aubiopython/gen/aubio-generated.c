// generated list of objects created with generator.py

#include "aubio-generated.h"

int generated_types_ready (void)
{
  return (
  PyType_Ready (&Py_mfccType) < 0
     ||  PyType_Ready (&Py_specdescType) < 0
     ||  PyType_Ready (&Py_tssType) < 0
     ||  PyType_Ready (&Py_pitchType) < 0
     ||  PyType_Ready (&Py_onsetType) < 0
     ||  PyType_Ready (&Py_tempoType) < 0
     ||  PyType_Ready (&Py_sourceType) < 0
     ||  PyType_Ready (&Py_sinkType) < 0
     ||  PyType_Ready (&Py_samplerType) < 0
     ||  PyType_Ready (&Py_peakpickerType) < 0
     ||  PyType_Ready (&Py_pitchmcombType) < 0
     ||  PyType_Ready (&Py_pitchyinType) < 0
     ||  PyType_Ready (&Py_pitchyinfftType) < 0
     ||  PyType_Ready (&Py_pitchschmittType) < 0
     ||  PyType_Ready (&Py_pitchfcombType) < 0
     ||  PyType_Ready (&Py_beattrackingType) < 0
     ||  PyType_Ready (&Py_scaleType) < 0
     ||  PyType_Ready (&Py_histType) < 0);
}

void add_generated_objects ( PyObject *m )
{
  Py_INCREF (&Py_mfccType);
  PyModule_AddObject (m, "mfcc", (PyObject *) & Py_mfccType);
  Py_INCREF (&Py_specdescType);
  PyModule_AddObject (m, "specdesc", (PyObject *) & Py_specdescType);
  Py_INCREF (&Py_tssType);
  PyModule_AddObject (m, "tss", (PyObject *) & Py_tssType);
  Py_INCREF (&Py_pitchType);
  PyModule_AddObject (m, "pitch", (PyObject *) & Py_pitchType);
  Py_INCREF (&Py_onsetType);
  PyModule_AddObject (m, "onset", (PyObject *) & Py_onsetType);
  Py_INCREF (&Py_tempoType);
  PyModule_AddObject (m, "tempo", (PyObject *) & Py_tempoType);
  Py_INCREF (&Py_sourceType);
  PyModule_AddObject (m, "source", (PyObject *) & Py_sourceType);
  Py_INCREF (&Py_sinkType);
  PyModule_AddObject (m, "sink", (PyObject *) & Py_sinkType);
  Py_INCREF (&Py_samplerType);
  PyModule_AddObject (m, "sampler", (PyObject *) & Py_samplerType);
  Py_INCREF (&Py_peakpickerType);
  PyModule_AddObject (m, "peakpicker", (PyObject *) & Py_peakpickerType);
  Py_INCREF (&Py_pitchmcombType);
  PyModule_AddObject (m, "pitchmcomb", (PyObject *) & Py_pitchmcombType);
  Py_INCREF (&Py_pitchyinType);
  PyModule_AddObject (m, "pitchyin", (PyObject *) & Py_pitchyinType);
  Py_INCREF (&Py_pitchyinfftType);
  PyModule_AddObject (m, "pitchyinfft", (PyObject *) & Py_pitchyinfftType);
  Py_INCREF (&Py_pitchschmittType);
  PyModule_AddObject (m, "pitchschmitt", (PyObject *) & Py_pitchschmittType);
  Py_INCREF (&Py_pitchfcombType);
  PyModule_AddObject (m, "pitchfcomb", (PyObject *) & Py_pitchfcombType);
  Py_INCREF (&Py_beattrackingType);
  PyModule_AddObject (m, "beattracking", (PyObject *) & Py_beattrackingType);
  Py_INCREF (&Py_scaleType);
  PyModule_AddObject (m, "scale", (PyObject *) & Py_scaleType);
  Py_INCREF (&Py_histType);
  PyModule_AddObject (m, "hist", (PyObject *) & Py_histType);
}