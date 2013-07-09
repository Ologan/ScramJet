cdef extern from "../src/sjarray.h":
    ctypedef struct sj_array:
        pass

    ctypedef union sj_value:
        int i32

    sj_array *sj_create_array1( int type, size_t size )
    void sj_free_array( sj_array *array )
    void sj_sum_constant( sj_array *array, sj_value value )
    void sj_print_array( sj_array *array )