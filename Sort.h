#include "Tree.h"
#include "Sequence.h"
#include <functional>

//Быстрая сортировка для произвольного массива с заданным размером
//Вспомогательная функция
template <typename T>
void QS_help(std::function<bool(T, T)> func, T *mas, int size) {

    if(size == 0 || size == 1) return;

    //Индексы в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный (опорный) элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {
        //Пробегаем элементы, ищем те, которые нужно перекинуть в другую часть
        //В правой части массива пропускаем(оставляем на месте) элементы, которые проходят условие сортровки
        while(func(mas[j],mid)) {
            j--;
        }
        //В левой части пропускаем элементы, которые не проходят условие сортировки
        while(!func(mas[i],mid) && mas[i] != mid) {
            i++;
        }

        //Меняем элементы местами
        if (i <= j) {
            T tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if(j > 0) {
        //"Левый кусок"
        QS_help<T>(func, mas, j + 1);
    }
    if (i < size) {
        //"Правый кусок"
        QS_help<T>(func, &mas[i], size - i);
    }
}


//Быстрая сортировка
template <typename T>
Sequence<T>* quickSort(std:: function<bool(T, T)> func, Sequence<T>* seq){
    if(seq->GetLength() == 0 || seq->GetLength() == 1) {
        return seq;
    }
    T* arr = new T[seq->GetLength()];
    for(int i = 0; i < seq->GetLength(); i++){
        arr[i] = seq->Get(i);
    }
    QS_help(func, arr, seq->GetLength());
    Sequence<T>* res = (seq->GetSubSequence(0, seq->GetLength()-1));
    res->Replace(arr, seq->GetLength());
    return res;
}

template<typename T>
ArraySequence<T>* treeSort(std::function<bool(T, T)> func, ArraySequence<T>* sequence){
    Tree<T>* tree = new Tree<T>(func);
    for(int i = 0; i< sequence->GetLength(); i++)
        tree->addElem(sequence->Get(i));
    auto* arraySequence = new ArraySequence<T>(*(tree->LNR()));
    return arraySequence;
}   //Сортировка с помощью выбора из дерева для динамического массива


//Сортировка деревом (список)
template<typename T>
ListSequence<T>* treeSort(std::function<bool(T, T)> func, ListSequence<T>* sequence){
    Tree<T>* tree = new Tree<T>(func);
    for(int i = 0; i< sequence->GetLength(); i++)
        tree->addElem(sequence->Get(i));
    auto* dynamicArray = tree->LNR();
    T* array = dynamicArray->GetHead();
    ListSequence<T>* listSequence = new ListSequence<T>(array, sequence->GetLength());
    return listSequence;
}   //Сортировка с помощью выбора из дерева для связного списка

//Сортировка пузырьком
template <typename T>
Sequence<T>* bubbleSort(std::function<bool(T, T)> predicate, Sequence<T> *sequence)
{
    Sequence<T>* res = sequence->GetSubSequence(0,sequence->GetLength()-1);      //хитрое копирование
    for(int i = (res)->GetLength(); i > 0; i--)     //все просто: сравниваем j и j+1. Больше - переставляем.
        for(int j = 0; j<i-1; j++)
            if (predicate( res->Get(j),res->Get(j+1) ))
                res->Swap(j,j+1);
    return res;
}

#endif
