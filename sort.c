#include "sort.h"

void select_sort(int arr[], int nr)
{
	int tmp, max;
	for (int i = 0; i < nr-1; ++i)
	{
		max = i;
		for (int j = i+1; j < nr; ++j)
			if (arr[max] > arr[j])
				max = j;
		tmp = arr[i];
		arr[i] = arr[max];
		arr[max] = tmp;
	}
}

void select_2way_sort(int arr[], int nr)
{
	int tmp, min, max;
	for (int i = 0; i < nr/2; ++i)
	{
		min = max = i;
		for (int j = i+1; j < nr-i; ++j)
		{
			if (arr[max] < arr[j])
				max = j;
			if (arr[min] > arr[j])
				min = j;
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
		if (max == i)
			max = min;
		tmp = arr[nr-1-i];
		arr[nr-1-i] = arr[max];
		arr[max] = tmp;
	}
}

void bubble_sort(int arr[], int nr)
{
	int tmp, pos;
	for (int i = 0; i < nr-1; )
	{
		pos = nr-1;
		for (int j = nr-1; j > i; --j)
			if (arr[j] < arr[j-1])
			{
				tmp = arr[j];
				arr[j] = arr[j-1];
				arr[j-1] = tmp;
				pos = j;
			}
		i = pos;
	}
}

void bubble_2way_sort(int arr[], int nr)
{
	int tmp, pos;
	int low = 0, high = nr-1;
	while(low < high)
	{
		pos = low;
		for (int i = low; i < high; ++i)
			if (arr[i] > arr[i+1])
			{
				tmp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = tmp;
				pos = i;
			}
		high = pos;

		pos = high;
		for (int i = high; i > low; --i)
			if (arr[i] < arr[i-1])
			{
				tmp = arr[i];
				arr[i] = arr[i-1];
				arr[i-1] = tmp;
				pos = i;
			}
		low = pos;
	}
}

void insert_sort(int arr[], int nr)
{
	for (int i = 1; i < nr; ++i)
	{
		int j, key = arr[i];
		for (j = i; j > 0 && arr[j-1] > key; --j)
			arr[j] = arr[j-1];
		arr[j] = key;
	}
}

void insert_binary_sort(int arr[], int nr)
{
	for (int i = 1; i < nr; ++i)
	{
		int low = 0, high = i-1;
		int mid, key = arr[i];
		while(low <= high){
			mid = (low+high)/2;
			arr[mid] < key ? (low = mid+1) : (high = mid-1);
		}

		for (int j = i; j > low; --j)
			arr[j] = arr[j-1];
		arr[low] = key;
	}
}

void insert_2way_sort(int arr[], int nr)
{
	int tmp[nr];
	tmp[0] = arr[0];
	int first = 0 , last = 0;
	for (int i = 1; i < nr; ++i)
	{
		if (arr[i] < tmp[first])
			tmp[first = (first-1+nr)%nr] = arr[i];
		else if (arr[i] > tmp[last])
			tmp[++last] = arr[i];
		else{
			int j, jless;
			for (j = ++last; tmp[jless=(j-1+nr)%nr] > arr[i]; j = jless)
				tmp[j] = tmp[jless];
			tmp[j] = arr[i];
		}
	}
	for (int i = 0; i < nr; ++i)
		arr[i] = tmp[(first+i)%nr];
}

static void heap_adjust(int arr[], int nr, int parent)
{
	int key = arr[parent];
	int child = parent*2 + 1;
	while(child < nr)
	{
		if (child+1 < nr && arr[child] < arr[child+1])
			child++;
		if (key > arr[child])
			break;
		arr[parent] = arr[child];
		parent = child;
		child = parent*2 + 1;
	}
	arr[parent] = key;
}

void heap_sort(int arr[], int nr)
{
	for (int i = nr/2 - 1; i >= 0; --i)
		heap_adjust(arr, nr, i);
	int tmp;
	for (int i = nr-1; i > 0; --i)
	{
		tmp = arr[i];
		arr[i] = arr[0];
		arr[0] = tmp;
		heap_adjust(arr, i, 0);
	}
}

static void swap(int arr[], int i, int j)
{
	int tmp = arr[i];
	arr[i] = arr[j];
	arr[j] = tmp;
}

void quick_sort(int arr[], int left, int right)
{
	if (left >= right)
		return;
	swap(arr, left, (left+right)/2);

	int mid = left;
	for (int i = left+1; i <= right; ++i)
		if (arr[i] < arr[left])
			swap(arr, ++mid, i);
	swap(arr, mid, left);

	quick_sort(arr, left, mid-1);
	quick_sort(arr, mid+1, right);
}

void shell_sort(int arr[], int nr)
{
	for (int d = nr/2; d > 0; d /= 2)
	{
		if (d%2 == 0)
			d++;
		for (int i = d; i < nr; ++i)
		{
			int j, key = arr[i];
			for (j = i; j >= d && arr[j-d] > key ; j -= d)
				arr[j] = arr[j-d];
			arr[j] = key;
		}
	}
}

void merge_sort(int arr[], int left, int right)
{
	if (left >= right)
		return;
	int mid = (left+right)/2;
	merge_sort(arr, left, mid);
	merge_sort(arr, mid+1, right);

	int count = right-left+1, tmp[count];
	for (int i = 0; i < count; ++i)
		tmp[i] = arr[left+i];
	int j = 0, jmax = mid-left, k = jmax+1;
	for (int i = left; i <= right; ++i)
		arr[i] = j>jmax || k<count && tmp[j] > tmp[k] ? tmp[k++] : tmp[j++];
}

void count_sort(int arr[], int nr)
{
	int max = arr[0];
	for (int i = 1; i < nr; ++i)
		if (max < arr[i])
			max = arr[i];
	int counts[++max];
	for (int i = 0; i < max; ++i)
		counts[i] = 0;
	for (int i = 0; i < nr; ++i)
		counts[arr[i]]++;
	for (int i = 0, j = 0; i < max; ++i)
		while(counts[i]-- > 0)
			arr[j++] = i;
}