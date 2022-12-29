package Binary_Trees;

import java.util.Comparator;

public class Runner {
    public static void main(String[] args) {
        Integer[] values = {0,3204,6563,545,655,3254,643,5,4356,565,4};
        BTree<Integer> tree = new BTree<>();
        for(int x : values) {
            tree.insert(x);
        }
        System.out.println(tree.getList(Comparator.naturalOrder()).toString());
        System.out.println(tree.contains(3204));
    }
}