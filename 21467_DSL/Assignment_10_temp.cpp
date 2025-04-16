#include <iostream>
using namespace std;

class HeapSort {
public:
    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void maxheapify(int arr[], int i, int n) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxheapify(arr, largest, n);
        }
    }

    void buildMaxHeap(int arr[], int n) {
        for (int i = n / 2 - 1; i >= 0; i--) {
            maxheapify(arr, i, n);
        }
    }

    void heapSort(int arr[], int n) {
        buildMaxHeap(arr, n);
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            maxheapify(arr, 0, i);
        }

        cout << "Sorted array: ";
        displayArray(arr, n);
    }

    void inputArray(int arr[], int &n) {
        cout << "Enter the number of elements: ";
        cin >> n;
        cout << "Enter the elements:\n";
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
    }

    void displayArray(int arr[], int n) {
        for (int i = 0; i < n; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    HeapSort hs;
    int arr[100], n = 0, choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Input Array\n";
        cout << "2. Sort Array using HeapSort\n";
        cout << "3. Display Array\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                hs.inputArray(arr, n);
                break;
            case 2:
                if (n <= 0) {
                    cout << "Array is empty\n";
                } else {
                    hs.heapSort(arr, n);
                }
                break;
            case 3:
                if (n <= 0) {
                    cout << "Array is empty\n";
                } else {
                    cout << "Current array: ";
                    hs.displayArray(arr, n);
                }
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice\n";
        }
    } while (choice != 4);

    return 0;
}
