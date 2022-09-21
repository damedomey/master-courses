// It possible to get the best performance if we increase the initial Dynamic Array length.
public class Main {
    public static void main(String[] args) {
        int sum = 0;
        final int MAX_ITER = 100_000_000;
        Stack stack = new Stack();
        long start = System.nanoTime();
        for (int i=0; i < MAX_ITER; i++){
            stack.push(i);
        }

        for (int i=0; i < MAX_ITER; i++){
            sum += stack.pop();
        }
        long end = System.nanoTime();
        System.out.println("composition sum = " + sum + " => " + ((end - start) / 1000000) + " ms");

        StackHeritage stackHeritage = new StackHeritage();
        sum = 0;
        start = System.nanoTime();
        for (int i=0; i < MAX_ITER; i++){
            stackHeritage.push(i);
        }

        for (int i=0; i < MAX_ITER; i++){
            sum += stackHeritage.pop();
        }
        end = System.nanoTime();
        System.out.println("heritage sum = " + sum + " => " + ((end - start) / 1000000) + " ms");
    }
}

class DynamicArray {
    private int[] array;
    private int limit;

    DynamicArray(int limit){
        this.limit = limit;
        array = new int[limit];
    }

    int get(int index){
        return array[index];
    }
    void set(int index, int value){
        if (index >= this.getLimit()){
            System.out.println("Out of bounds error. Cancelled");
            return;
        }
        array[index] = value;
    }

    int getLimit(){
        return limit;
    }

    void expand(int newLength){
        int [] newArray = new int[newLength];
        for (int i = 0; i<getLimit(); i++){
            newArray[i] = array[i];
        }
        array = newArray;
        limit = newLength;
    }
}

class Stack {
    private DynamicArray array;
    private int last;

    Stack(){
        array = new DynamicArray(1000);
        last = 0;
    }
    void push(int value){
        if (last >= array.getLimit()){
            array.expand((array.getLimit() > 1_000_000) ?2 * array.getLimit() + 1_000_000 : 2 * array.getLimit() ); // limite probably lost cost to 1_000_000
        }
        array.set(last++, value);
    }

    int pop(){
        return array.get(--last);
    }

    int top(){
        return array.get(last);
    }
}

// In this case, the good practice recommend to make certain methods of DynamicArray like set, get and expand as protected
class StackHeritage extends DynamicArray {
    private int last;

    StackHeritage() {
        super(1000);
        last = 0;
    }

    void push(int value){
        if (last >= this.getLimit()) {
            this.expand((this.getLimit() > 1_000_000) ?2 * this.getLimit() + 1_000_000 : 2 * this.getLimit() );
        }

        this.set(last++, value);
    }

    int pop(){
        return this.get(--last);
    }

    int top(){
        return this.get(last);
    }
}