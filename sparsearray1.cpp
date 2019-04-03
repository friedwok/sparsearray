#include<stdio.h>

template <class T>
class SparseArray {
	struct Item {
		int index;
		T value;
		Item *next;
	};
	Item *first;
public:
	SparseArray() : first(0) {}
	~SparseArray();
	class Interm {
		friend class SparseArray<T>;
		SparseArray<T> *master;
		int index;
		Interm(SparseArray<T> *a_master, int ind)
			: master(a_master), index(ind) {}
		T& Provide();
		void Remove();
	public:
		operator T();
		T operator=(T x);
		T operator+=(T x);
		T operator++();
		T operator++(int);
	};
	friend class Interm;

	Interm operator[](int idx)
	{
		return Interm(this, idx);
	}
private:
	SparseArray(const SparseArray<T>&) {}
	void operator=(const SparseArray<T>&) {}
};

template <class T>
SparseArray<T>::~SparseArray()
{
	while(first) {
		Item *tmp = first;
		first = first->next;
		delete tmp;
	}
}

template <class T>
T SparseArray<T>::Interm::operator=(T x)
{
	if(x == 0) {
		Remove();
	} else {
		Provide() = x;
	}
	return x;
}

template <class T>
T SparseArray<T>::Interm::operator+=(T x)
{
	T& location = Provide();
	location += x;
	T res = location;
	if(res == 0)
		Remove();
	return res;
}

template <class T>
T SparseArray<T>::Interm::operator++()
{
	T& location = Provide();
	T res = ++location;
	if(location == 0)
		Remove();
	return res;
}

template <class T>
T SparseArray<T>::Interm::operator++(int)
{
	T& location = Provide();
	T res = location++;
	if(location == 0)
		Remove();
	return res;
}

template <class T>
SparseArray<T>::Interm::operator T()
{
	Item *tmp;
	for(tmp = master->first; tmp; tmp = tmp->next) {
		if(tmp->index == index) {
			return tmp->value;
		}
	}
	return 0;
}

template <class T>
T& SparseArray<T>::Interm::Provide()
{
	Item *tmp;
	for(tmp = master->first; tmp; tmp = tmp->next) {
		if(tmp->index == index)
			return tmp->value;
	}
	tmp = new Item;
	tmp->index = index;
	tmp->next = master->first;
	master->first = tmp;
	return tmp->value;
}

template <class T>
void SparseArray<T>::Interm::Remove()
{
	Item **tmp;
	for(tmp = &(master->first); *tmp; tmp = &(*tmp)->next) {
		if((*tmp)->index == index) {
			Item *to_delete = *tmp;
			*tmp = (*tmp)->next;
			delete to_delete;
			return;
		}
	}
}


int main()
{
	SparseArray<double> arr1;
	arr1[10] = 5.5;
	arr1[33] = 86.4;
	++arr1[10];
	arr1[10] += 3.9;
	arr1[10] = 0;
	return 0;
}
