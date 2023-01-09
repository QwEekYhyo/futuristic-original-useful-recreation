#include <iostream>

int length(int *arr) {
    return sizeof(arr)/sizeof(int);
}

void reassign(int *arr1, int *arr2) {
    int len1 = length(arr1);
    int len2 = length(arr2);
    if (len1 != len2) {
        return;
    }
    for (int i = 0; i < len1; i++) {
        std::cout << arr1[i] << " and " << arr2[i] << '\n';
        arr1[i] = arr2[i];
    }
}
