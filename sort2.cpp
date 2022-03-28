#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iterator>
#include <cmath>
#include <chrono>
#include <algorithm>

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void QuickSort(int *tab, int begin, int end)
{
    int piv, tmp;

    int i = begin;
    int j = end;

    piv = tab[(begin + end) / 2];

    do
    {
        while (tab[i] < piv)
        {
            ++i;
        }

        while (tab[j] > piv)
        {
            --j;
        }

        if (i <= j)
        {
            swap(tab[i], tab[j]);
            ++i;
            --j;
        }
    } while (i < j);

    if (begin < j)
    {
        QuickSort(tab, begin, j);
    }

    if (end > i)
    {
        QuickSort(tab, i, end);
    }
}

void merge(int *tab, int begin, int mid, int end)
{

    int *tmp_first = new int[mid - begin + 1];
    int *tmp_second = new int[end - mid];

    for (int i = 0; i < (mid - begin + 1); i++)
    {
        tmp_first[i] = tab[i + begin];
    }

    for (int j = 0; j < (end - mid); j++)
    {
        tmp_second[j] = tab[j + mid + 1];
    }

    int k = 0;
    int l = 0;
    int index = begin;

    while (k < (mid - begin + 1) && l < (end - mid))
    {
        if (tmp_first[k] <= tmp_second[l])
        {
            tab[index] = tmp_first[k];
            ++k;
        }
        else
        {
            tab[index] = tmp_second[l];
            ++l;
        }
        ++index;
    }

    while (k < (mid - begin + 1))
    {
        tab[index] = tmp_first[k];
        ++k;
        ++index;
    }

    while (l < (end - mid))
    {
        tab[index] = tmp_second[l];
        ++l;
        ++index;
    }

    delete[] tmp_first;
    delete[] tmp_second;
}

void mergeSort(int *tab, int begin, int end)
{
    if (begin < end)
    {
        int mid = begin + (end - begin) / 2;

        mergeSort(tab, begin, mid);
        mergeSort(tab, mid + 1, end);
        merge(tab, begin, mid, end);
    }
}

void insertionSort(int *tab, int begin, int end)
{
    int j, tmp;
    for (int i = begin + 1; i < end; i++)
    {
        tmp = tab[i];
        j = i;

        while (j >= begin && tab[j - 1] > tmp)
        {
            tab[j] = tab[j - 1];
            --j;
        }
        tab[j] = tmp;
    }
}

void heapify(int *tab, int size_of_heap, int root)
{
    int max;
    int left = 2 * root + 1;
    int right = 2 * root + 2;

    if (left < size_of_heap && tab[left] > tab[root])
    {
        max = left;
    }
    else
    {
        max = root;
    }

    if (right < size_of_heap && tab[right] > tab[max])
    {
        max = right;
    }

    if (max != root)
    {
        swap(tab[root], tab[max]);
        heapify(tab, size_of_heap, max);
    }
}

void heapBuild(int *tab, int size_of_heap)
{
    int i;

    for (int i = size_of_heap / 2; i >= 0; i--)
    {
        heapify(tab, size_of_heap, i);
    }
}

void heapSort(int *tab, int size)
{
    if (size <= 1)
    {
        return;
    }

    heapBuild(tab, size);

    for (int i = size - 1; i > 0; i--)
    {
        swap(tab[0], tab[i]);
        --size;
        heapify(tab, size, 0);
    }
}

int partition(int *tab, int begin, int end)
{
    int piv;
    int i = begin;
    // int j = end;

    // std::cout<<"P1 "<<begin<<' '<<end<<'\n';
    piv = tab[end];
    // std::cout<<"P1\n";
    for (int j = begin; j < end; j++)
    {
        if (tab[j] <= piv)
        {

            swap(tab[j], tab[i]);
            ++i;
        }
    }

    // std::cout<<"P1\n";
    swap(tab[i], tab[end]);
    /*do
    {
        while (tab[i] < piv)
        {
            ++i;
        }

        while (tab[j] > piv)
        {
            --j;
        }

        if(i<=j)
        {
            swap(tab[i],tab[j]);
            ++i;
            --j;
        }
    } while (i < j);*/

    return i;
}

void intro(int *tab, int maxdepth, int *begin, int *end)
{
    int size = end - begin;
    int piv;
    if (size < 16)
    {
        insertionSort(tab, begin - tab, end - tab);
        // std::cout<<"I\n";
        return;
    }
    else if (maxdepth == 0)
    {
        heapSort(tab, size);
        // std::cout<<"H\n";
        return;
    }
    else
    {
        // std::cout<<"U\n";
        piv = partition(tab, begin - tab, end - tab);
        // std::cout<<"Q\n";

        for (int i = 0; i < 19; i++)
        {
            std::cout << tab[i] << ' ';
        }
        std::cout << '\n';

        intro(tab, maxdepth - 1, begin, tab + piv - 1);
        intro(tab, maxdepth - 1, tab + piv + 1, end);

        // intro(tab,maxdepth-1,piv,begin,piv-1);
        // intro(tab,maxdepth-1,size-piv-1,piv+1,end);
    }
}

void introSort(int *tab, int size, int *begin, int *end)
{
    int maxdepth = std::floor(log2(size)) * 2;
    // std::cout<<maxdepth<<'\n';
    intro(tab, maxdepth, begin, end);
}

int main()
{

    int tab[] = {1, 5, 4, 7, 12, 54, 112, 3, 43, 67, 99, 7, 2, 10, 64, 33, 87, 17, 91};

    int size = 19;

    for (int i = 0; i < 19; i++)
    {
        // std::cout<<tab[i]<< ' ';
    }
    std::cout << '\n';
    // heapSort(tab,size);
    // std::sort(tab,tab+10);
    for (int i = 0; i < 19; i++)
    {
        // std::cout<<tab[i]<< ' ';
    }

    std::chrono::high_resolution_clock clk;
    using std::chrono::duration;
    using std::chrono::duration_cast;
    std::chrono::milliseconds ms;
    std::chrono::nanoseconds ns;

    double czas = 0;

    int Tsize = 1000000;
    int part = 0.997 * Tsize;

    int **tab1 = new int *[100];
    for (int i = 0; i < 100; i++)
    {
        tab1[i] = new int[Tsize];
    }

    srand(time(NULL));
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < Tsize; j++)
        {
            tab1[i][j] = rand();
        }

        std::sort(tab1[i], tab1[i] + Tsize, std::greater<int>());
    }

    std::cout << "H\n";

    auto t1 = clk.now();
    for (int i = 0; i < 100; i++)
    {
        // QuickSort(tab1[i],0,Tsize);
        // mergeSort(tab1[i],0,Tsize-1);
        heapSort(tab1[i], Tsize);
    }
    auto t2 = clk.now();

    duration<double, std::milli> ms_double = t2 - t1;
    std::chrono::duration<double> time = t2 - t1;
    std::cout << '\n'
              << "Czas s: " << time.count();
    // czas = czas + ms_double.count();

    for (int i = 0; i < 100; i++)
    {
        delete[] tab1[i];
    }
    delete[] tab1;
    return 0;
}