// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_pitchschmitt_t * o;
  uint_t buf_size;
} Py_pitchschmitt;

static char Py_pitchschmitt_doc[] = "pitchschmitt object";

static PyObject *
Py_pitchschmitt_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_pitchschmitt *self;
  uint_t buf_size = 0;
  static char *kwlist[] = { "buf_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|I", kwlist,
          &buf_size)) {
    return NULL;
  }

  self = (Py_pitchschmitt *) pytype->tp_alloc (pytype, 0);

  if (self == NULL) {
    return NULL;
  }

  self->buf_size = Py_default_vector_length;
  if (buf_size > 0) {
    self->buf_size = buf_size;
  } else if (buf_size < 0) {
    PyErr_SetString (PyExc_ValueError,
        "can not use negative value for buf_size");
    return NULL;
  }

  return (PyObject *) self;
}

AUBIO_INIT(pitchschmitt , self->buf_size)

AUBIO_DEL(pitchschmitt)

/* function Py_pitchschmitt_do */
static PyObject * 
Py_pitchschmitt_do(Py_pitchschmitt * self, PyObject * args)
{
  /* input vectors python prototypes */
  PyObject * samples_in_obj;

  /* input vectors prototypes */
  fvec_t* samples_in;
  /* output vectors prototypes */
  fvec_t* cands_out;


  if (!PyArg_ParseTuple (args, "O", &samples_in_obj)) {
    return NULL;
  }


  /* input vectors parsing */
  samples_in = PyAubio_ArrayToCFvec (samples_in_obj);

  if (samples_in == NULL) {
    return NULL;
  }

  
  
  /* creating output cands_out as a new_fvec of length 1 */
  cands_out = new_fvec (1);


  /* compute _do function */
  aubio_pitchschmitt_do (self->o, samples_in, cands_out);

  return (PyObject *)PyAubio_CFvecToArray (cands_out);
}

AUBIO_MEMBERS_START(pitchschmitt)
  {"buf_size", T_INT, offsetof (Py_pitchschmitt, buf_size), READONLY, ""},
AUBIO_MEMBERS_STOP(pitchschmitt)


static PyMethodDef Py_pitchschmitt_methods[] = {
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(pitchschmitt, "aubio.pitchschmitt")
