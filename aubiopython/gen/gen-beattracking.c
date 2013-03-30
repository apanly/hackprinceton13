// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_beattracking_t * o;
  uint_t hop_size;
} Py_beattracking;

static char Py_beattracking_doc[] = "beattracking object";

static PyObject *
Py_beattracking_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_beattracking *self;
  uint_t hop_size = 0;
  static char *kwlist[] = { "hop_size", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|I", kwlist,
          &hop_size)) {
    return NULL;
  }

  self = (Py_beattracking *) pytype->tp_alloc (pytype, 0);

  if (self == NULL) {
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

AUBIO_INIT(beattracking , self->hop_size)

AUBIO_DEL(beattracking)

/* function Py_beattracking_do */
static PyObject * 
Py_beattracking_do(Py_beattracking * self, PyObject * args)
{
  /* input vectors python prototypes */
  PyObject * dfframes_obj;

  /* input vectors prototypes */
  fvec_t* dfframes;
  /* output vectors prototypes */
  fvec_t* out;


  if (!PyArg_ParseTuple (args, "O", &dfframes_obj)) {
    return NULL;
  }


  /* input vectors parsing */
  dfframes = PyAubio_ArrayToCFvec (dfframes_obj);

  if (dfframes == NULL) {
    return NULL;
  }

  
  
  /* creating output out as a new_fvec of length self->hop_size */
  out = new_fvec (self->hop_size);


  /* compute _do function */
  aubio_beattracking_do (self->o, dfframes, out);

  return (PyObject *)PyAubio_CFvecToArray (out);
}

AUBIO_MEMBERS_START(beattracking)
  {"hop_size", T_INT, offsetof (Py_beattracking, hop_size), READONLY, ""},
AUBIO_MEMBERS_STOP(beattracking)


static PyObject *
Pyaubio_beattracking_get_bpm (Py_beattracking *self, PyObject *unused)
{
  smpl_t tmp = aubio_beattracking_get_bpm (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyObject *
Pyaubio_beattracking_get_confidence (Py_beattracking *self, PyObject *unused)
{
  smpl_t tmp = aubio_beattracking_get_confidence (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyMethodDef Py_beattracking_methods[] = {
  {"get_bpm", (PyCFunction) Pyaubio_beattracking_get_bpm,
    METH_NOARGS, ""},
  {"get_confidence", (PyCFunction) Pyaubio_beattracking_get_confidence,
    METH_NOARGS, ""},
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(beattracking, "aubio.beattracking")
