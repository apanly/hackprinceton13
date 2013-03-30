// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_source_t * o;
  char_t* uri;
  uint_t samplerate;
  uint_t hop_size;
} Py_source;

static char Py_source_doc[] = "source object";

static PyObject *
Py_source_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_source *self;
  char_t* uri = NULL;
  uint_t samplerate = 0;
  uint_t hop_size = 0;
  static char *kwlist[] = { "uri", "samplerate", "hop_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|sII", kwlist,
          &uri, &samplerate, &hop_size)) {
    return NULL;
  }

  self = (Py_source *) pytype->tp_alloc (pytype, 0);

  if (self == NULL) {
    return NULL;
  }

  self->uri = "none";
  if (uri != NULL) {
    self->uri = uri;
  }

  self->samplerate = Py_aubio_default_samplerate;
  if (samplerate > 0) {
    self->samplerate = samplerate;
  } else if (samplerate < 0) {
    PyErr_SetString (PyExc_ValueError,
        "can not use negative value for samplerate");
    return NULL;
  }

  self->hop_size = Py_default_vector_length / 2;
  if (hop_size > 0) {
    self->hop_size = hop_size;
  } else if (hop_size < 0) {
    PyErr_SetString (PyExc_ValueError,
        "can not use negative value for hop_size");
    return NULL;
  }

  return (PyObject *) self;
}

AUBIO_INIT(source , self->uri, self->samplerate, self->hop_size)

AUBIO_DEL(source)

/* function Py_source_do */
static PyObject * 
Py_source_do(Py_source * self, PyObject * args)
{


  /* output vectors prototypes */
  fvec_t* read_to;
  uint_t read;





  
  /* creating output read_to as a new_fvec of length self->hop_size */
  read_to = new_fvec (self->hop_size);
  read = 0;


  /* compute _do function */
  aubio_source_do (self->o, read_to, &read);

  PyObject *outputs = PyList_New(0);
  PyList_Append( outputs, (PyObject *)PyAubio_CFvecToArray (read_to));
  PyList_Append( outputs, (PyObject *)PyInt_FromLong (read));
  return outputs;;
}

AUBIO_MEMBERS_START(source)
  {"uri", T_STRING, offsetof (Py_source, uri), READONLY, ""},
  {"samplerate", T_INT, offsetof (Py_source, samplerate), READONLY, ""},
  {"hop_size", T_INT, offsetof (Py_source, hop_size), READONLY, ""},
AUBIO_MEMBERS_STOP(source)


static PyObject *
Pyaubio_source_get_samplerate (Py_source *self, PyObject *unused)
{
  uint_t tmp = aubio_source_get_samplerate (self->o);
  return (PyObject *)PyInt_FromLong (tmp);
}

static PyObject *
Pyaubio_source_get_channels (Py_source *self, PyObject *unused)
{
  uint_t tmp = aubio_source_get_channels (self->o);
  return (PyObject *)PyInt_FromLong (tmp);
}

static PyMethodDef Py_source_methods[] = {
  {"get_samplerate", (PyCFunction) Pyaubio_source_get_samplerate,
    METH_NOARGS, ""},
  {"get_channels", (PyCFunction) Pyaubio_source_get_channels,
    METH_NOARGS, ""},
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(source, "aubio.source")
