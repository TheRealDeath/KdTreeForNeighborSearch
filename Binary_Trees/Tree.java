package Binary_Trees;

public abstract class Tree<T extends Comparable<T>> {
    protected int size;

    public abstract void insert(T value);
    //public abstract boolean delete();
    public abstract boolean contains(T key);
    public int getSize() {return size;}
}
