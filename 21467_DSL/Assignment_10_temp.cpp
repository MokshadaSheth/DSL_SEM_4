#include <iostream>
using namespace std;

class Heap
{
    int *arr;
    int n;

public:
    Heap()
    {
        arr = new int[0];
        n = -1;
    }
    Heap(int size)
    {
        arr = new int[size];
        n = size;
    }
    ~Heap()
    {
        cout<<"\nDestructor Deleting Objects..\n";
        delete[] arr;
    }

    void maxHeapify(int i, int size);
    void minHeapify(int i, int size);
    void buildMaxHeap();
    void buildMinHeap();
    void heapSortDesen();
    void heapSortAscen();
    void inputData();
    void displayArr();
    void getSmallest();
    void getLargest();
};
void Heap :: maxHeapify(int i, int size)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left<size && arr[left] > arr[largest])
    {
        largest = left;
    }
    if(right<size && arr[right] > arr[largest])
    {
        largest = right;
    }
    if(largest != i)
    {
        swap(arr[i],arr[largest]);
        maxHeapify(largest,size);
    }
}
void Heap :: minHeapify(int i, int size)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < size && arr[left] < arr[smallest])
    {
        smallest = left;
    }
    if(right < size && arr[right] < arr[smallest])
    {
        smallest = right;
    }
    if(smallest != i)
    {
        swap(arr[i],arr[smallest]);
        minHeapify(smallest,size);
    }
}
void Heap ::buildMaxHeap()
{
    for(int i= n/2-1; i>=0; i--)
    {
        maxHeapify(i,n);
    }
}
void Heap :: buildMinHeap()
{
    for(int i= n/2-1; i>=0; i--)
    {
        minHeapify(i,n);
    }
}
void Heap :: heapSortAscen()
{
    buildMaxHeap(); 
    for(int i=n-1; i>0; i--)
    {
        swap(arr[0], arr[i]);
        maxHeapify(0,i); //Top ele, size which reduced
    }
    cout<<"\nSorted the array in Ascending order\n";
}
void Heap :: heapSortDesen()
{
    buildMinHeap();
    for(int i=n-1; i>0; i--)
    {
        swap(arr[0], arr[i]);
        minHeapify(0,i); //Top ele, size which reduced
    }
    cout<<"\nSorted the array in Desending Order\n";
}
void Heap :: getLargest()
{
    buildMaxHeap();
    cout<<"\n Largest: "<<arr[0]<<endl;
}
void Heap :: getSmallest()
{
    buildMinHeap();
    cout<<"\n Smallest: "<<arr[0]<<endl;
}
void Heap ::inputData()
{
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter " << i << " ele: ";
        cin >> arr[i];
    }
}
void Heap :: displayArr()
{
    for (int i = 0; i < n; i++)
    {
        cout<<" "<<arr[i];
    }
}
int main()
{
    int choice;
    Heap obj;
    do
    {
        cout << "\n1.Input Array\n2.Display Array\n3.Heap Sort Desending\n4.Heap Sort Ascending\n5.Get Max Ele\n6.Get Min Ele\n7.Exit\n";
        cout << "\nEnter choice code: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            int size;
            cout << "\nEnter total number of elements:";
            cin >> size;
            obj = Heap(size);
            obj.inputData();
            break;
        case 2:
            obj.displayArr();
            break;
        case 3:
            obj.heapSortDesen();
            break;
        case 4:
            obj.heapSortAscen();
            break;
        case 5:
            obj.getLargest();
            break;
        case 6:
            obj.getSmallest();
        case 7:
            cout<<"\nByee";
            break;
        default:
            cout<<"\nInvalid IP";
            break;
        }
    } while (choice != 7);
    return 0;
}