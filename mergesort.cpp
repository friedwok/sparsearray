#include<iostream>

//standart comparator
template <typename T>
class standart_cmp
{
public:
	static bool less(const T &a, const T &b)
	{
		return a < b;
	}
};

//array merge function
//array - массив, который упорядочен (при помощи этого же компаратора) до middle, и посл middle
//buffer - массив, размером не меньше array
template <typename T, typename cmp = standart_cmp<T>>

void merge(T *array, T *buffer, int left, int middle, int right)
{
	//Индексы считывания чисел из array
	int it_left = 0;
	int it_right = 0;

	//Как только какой-либо из "итераторов" выходит за границу, прекращаем цикл
	while((left + it_left < middle) && (middle + it_right < right)) {
		if(cmp::less(array[left + it_left], array[middle + it_right])) {
			buffer[it_left + it_right] = array[left + it_left];
			it_left++;
		} else {
			buffer[it_left + it_right] = array[middle + it_right];
			it_right++;
		}
	}

	//Записываем оставшиеся части, невыписанные из array
	while(left + it_left < middle)
	{
		buffer[it_left + it_right] = array[left + it_left];
		it_left++;
	}

	while(middle + it_right < right)
	{
		buffer[it_left + it_right] = array[middle + it_right];
		it_right++;
	}

	//Выписываем buffer в array
	for(int i = 0; i < it_left + it_right; i++)
		array[left + i] = buffer[i];
}

//array - массив
//buffer - буфер для сортировки, размером не меньше. чем array
//left - нижняя граница right - верхняя

template <typename T, typename cmp = standart_cmp<T>>
void merge_sort(T *array, T *buffer, int left, int right)
{
	//Массив единичного размера уже отсортированным считается
	if(right - left <= 1)
	{
		return;
	}

	//Индекс серединного элемента
	int middle = left + (right - left) / 2;

	//Сортируем половинки массива
	merge_sort(array, buffer, left, middle);
	merge_sort(array, buffer, middle, right);

	//Составляем из двух отсортированных половинок
	//Целый отсортированный массив
	merge<T, cmp>(array, buffer, left, middle, right);
}

int main()
{
	int n;
	std::cout << "arr size = ";
	std::cin >> n;

	int *arr = new int[n];
	int *buff = new int[n];

	for(int i = 0; i < n; i++) {
		std::cout << "arr[" << i << "] = ";
		std::cin >> arr[i];
	}

	merge_sort(arr, buff, 0, n);

	for(int i = 0; i < n; i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	return 0;
}
