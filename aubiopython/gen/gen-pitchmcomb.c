// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_pitchmcomb_t * o;
  uint_t buf_size;
  uint_t hop_size;
} Py_pitchmcomb;

static char Py_pitchmcomb_doc[] = "pitchmcomb object";

static PyObject *
Py_pitchmcomb_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_pitchmcomb *self;
  uint_t buf_size = 0;
  uint_t hop_size = 0;
  static char *kwlist[] = { "buf_size", "hop_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|II", kwlist,
          &buf_size, &hop_size)) {
    return NULL;
  }

  self = (Py_pitchmcomb *) pytype->tp_alloc (pytype, 0);

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

AUBIO_INIT(pitchmcomb , self->buf_size, self->hop_size)

AUBIO_DEL(pitchmcomb)

/* function Py_pitchmcomb_do */
static PyObject * 
Py_pitchmcomb_do(Py_pitchmcomb * self, PyObject * args)
{
  /* input vectors python prototypes */
  PyObject * in_fftgrain_obj;

  /* input vectors prototypes */
  cvec_t* in_fftgrain;
  /* output vectors prototypes */
  fvec_t* out_cands;


  if (!PyArg_ParseTuple (args, "O", &in_fftgrain_obj)) {
    return NULL;
  }


  /* input vectors parsing */
  in_fftgrain = PyAubio_ArrayToCCvec (in_fftgrain_obj);

  if (in_fftgrain == NULL) {
    return NULL;
  }

  
  
  /* creating output out_cands as a new_fvec of length 1 */
  out_cands = new_fvec (1);


  /* compute _do function */
  aubio_pitchmcomb_do (self->o, in_fftgrain, out_cands);

  return (PyObject *)PyAubio_CFvecToArray (out_cands);
}

AUBIO_MEMBERS_START(pitchmcomb)
  {"buf_size", T_INT, offsetof (Py_pitchmcomb, buf_size), READONLY, ""},
  {"hop_size", T_INT, offsetof (Py_pitchmcomb, hop_size), READONLY, ""},
AUBIO_MEMBERS_STOP(pitchmcomb)


static PyMethodDef Py_pitchmcomb_methods[] = {
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(pitchmcomb, "aubio.pitchmcomb")
