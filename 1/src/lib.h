void lib_bisort(void *, unsigned long, unsigned long, int (*compare)(void*, void*)); // binary-insertion sort main function
void lib_qsort_left_pivot(void *, unsigned long, int, int, int (*compare)(void*, void*)); // quick sort using a left pivot
void lib_qsort_mid_pivot(void *, unsigned long, int, int, int (*compare)(void*, void*)); // quick sort using a middle pivot
void lib_qsort_right_pivot(void *, unsigned long, int, int, int (*compare)(void*, void*)); // quick sort using a right pivot
void lib_qsort_random_pivot(void *, unsigned long, int, int, int (*compare)(void*, void*)); // quick sort using a random pivot
