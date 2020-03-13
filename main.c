#include <assert.h>
#include <stdio.h>
#include <time.h>
#define NDEBUG 1
    unsigned int ns[] = { 1000, 900, 800, 700, 600, 500, 400, 300,200,100};


    int random(int min, int max){
    int tmp;
    if (max>=min){
        max = max - min;
    }else{
        tmp= min - max;
        min= max;
        max= tmp;
    }
    return  (rand() % max + min);
}


    void swap1(int *t,int i, int j){
    int tmp;
        tmp = t[i];
        t[i] = t[j];
        t[j] = tmp;
    }

    void swap(int *xp, int *yp)
    {
        int temp = *xp;
        *xp = *yp;
        *yp = temp;
    }
    void fill_increasing(int *t, unsigned int n) {
       for(int i = 0; i<n; i++) {t[i] = 2*i;}
    }

    void fill_decreasing(int *t, unsigned int n) {
        int j=0;
       for(int i = n-1; i>=0; i--) {t[i] = j++;}
    }

    void fill_vshape(int *t, unsigned int n) {
            int j=n/2;
        for(int i = 0; i<n/2; i++) {
                t[i] = 2*--j;
        }
        for(int i = n/2; i<=n-1; i++) {
                t[i] = 2*j++;
        }
    }

int argmin(int A[], int begin, int end ){
    int argmin;
    argmin = begin;
    for (int i= begin ; i<=end; i++){
         if (A[i] < A[argmin]){
            argmin = i;
        }
    }
    return argmin;
}

    void selection_sort(int *t, unsigned int n) {
        int j;
      for (int i = 0; i<n; i++){
        j = argmin(t, i, n-1 );
        swap1(t,i,j);
      }

    }



    void insertion_sort(int *t, unsigned int n) {

        int i, key, j;
        for (i = 1; i < n; i++) {
            key = t[i];
            j = i - 1;

            while (j >= 0 && t[j] > key) {
               t[j + 1] = t[j];
                j = j - 1;
            }
            t[j + 1] = key;
        }
    }
    int partition(int *t,int p, int r){
        int x = t[r];
        int i = p - 1;
        for (int j = p; j<r; j++){
            if (t[j] <= x){
                i = i + 1;
                swap1(t, i, j);
            }
        }
        i = i + 1;
        swap1(t, i, r);
        return i;
    }
    int random_partition(int *t,int p,int r){
    int i = random(p, r);
    swap1(t, i, r);
    return partition(t, p, r);
    }


    void quick_sort2(int *t,int p,int r){
        int q;
       if (p < r){
            q = partition(t, p, r);
            quick_sort2(t, p, q - 1);
            quick_sort2(t, q + 1, r);

       }
    }


    void quick_sort(int *t, unsigned int n) {
       quick_sort2(t, 0, n - 1);
    }

    void heapify(int arr[], int n, int i)
    {
        int largest = i; // Initialize largest as root
        int l = 2*i + 1; // left = 2*i + 1
        int r = 2*i + 2; // right = 2*i + 2

        if (l < n && arr[l] > arr[largest])
            largest = l;

        if (r < n && arr[r] > arr[largest])
            largest = r;

        if (largest != i)
        {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            heapify(arr, n, largest);
        }
    }

    void heap_sort(int *t, unsigned int n) {
          for (int i = n / 2 - 1; i >= 0; i--)
            heapify(t, n, i);

        for (int i=n-1; i>=0; i--)
        {
            int temp = t[0];
            t[0] = t[i];
            t[i] = temp;

            heapify(t, i, 0);
        }
    }



    void fill_random(int *t, unsigned int n) {
        for (unsigned int i = 0; i < n; i++) {
            t[i] = rand();
        }
    }

    void is_random(int *t, unsigned int n) {
        return;
    }

    void is_increasing(int *t, unsigned int n) {
        for (unsigned int i = 1; i < n; i++) {
           assert(t[i] > t[i - 1]);
        }
    }

    void is_decreasing(int *t, unsigned int n) {
        for (unsigned int i = 1; i < n; i++) {
          assert(t[i] < t[i - 1]);
        }
    }

    void is_vshape(int *t, unsigned int n) {
        int *begin = t;

        int *end = t + n - 1;
        while (end - begin > 1) {
           //assert(*begin > *end);
            begin++;
           assert(*end > *begin);
            end--;
        }
    }

    void is_sorted(int *t, unsigned int n) {
        for (unsigned int i = 1; i < n; i++) {
            assert(t[i] >= t[i - 1]);
        }
    }

    void (*fill_functions[])(int *, unsigned int) = { fill_random, fill_increasing, fill_decreasing, fill_vshape };
    void (*check_functions[])(int *, unsigned int) = { is_random, is_increasing, is_decreasing, is_vshape };
    void (*sort_functions[])(int *, unsigned int) = { selection_sort, insertion_sort, quick_sort, heap_sort };

    char *fill_names[] = { "Random", "Increasing", "Decreasing", "V-Shape" };
    char *sort_names[] = { "SelectionSort", "InsertionSort", "QuickSort", "HeapSort" };

    int main() {
        for (unsigned int i = 0; i < sizeof(sort_functions) / sizeof(*sort_functions); i++) {
            void (*sort)(int *, unsigned int) = sort_functions[i];

            for (unsigned int j = 0; j < sizeof(fill_functions) / sizeof(*fill_functions); j++) {
                void (*fill)(int *, unsigned int) = fill_functions[j];
                void (*check)(int *, unsigned int) = check_functions[j];

                for (unsigned int k = 0; k < sizeof(ns) / sizeof(*ns); k++) {
                    unsigned int n = ns[k];
                    int *t = malloc(n * sizeof(*t));

                    fill(t, n);
                    check(t, n);

                    clock_t begin = clock();
                    sort(t, n);
                    clock_t end = clock();
                    is_sorted(t, n);

                    printf("%s\t%s\t%u\t%f\n", sort_names[i], fill_names[j], n, (double)(end - begin) / (double) CLOCKS_PER_SEC);
                    free(t);
                }
            }
        }
        return 0;
    }
