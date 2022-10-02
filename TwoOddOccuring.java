public class TwoOddOccuring {

    public static void main(String[] args) {

        // Given an array where all elements appear even number of times except two, print the two odd occurring elements.
        // It may be assumed that the size of array is at-least two.

        int [] arr = {3,8,7,2,2,3,4,3,4,7,7,8,9,9,3,2};
        twoOddOccuring(arr);

    }

    public static void twoOddOccuring(int []arr){
        int xor = 0;
        int a =0, b = 0;
        for(int i : arr){
            xor = xor ^ i;
        }
        int sb = (xor) & ~(xor - 1);

        for(int i : arr){
            if((sb & i) == 0){
                a = a ^ i;
            }
            else{
                b = b ^ i;
            }
        }

        System.out.println(a);
        System.out.println(b);

    }
}
