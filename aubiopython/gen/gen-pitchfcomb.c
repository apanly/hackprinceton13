// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_pitchfcomb_t * o;
  uint_t buf_size;
  uint_t hop_size;
} Py_pitchfcomb;

static char Py_pitchfcomb_doc[] = "pitchfcomb object";

static PyObject *
Py_pitchfcomb_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_pitchfcomb *self;
  uint_t buf_size = 0;
  uint_t hop_size = 0;
  static char *kwlist[] = { "buf_size", "hop_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|II", kwlist,
          &buf_size, &hop_size)) {
    return NULL;
  }

  self = (Py_pitchfcomb *) pytype->tp_alloc (pytype, 0);

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

AUBIO_INIT(pitchfcomb , self->buf_size, self->hop_size)

AUBIO_DEL(pitchfcomb)

/* function Py_pitchfcomb_do */
static PyObject * 
Py_pitchfcomb_do(Py_pitchfcomb * self, PyObject * args)
{
  /* input vectors python prototypes */
  PyObject * input_obj;

  /* input vectors prototypes */
  fvec_t* input;
  /* output vectors prototypes */
  fvec_t* output;


  if (!PyArg_ParseTuple (args, "O", &input_obj)) {
    return NULL;
  }


  /* input vectors parsing */
  input = PyAubio_ArrayToCFvec (input_obj);

  if (input == NULL) {
    return NULL;
  }

  
  
  /* creating output output as a new_fvec of length 1 */
  output = new_fvec (1);


  /* compute _do function */
  aubio_pitchfcomb_do (self->o, input, output);

  return (PyObject *)PyAubio_CFvecToArray (output);
}

AUBIO_MEMBERS_START(pitchfcomb)
  {"buf_size", T_INT, offsetof (Py_pitchfcomb, buf_size), READONLY, ""},
  {"hop_size", T_INT, offsetof (Py_pitchfcomb, hop_size), READONLY, ""},
AUBIO_MEMBERS_STOP(pitchfcomb)


static PyMethodDef Py_pitchfcomb_methods[] = {
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(pitchfcomb, "aubio.pitchfcomb")
