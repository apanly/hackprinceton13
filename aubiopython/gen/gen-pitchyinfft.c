// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_pitchyinfft_t * o;
  uint_t buf_size;
} Py_pitchyinfft;

static char Py_pitchyinfft_doc[] = "pitchyinfft object";

static PyObject *
Py_pitchyinfft_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_pitchyinfft *self;
  uint_t buf_size = 0;
  static char *kwlist[] = { "buf_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|I", kwlist,
          &buf_size)) {
    return NULL;
  }

  self = (Py_pitchyinfft *) pytype->tp_alloc (pytype, 0);

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

AUBIO_INIT(pitchyinfft , self->buf_size)

AUBIO_DEL(pitchyinfft)

/* function Py_pitchyinfft_do */
static PyObject * 
Py_pitchyinfft_do(Py_pitchyinfft * self, PyObject * args)
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
  aubio_pitchyinfft_do (self->o, samples_in, cands_out);

  return (PyObject *)PyAubio_CFvecToArray (cands_out);
}

AUBIO_MEMBERS_START(pitchyinfft)
  {"buf_size", T_INT, offsetof (Py_pitchyinfft, buf_size), READONLY, ""},
AUBIO_MEMBERS_STOP(pitchyinfft)


static PyObject *
Pyaubio_pitchyinfft_set_tolerance (Py_pitchyinfft *self, PyObject *args)
{
  uint_t err = 0;

  smpl_t tol;

  if (!PyArg_ParseTuple (args, "f", &tol)) {
    return NULL;
  } 

  err = aubio_pitchyinfft_set_tolerance (self->o, tol);

  if (err > 0) {
    PyErr_SetString (PyExc_ValueError,
        "error running aubio_pitchyinfft_set_tolerance");
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyObject *
Pyaubio_pitchyinfft_get_tolerance (Py_pitchyinfft *self, PyObject *unused)
{
  smpl_t tmp = aubio_pitchyinfft_get_tolerance (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyObject *
Pyaubio_pitchyinfft_get_confidence (Py_pitchyinfft *self, PyObject *unused)
{
  smpl_t tmp = aubio_pitchyinfft_get_confidence (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyMethodDef Py_pitchyinfft_methods[] = {
  {"set_tolerance", (PyCFunction) Pyaubio_pitchyinfft_set_tolerance,
    METH_VARARGS, ""},
  {"get_tolerance", (PyCFunction) Pyaubio_pitchyinfft_get_tolerance,
    METH_NOARGS, ""},
  {"get_confidence", (PyCFunction) Pyaubio_pitchyinfft_get_confidence,
    METH_NOARGS, ""},
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(pitchyinfft, "aubio.pitchyinfft")
