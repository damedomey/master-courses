import java.util.Stack;

public class Main {
    public static void main(String[] args) {
        int sum = 0;
        Stack<Integer> stack = new Stack<>();

        long start = System.nanoTime();
        for(int i = 0; i <1_000_000; i++){
            stack.push(i);
        }

        for (int i = 0; i <1_000_000; i++){
            sum += stack.pop();
        }
        System.out.println("Sum = " + sum);
        System.out.println((System.nanoTime() - start)+ " nano seconds");
    }
}