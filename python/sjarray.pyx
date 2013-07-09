cimport csjarray

cdef class SJArray:
    cdef csjarray.sj_array* _array

    def __cinit__(self, int type, int size):
        self._array = csjarray.sj_create_array1(type, size)

    def __dealloc__(self):
        if self._array is not NULL:
            csjarray.sj_free_array(self._array)

    def show(self):
        csjarray.sj_print_array(self._array)

    def sum(self, int val):
        cdef csjarray.sj_value value
        value.i32 = val
        csjarray.sj_sum_constant(self._array, value)