// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_pitchyin_t * o;
  uint_t buf_size;
} Py_pitchyin;

static char Py_pitchyin_doc[] = "pitchyin object";

static PyObject *
Py_pitchyin_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_pitchyin *self;
  uint_t buf_size = 0;
  static char *kwlist[] = { "buf_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|I", kwlist,
          &buf_size)) {
    return NULL;
  }

  self = (Py_pitchyin *) pytype->tp_alloc (pytype, 0);

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

AUBIO_INIT(pitchyin , self->buf_size)

AUBIO_DEL(pitchyin)

/* function Py_pitchyin_do */
static PyObject * 
Py_pitchyin_do(Py_pitchyin * self, PyObject * args)
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
  aubio_pitchyin_do (self->o, samples_in, cands_out);

  return (PyObject *)PyAubio_CFvecToArray (cands_out);
}

AUBIO_MEMBERS_START(pitchyin)
  {"buf_size", T_INT, offsetof (Py_pitchyin, buf_size), READONLY, ""},
AUBIO_MEMBERS_STOP(pitchyin)


static PyObject *
Pyaubio_pitchyin_set_tolerance (Py_pitchyin *self, PyObject *args)
{
  uint_t err = 0;

  smpl_t tol;

  if (!PyArg_ParseTuple (args, "f", &tol)) {
    return NULL;
  } 

  err = aubio_pitchyin_set_tolerance (self->o, tol);

  if (err > 0) {
    PyErr_SetString (PyExc_ValueError,
        "error running aubio_pitchyin_set_tolerance");
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyObject *
Pyaubio_pitchyin_get_tolerance (Py_pitchyin *self, PyObject *unused)
{
  smpl_t tmp = aubio_pitchyin_get_tolerance (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyObject *
Pyaubio_pitchyin_get_confidence (Py_pitchyin *self, PyObject *unused)
{
  smpl_t tmp = aubio_pitchyin_get_confidence (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyMethodDef Py_pitchyin_methods[] = {
  {"set_tolerance", (PyCFunction) Pyaubio_pitchyin_set_tolerance,
    METH_VARARGS, ""},
  {"get_tolerance", (PyCFunction) Pyaubio_pitchyin_get_tolerance,
    METH_NOARGS, ""},
  {"get_confidence", (PyCFunction) Pyaubio_pitchyin_get_confidence,
    METH_NOARGS, ""},
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(pitchyin, "aubio.pitchyin")
