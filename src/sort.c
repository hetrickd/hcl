static inline void swap(int* a, int* b) {
	int t = *a;
	*a = *b;
	*b = t;
}

// assumes 2-6 elements, simplest possible sort
void sort(int* arr, int n) {
	if (arr[0] > arr[1]) swap(&arr[0], &arr[1]);
	if (n == 2) return;

	if (arr[1] > arr[2]) swap(&arr[1], &arr[2]);
	if (arr[0] > arr[1]) swap(&arr[0], &arr[1]);
	if (n == 3) return;

	if (arr[2] > arr[3]) swap(&arr[2], &arr[3]);
	if (arr[1] > arr[2]) swap(&arr[1], &arr[2]);
	if (arr[0] > arr[1]) swap(&arr[0], &arr[1]);
	if (n == 4) return;

	if (arr[3] > arr[4]) swap(&arr[3], &arr[4]);
	if (arr[2] > arr[3]) swap(&arr[2], &arr[3]);
	if (arr[1] > arr[2]) swap(&arr[1], &arr[2]);
	if (arr[0] > arr[1]) swap(&arr[0], &arr[1]);
	if (n == 5) return;

	if (arr[4] > arr[5]) swap(&arr[4], &arr[5]);
	if (arr[3] > arr[4]) swap(&arr[3], &arr[4]);
	if (arr[2] > arr[3]) swap(&arr[2], &arr[3]);
	if (arr[1] > arr[2]) swap(&arr[1], &arr[2]);
	if (arr[0] > arr[1]) swap(&arr[0], &arr[1]);
}
