void bubbleSort(int *Array, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    for (int j = 0; j < size - i - 1; j++)
    {
      if (Array[j] > Array[j + 1])
      {
        int temp = Array[j];
        Array[j] = Array[j + 1];
        Array[j + 1] = temp;
      }
    }
  }
}

void selectionsort(int *Array, int size)
{
  int minIndex = -1;
  for (int i = 0; i < size; i++)
  {
    minIndex = i;
    for (int j = i + 1; j < size; j++)
    {
      if (Array[minIndex] > Array[j])
      {
        minIndex = j;
      }
    }
    int temp = Array[i];
    Array[i] = Array[minIndex];
    Array[minIndex] = temp;
  }
}

void insertionSortLiteral(int Array[], int size)
{
  for (int i = 0; i < size; i++)
  {
    int j = i;
    while ((j > 0) && (Array[j] < Array[j - 1]))
    {
      int temp = Array[j];
      Array[j] = Array[j - 1];
      Array[j - 1] = temp;
      j--;
    }
  }
}

void insertionSortOptimaize(int Array[], int size)
{
  for (int i = 0; i < size; i++)
  {
    int temp = Array[i];
    int j = i - 1;
    while ((j >= 0) && (temp < Array[j]))
    {
      Array[j + 1] = Array[j];
      j--;
    }
    Array[j + 1] = temp;
  }
}

int partion(int Array[], int low, int high)
{
  int pivot = Array[high];

  int i = low - 1;

  for (int j = low; j < high; j++)
  {
    if (Array[j] <= pivot)
    {
      i++;
      int temp = Array[i];
      Array[i] = Array[j];
      Array[j] = temp;
    }
  }
  Array[high] = Array[i + 1];
  Array[i + 1] = pivot;
  return (i + 1);
}

void QuickSort(int Array[], int low, int high)
{
  if (low < high)
  {
    int pivot = partion(Array, low, high);
    QuickSort(Array, low, pivot - 1);
    QuickSort(Array, pivot + 1, high);
  }
}

void shellSort(int Array[], int size)
{
  for (int gap = size / 2; gap > 0; gap /= 2)
  {
    for (int i = gap; i < size; i++)
    {
      int temp = Array[i];
      int j = i;
      while (j >= gap && Array[j - gap] > temp)
      {
        Array[j] = Array[j - gap];
        j -= gap;
      }

      Array[j] = temp;
    }
  }
}



