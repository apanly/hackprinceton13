// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_hist_t * o;
  smpl_t flow;
  smpl_t fhig;
  uint_t nelems;
} Py_hist;

static char Py_hist_doc[] = "hist object";

static PyObject *
Py_hist_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_hist *self;
  smpl_t flow = 0;
  smpl_t fhig = 0;
  uint_t nelems = 0;
  static char *kwlist[] = { "flow", "fhig", "nelems", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|ffI", kwlist,
          &flow, &fhig, &nelems)) {
    return NULL;
  }

  self = (Py_hist *) pytype->tp_alloc (pytype, 0);

  if (self == NULL) {
    return NULL;
  }

  self->flow = 0.;
  if (flow != 0.) {
    self->flow = flow;
  }

  self->fhig = 1.;
  if (fhig != 1.) {
    self->fhig = fhig;
  }

  self->nelems = 10;
  if (nelems > 0) {
    self->nelems = nelems;
  } else if (nelems < 0) {
    PyErr_SetString (PyExc_ValueError,
        "can not use negative value for nelems");
    return NULL;
  }

  return (PyObject *) self;
}

AUBIO_INIT(hist , self->flow, self->fhig, self->nelems)

AUBIO_DEL(hist)

/* function Py_hist_do */
static PyObject * 
Py_hist_do(Py_hist * self, PyObject * args)
{
  /* input vectors python prototypes */
  PyObject * input_obj;

  /* input vectors prototypes */
  fvec_t* input;


  if (!PyArg_ParseTuple (args, "O", &input_obj)) {
    return NULL;
  }


  /* input vectors parsing */
  input = PyAubio_ArrayToCFvec (input_obj);

  if (input == NULL) {
    return NULL;
  }

  
  


  /* compute _do function */
  aubio_hist_do (self->o, input);

  Py_RETURN_NONE;
}

AUBIO_MEMBERS_START(hist)
  {"flow", T_FLOAT, offsetof (Py_hist, flow), READONLY, ""},
  {"fhig", T_FLOAT, offsetof (Py_hist, fhig), READONLY, ""},
  {"nelems", T_INT, offsetof (Py_hist, nelems), READONLY, ""},
AUBIO_MEMBERS_STOP(hist)


static PyMethodDef Py_hist_methods[] = {
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(hist, "aubio.hist")
