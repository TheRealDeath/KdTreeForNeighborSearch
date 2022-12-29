package Binary_Trees;

import java.util.*;
public class BTree<T extends Object & Comparable<T>> extends Tree<T>{
    private Node root;

    public BTree() {
        root = null;
    }

    private class Node {
        public T value;
        public Node left, right;
        public Node(T value) {
            this.value = value;
        }
        @Override
        public String toString() {
            return value.toString();
        }
    }
    public void insert(T value) {
        size++;
        root = insertRec(root,value);
    }
    private Node insertRec(Node root, T value) {
        if(root == null) return new Node(value);
        if(value.compareTo(root.value) < 0) root.left = insertRec(root.left,value);
        else if(value.compareTo(root.value) > 0) root.right = insertRec(root.right,value);
        return root;
    }
    private List<T> list;
    public List<T> getList(Comparator<T> t) {
        list = new ArrayList<>();
        inOrder(root);
        list.sort(t);
        return list;
    }
    private void inOrder(Node current) {
		if(current != null) {
            inOrder(current.left);
            list.add(current.value);
            inOrder(current.right);
		}
	}

    /*public boolean delete() {

    }*/
    public boolean contains(T key) {
        return containsRec(root, key);
    }
    private boolean containsRec(Node root, T key) {
        if(root.value == key) return true;
        if(key.compareTo(root.value) < 0) return containsRec(root.left,key);
        else if(key.compareTo(root.value) > 0) return containsRec(root.right, key);
        return false;
    }
}