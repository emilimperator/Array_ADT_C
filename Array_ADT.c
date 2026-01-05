#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Array {
    int *A;
    int size;
    int length;
};

void Display(struct Array arr);
void Append(struct Array *arr, int element);
void Insert(struct Array *arr, int index, int element);
void Insert_Sorted(struct Array *arr, int element);
bool IsSorted(struct Array arr);
void Swap(int *element_1, int *element_2);
void Delete(struct Array *arr, int index);
int LinearSearch(struct Array arr, int element);
int BinarySearch(struct Array arr, int element);
void Get(struct Array arr, int index);
void Set(struct Array *arr, int index, int element);
int Max(struct Array arr);
int Min(struct Array arr);
int Sum(struct Array arr);
int Sum_Recursive(struct Array arr, int size);
int Average(struct Array arr);
void Reverse(struct Array *arr);
void LeftRotate(struct Array arr);
void RightRotate(struct Array arr);
void Negative_Left(struct Array *arr);
void Positive_Left(struct Array *arr);
int *Merge(int *arr_1, int size_1, int *arr_2, int size_2);

int main(void) {
    struct Array arr;
    printf("Enter the size of an array: "); // 10
    scanf("%d", &arr.size);
    arr.A = (int *)malloc(arr.size * sizeof(int));

    bool stop = false;
    int n = 0;
    while (!stop) {
        int a;
        printf("Enter the number of elements: "); // 7
        scanf("%d", &a);
        if (a <= arr.size) {
            stop = true;
            n = a;
        } else {
            printf("The number of elements that are requested should be "
                   "smaller or equal to the size of an array.\n");
        }
    }

    printf("Enter the all elements: "); // 1 2 3 4 5 6 7
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr.A[i]);
    }
    arr.length = n;

    Insert(&arr, 6, 7); // 1 2 3 4 5 6 7 7
    printf("After inserting in an array: ");
    Display(arr);

    Insert_Sorted(&arr, 8);
    printf("After inserting in a sorted array: ");
    Display(arr);

    Append(&arr, 10); // 1 2 3 4 5 6 7 7 10
    printf("After appending an element to the end: ");
    Display(arr);

    Delete(&arr, 3); // 1 2 3 5 6 7 7 10
    printf("After deleting an element by index: ");
    Display(arr);

    Set(&arr, 3, 4); // 1 2 3 4 6 7 7 10
    printf("After changing an element in specific index: ");
    Display(arr);

    int *merged_arrays = Merge(arr.A, arr.length, (int[]){1, 2, 3, 4}, 4);
    printf("After merging two arrays: ");
    for (int i = 0; i < arr.length + 4; i++) {
        printf("%d ", merged_arrays[i]);
    }
    printf("\n");

    Reverse(&arr); // 10 7 7 6 4 3 2 1
    printf("After reversing an array: ");
    Display(arr);

    LeftRotate(arr); // 7 7 6 4 3 2 1 10
    printf("After left-rotating an array: ");
    Display(arr);

    RightRotate(arr); // 10 7 7 6 4 3 2 1
    printf("After right-rotating an array: ");
    Display(arr);

    printf("The Maximum Element of the list is: %d\n", Max(arr));

    printf("The Minimum Element of the list is: %d\n", Min(arr));

    printf("The Sum of the list is: %d\n", Sum(arr));

    printf("The Sum of the list in recursive way is: %d\n",
           Sum_Recursive(arr, arr.length));

    printf("The Average of the list is: %d\n", Average(arr));

    free(arr.A);
}

void Display(struct Array arr) {
    printf("Elements are: ");
    for (int i = 0; i < arr.length; i++) {
        printf("%d ", arr.A[i]);
    }
    printf("\n");
}

void Append(struct Array *arr, int element) {
    if (arr->length < arr->size) {
        arr->A[arr->length] = element;
        arr->length++;
    } else
        printf("The length of an array cannot be bigger than the size of an "
               "array.\n");
}

void Insert(struct Array *arr, int index, int element) {
    if (index >= 0 && index <= arr->length) {
        if (arr->length < arr->size) {
            for (int i = arr->length; i > index; i--) {
                arr->A[i] = arr->A[i - 1];
            }
            arr->A[index] = element;
            arr->length++;
        } else
            printf("The length of an array cannot be bigger than the size of "
                   "an array.\n");
    } else
        printf("Index is out of range.\n");
}

void Insert_Sorted(struct Array *arr, int element) {
    if (arr->length == arr->size) {
        printf("Array is full.\n");
        return;
    }
    int i = arr->length - 1;

    while (i >= 0 && arr->A[i] > element) {
        arr->A[i + 1] = arr->A[i];
        i--;
    }

    arr->A[i + 1] = element;
    arr->length++;
}

