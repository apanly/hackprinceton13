// WARNING: this file is generated, DO NOT EDIT

// WARNING: if you haven't read the first line yet, please do so
#include "aubiowraphell.h"

typedef struct
{
  PyObject_HEAD
  aubio_scale_t * o;
  smpl_t flow;
  smpl_t fhig;
  smpl_t ilow;
  smpl_t ihig;
} Py_scale;

static char Py_scale_doc[] = "scale object";

static PyObject *
Py_scale_new (PyTypeObject * pytype, PyObject * args, PyObject * kwds)
{
  Py_scale *self;
  smpl_t flow = 0;
  smpl_t fhig = 0;
  smpl_t ilow = 0;
  smpl_t ihig = 0;
  static char *kwlist[] = { "flow", "fhig", "ilow", "ihig", NULL };

  if (!PyArg_ParseTupleAndKeywords (args, kwds, "|ffff", kwlist,
          &flow, &fhig, &ilow, &ihig)) {
    return NULL;
  }

  self = (Py_scale *) pytype->tp_alloc (pytype, 0);

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

  self->ilow = 0.;
  if (ilow != 0.) {
    self->ilow = ilow;
  }

  self->ihig = 1.;
  if (ihig != 1.) {
    self->ihig = ihig;
  }

  return (PyObject *) self;
}

AUBIO_INIT(scale , self->flow, self->fhig, self->ilow, self->ihig)

AUBIO_DEL(scale)

/* function Py_scale_do */
static PyObject * 
Py_scale_do(Py_scale * self, PyObject * args)
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
  aubio_scale_do (self->o, input);

  Py_RETURN_NONE;
}

AUBIO_MEMBERS_START(scale)
  {"flow", T_FLOAT, offsetof (Py_scale, flow), READONLY, ""},
  {"fhig", T_FLOAT, offsetof (Py_scale, fhig), READONLY, ""},
  {"ilow", T_FLOAT, offsetof (Py_scale, ilow), READONLY, ""},
  {"ihig", T_FLOAT, offsetof (Py_scale, ihig), READONLY, ""},
AUBIO_MEMBERS_STOP(scale)


static PyObject *
Pyaubio_scale_set_limits (Py_scale *self, PyObject *args)
{
  uint_t err = 0;

  smpl_t ilow;
smpl_t ihig;
smpl_t olow;
smpl_t ohig;

  if (!PyArg_ParseTuple (args, "ffff", &ilow, &ihig, &olow, &ohig)) {
    return NULL;
  } 

  err = aubio_scale_set_limits (self->o, ilow,ihig,olow,ohig);

  if (err > 0) {
    PyErr_SetString (PyExc_ValueError,
        "error running aubio_scale_set_limits");
    return NULL;
  }
  Py_RETURN_NONE;
}

static PyMethodDef Py_scale_methods[] = {
  {"set_limits", (PyCFunction) Pyaubio_scale_set_limits,
    METH_VARARGS, ""},
  {NULL} /* sentinel */
};

AUBIO_TYPEOBJECT(scale, "aubio.scale")
