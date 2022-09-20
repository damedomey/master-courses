#include <iostream>
#include <chrono>

using namespace std;

class Stopwatch {
    std::chrono::high_resolution_clock::time_point start_;
    std::chrono::high_resolution_clock::time_point stop_;
public:
    Stopwatch() {}
    void start() { start_ = std::chrono::high_resolution_clock::now(); }
    void stop() { stop_ = std::chrono::high_resolution_clock::now(); }
    // Le ratio vaut std::nano, std::micro, std::milli, std::ratio<1> (ie equivalent to seconds),...
    // ATTENTION: there is no rounding mode: just a truncation
    template <class ratio>
    int64_t elapsed()const {
        typedef std::chrono::duration<int64_t, ratio> duration_type;
        duration_type et = std::chrono::duration_cast<duration_type>(stop_ - start_);
        return et.count();
    }
    int64_t elapsed_ms()const { return elapsed<std::milli>(); }
    int64_t elapsed_us()const { return elapsed<std::micro>(); }
    int64_t elapsed_ns()const { return elapsed<std::nano>(); }
    double mps(const int64_t numOp)const { // million per seconds
        double et = static_cast<double>(elapsed<std::nano>());
        return (numOp / et) * 1000.;
    }
    Stopwatch& operator+=(const Stopwatch& t) {
        stop_ += (t.stop_ - t.start_);
        return *this;
    }
};

class DynamicArray {
private:
    int *array;
    unsigned int limit;

public:
    DynamicArray(int limit = 1000) {
        this->limit = limit;
        array = (int *) malloc(limit * sizeof(int *));
    }

    ~DynamicArray() {
        delete [] array;
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

    void expand(int newAlloc = 1000) {
        limit += newAlloc;
        // limit *= 2;
        array = (int *) realloc(array, limit * sizeof(int *));
    };
};

class Stack{
private:
    DynamicArray *data;
    int last; //index of last element

public:
    Stack(int limit = 1000){
        data = new DynamicArray(limit);
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

class StackHeritage : private DynamicArray {
private:
    int last = 0;

public:
    StackHeritage(int limit = 1000): DynamicArray(limit) {

    }
    void push(int nbr){
        if (last == this->getLimit()) {
            this->expand();
        }
        this->set(last++, nbr);
    }

    int pop(){
        if (last == 0){
            printf("\nERR: This stack is empty. 0's returned.\n");
            return 0;
        }
        return this->get(last--);
    }

    int top(){
        return this->get(last);
    }

    int count() const{
        return last;
    }
};

int main() {
    int sum = 0;
    const int MAX_ITER = 100000000;
    Stopwatch sw;

    Stack stack;
    sw.start();
    for (int i = 0; i < MAX_ITER; i++){
        stack.push(i);
    }

    int count = stack.count(); // utilisation d'une variable sinon la diminution de la taille de la stack influence la boucle
    for (int i = 0; i < count; i++){
        sum += stack.pop();
    }
    sw.stop();

    printf("composition : sum == %d => %d ms\n", sum, (int)sw.elapsed_ms());

    sum = 0;
    StackHeritage stackHer = *new StackHeritage();
    sw.start();
    for (int i = 0; i < MAX_ITER; i++){
        stackHer.push(i);
    }

    count = stackHer.count();
    for (int i = 0; i < count; i++){
        sum += stackHer.pop();
    }
    sw.stop();

    printf("Heritage : sum == %d => %d ms\n", sum, (int)sw.elapsed_ms());
    return 0;
}