bool IsSorted(struct Array arr) {
    for (int i = 0; i < arr.length - 1; i++) {
        if (arr.A[i + 1] < arr.A[i])
            return false;
    }
    return true;
}

void Swap(int *element_1, int *element_2) {
    int temp = *element_1;
    *element_1 = *element_2;
    *element_2 = temp;
}

void Negative_Left(struct Array *arr) {
    int i = 0, j = arr->length - 1;
    while (i < j) {
        while (arr->A[i] < 0) {
            i++;
        }
        while (arr->A[j] > 0) {
            j--;
        }
        if (i < j) {
            Swap(&arr->A[i], &arr->A[j]);
        }
    }
}

void Positive_Left(struct Array *arr) {
    int i = 0, j = arr->length - 1;
    while (i < j) {
        while (arr->A[i] > 0) {
            i++;
        }
        while (arr->A[j] < 0) {
            j--;
        }
        if (i < j) {
            Swap(&arr->A[i], &arr->A[j]);
        }
    }
}

void Delete(struct Array *arr, int index) {
    if (index >= 0 && index < arr->length) {
        for (int i = index; i < arr->length - 1; i++) {
            arr->A[i] = arr->A[i + 1];
        }
        arr->length--;
    } else
        printf("Index is out of range.\n");
}

int LinearSearch(struct Array arr, int element) {
    for (int i = 0; i < arr.length; i++) {
        if (arr.A[i] == element) {
            return i;
        }
    }
    return -1;
}

int BinarySearch(struct Array arr, int element) {
    int left = 0, right = arr.length - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        if (arr.A[middle] == element) {
            return middle;
        } else if (arr.A[middle] < element) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }
    return -1;
}

void Get(struct Array arr, int index) {
    if (index >= 0 && index < arr.length) {
        printf("%d\n", arr.A[index]);
    } else
        printf("Index is out of range.\n");
}

void Set(struct Array *arr, int index, int element) {
    if (index >= 0 && index < arr->length) {
        arr->A[index] = element;
    } else
        printf("Index is out of range.\n");
}

int Max(struct Array arr) {
    int the_biggest = arr.A[0];
    for (int i = 1; i < arr.length; i++) {
        if (arr.A[i] > the_biggest) {
            the_biggest = arr.A[i];
        }
    }
    return the_biggest;
}

int Min(struct Array arr) {
    int the_smallest = arr.A[0];
    for (int i = 1; i < arr.length; i++) {
        if (arr.A[i] < the_smallest) {
            the_smallest = arr.A[i];
        }
    }
    return the_smallest;
}

int Sum(struct Array arr) {
    int total = 0;
    for (int i = 0; i < arr.length; i++) {
        total += arr.A[i];
    }
    return total;
}

int Sum_Recursive(struct Array arr, int size) {
    if (size < 1)
        return 0;
    else
        return Sum_Recursive(arr, size - 1) + arr.A[size - 1];
}

int Average(struct Array arr) {
    if (arr.length == 0)
        return 0;
    return (double)Sum(arr) / arr.length;
}

void Reverse(struct Array *arr) {
    int *B = (int *)malloc(arr->length * sizeof(int));
    for (int i = arr->length - 1, j = 0; i >= 0; i--, j++) {
        B[j] = arr->A[i];
    }
    free(arr->A);
    arr->A = B;
}

void LeftRotate(struct Array arr) {
    int first_element = arr.A[0];
    for (int i = 0; i < arr.length - 1; i++) {
        arr.A[i] = arr.A[i + 1];
    }
    arr.A[arr.length - 1] = first_element;
}

void RightRotate(struct Array arr) {
    int last_element = arr.A[arr.length - 1];
    for (int i = arr.length - 1; i > 0; i--) {
        arr.A[i] = arr.A[i - 1];
    }
    arr.A[0] = last_element;
}

int *Merge(int *arr_1, int size_1, int *arr_2, int size_2) {
    int *merged_arr = (int *)malloc((size_1 + size_2) * sizeof(int));

    if (!merged_arr) {
        printf("Memory allocation is failed.\n");
        return NULL;
    }

    int i = 0, j = 0, index = 0;
    while (i < size_1 && j < size_2) {
        if (arr_1[i] < arr_2[j]) {
            merged_arr[index++] = arr_1[i++];
        } else {
            merged_arr[index++] = arr_2[j++];
        }
    }

    while (i < size_1)
        merged_arr[index++] = arr_1[i++];
    while (j < size_2)
        merged_arr[index++] = arr_2[j++];

    return merged_arr;
}
