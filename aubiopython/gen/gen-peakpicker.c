// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_peakpicker_t * o;
} Py_peakpicker;

static char Py_peakpicker_doc[] = "peakpicker object";

static PyObject *
Py_peakpicker_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_peakpicker *self;

  self = (Py_peakpicker *) pytype->tp_alloc (pytype, 0);

  if (self == NULL) {
    return NULL;
  }

  return (PyObject *) self;
}

AUBIO_INIT(peakpicker )

AUBIO_DEL(peakpicker)

/* function Py_peakpicker_do */
static PyObject * 
Py_peakpicker_do(Py_peakpicker * self, PyObject * args)
{
  /* input vectors python prototypes */
  PyObject * in_obj;

  /* input vectors prototypes */
  fvec_t* in;
  /* output vectors prototypes */
  fvec_t* out;


  if (!PyArg_ParseTuple (args, "O", &in_obj)) {
    return NULL;
  }


  /* input vectors parsing */
  in = PyAubio_ArrayToCFvec (in_obj);

  if (in == NULL) {
    return NULL;
  }

  
  
  /* creating output out as a new_fvec of length 1 */
  out = new_fvec (1);


  /* compute _do function */
  aubio_peakpicker_do (self->o, in, out);

  return (PyObject *)PyAubio_CFvecToArray (out);
}

AUBIO_MEMBERS_START(peakpicker)
AUBIO_MEMBERS_STOP(peakpicker)


static PyObject *
Pyaubio_peakpicker_set_threshold (Py_peakpicker *self, PyObject *args)
{
  uint_t err = 0;

  smpl_t threshold;

  if (!PyArg_ParseTuple (args, "f", &threshold)) {
    return NULL;
  } 

  err = aubio_peakpicker_set_threshold (self->o, threshold);

  if (err > 0) {
    PyErr_SetString (PyExc_ValueError,
        "error running aubio_peakpicker_set_threshold");
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyObject *
Pyaubio_peakpicker_get_thresholded_input (Py_peakpicker *self, PyObject *unused)
{
  fvec_t* tmp = aubio_peakpicker_get_thresholded_input (self->o);
  return (PyObject *)PyAubio_CFvecToArray (tmp);
}

static PyObject *
Pyaubio_peakpicker_get_threshold (Py_peakpicker *self, PyObject *unused)
{
  smpl_t tmp = aubio_peakpicker_get_threshold (self->o);
  return (PyObject *)PyFloat_FromDouble (tmp);
}

static PyMethodDef Py_peakpicker_methods[] = {
  {"set_threshold", (PyCFunction) Pyaubio_peakpicker_set_threshold,
    METH_VARARGS, ""},
  {"get_thresholded_input", (PyCFunction) Pyaubio_peakpicker_get_thresholded_input,
    METH_NOARGS, ""},
  {"get_threshold", (PyCFunction) Pyaubio_peakpicker_get_threshold,
    METH_NOARGS, ""},
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(peakpicker, "aubio.peakpicker")
