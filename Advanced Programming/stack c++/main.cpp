#include <iostream>
#include <chrono>

using namespace std;

class DynamicArray {
private:
    int *array;
    unsigned int limit;

public:
    DynamicArray() {
        limit = 1000;
        array = (int *) malloc(limit * sizeof(int *));
    }

    int get(int position) {
        return array[position];
    }

    void set(int position, int data) {
        array[position] = data;
    }

    int getLimit() const {
        return limit;
    }

    void expand() {
        limit += 1000;
        array = (int *) realloc(array, limit * sizeof(int *));
    };
};

class Stack{
private:
    DynamicArray *data;
    int last; //index of last element

public:
    Stack(){
        data = new DynamicArray();
        last = 0;
    }
    void push(int nbr){
        if (last == data->getLimit()) {
            data->expand();
        }
        data->set(last++, nbr);
    }

    int pop(){
        if (last == 0){
            printf("\nERR: This stack is empty. 0's returned.\n");
            return 0;
        }
        return data->get(last--);
    }

    int top(){
        return data->get(last);
    }

    int count() const{
        return last;
    }
};

int main() {
    int sum = 0;

    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();

    Stack stack = *new Stack();

    for (int i = 0; i < 1000*1000; i++){
        stack.push(i);
    }

    int count = stack.count(); // utilisation d'une variable sinon la diminution de la taille de la stack influence la boucle
    for (int i = 0; i < count; i++){
        sum += stack.pop();
    }

    printf("sum == %d \n", sum);

    printf("%lld nanoseconds", chrono::duration_cast<chrono::nanoseconds>( chrono::high_resolution_clock::now() - start).count());

    return 0;
}