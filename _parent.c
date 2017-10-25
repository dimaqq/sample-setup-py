#include <Python.h>

typedef struct {
  PyObject_HEAD
} PyParent;

static PyObject* parent_new(PyTypeObject* type, PyObject* args,
                            PyObject* kwargs) {
  PyParent* self = (PyParent*)type->tp_alloc(type, 0);
  printf("Created parent %ld\n", (long)self);
  return (PyObject*)self;
}

static PyTypeObject PyParent_Type = {
    PyVarObject_HEAD_INIT(NULL, 0) "_parent.Parent", /*tp_name*/
    sizeof(PyParent),                                /*tp_basicsize*/
    0,                                               /*tp_itemsize*/
    0,                                               /*tp_dealloc*/
    0,                                               /*tp_print*/
    0,                                               /*tp_getattr*/
    0,                                               /*tp_setattr*/
    0,                                               /*tp_reserved*/
    0,                                               /*tp_repr*/
    0,                                               /*tp_as_number*/
    0,                                               /*tp_as_sequence*/
    0,                                               /*tp_as_mapping*/
    0,                                               /*tp_hash*/
    0,                                               /*tp_call*/
    0,                                               /*tp_str*/
    0,                                               /*tp_getattro*/
    0,                                               /*tp_setattro*/
    0,                                               /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE | Py_TPFLAGS_HAVE_GC, /*tp_flags*/
    0,                                                             /*tp_doc*/
    0,          /*tp_traverse*/
    0,          /*tp_clear*/
    0,          /*tp_richcompare*/
    0,          /*tp_weaklistoffset*/
    0,          /*tp_iter*/
    0,          /*tp_iternext*/
    0,          /*tp_methods*/
    0,          /*tp_members*/
    0,          /*tp_getset*/
    0,          /*tp_base*/
    0,          /*tp_dict*/
    0,          /*tp_descr_get*/
    0,          /*tp_descr_set*/
    0,          /*tp_dictoffset*/
    0,          /*tp_init*/
    0,          /*tp_alloc*/
    parent_new, /*tp_new*/
};

static struct PyModuleDef _parent_module = {
    PyModuleDef_HEAD_INIT, "_parent", "", -1, NULL, NULL, NULL, NULL, NULL};

PyMODINIT_FUNC PyInit__parent(void) {
  PyObject* m = PyModule_Create(&_parent_module);
  if (PyType_Ready(&PyParent_Type) < 0) return NULL;

  PyObject* d;
  d = PyModule_GetDict(m);

  if (PyDict_SetItemString(d, "Parent", (PyObject*)&PyParent_Type) != 0)
    return NULL;
  return m;
}
