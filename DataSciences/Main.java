package DataSciences;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Collectors;

public class Main {
    static final int k = 2;
    static private Map<String,Integer> values;
    static String[] dat = {"Black Pearls","Cactus","Clay","Crystal Deposit","Metal Deposit","Obsidian Deposit","Oil Rock","Oil Vein","Rare Flowers","Rich Metal Deposit","Rockarrot","Salt Deposit","Savoroot","Silica Deposit","Sulfur Deposit","Underwater Metal Deposit","Water Vein"};
    static int[] value = {100,5,5,25,25,25,25,50,5,100000,1,5,1,25,5,25,1};
    //                                             ^change
    public static void init() {
        values = new HashMap<>();
        for(int i = 0;i<dat.length;i++) {
            values.put(dat[i],value[i]);
        }
    }
    public static void main(String[] args) throws IOException {
        //implement a kd tree
        init();
        BufferedReader br = new BufferedReader(new FileReader("DataSciences\\coords.txt"));
        List<String> list = br.lines().collect(Collectors.toList());
        Map<String,Coordinate> map = new TreeMap<>();
        for(int i = 0;i<list.size()-1;i+=2) {
            String[] arr = {list.get(i).split("title=\"")[1].trim(),list.get(i+1).replaceAll("[^0-9. ]","").trim()};
            if(!map.containsKey(arr[1])) {
                String[] temper = arr[1].split(" ");
                double[] coords = {Double.parseDouble(temper[0]),Double.parseDouble(temper[temper.length-1])};
                map.put(arr[1],new Coordinate(coords[0],coords[1]));
            }
            map.get(arr[1]).list.add(new Resource(arr[0],values.get(arr[0])));
        }
        Set<Coordinate> set = new HashSet<>(map.values());
        Tree tree = new Tree(k);
        for(Coordinate x : set) tree.insert(x);
        Scanner sc = new Scanner(System.in);
        while(true) {
            System.out.print("Enter coords(x,y): ");
            String points[] = sc.nextLine().trim().split(" ");
            System.out.println(tree.nearestNeighbor(new double[]{Double.parseDouble(points[0]),Double.parseDouble(points[1])}));
            System.out.print("Quit: ");
            if(sc.nextLine().equalsIgnoreCase("yes")) break;
        }
        sc.close();
        br.close();
        /*PrintWriter writer = new PrintWriter("DataSciences\\out.txt");
        for(int i = 0;i<1000;i++) {
            Coordinate t = new Coordinate(Math.round(Math.random()*100 * 10.0) / 10.0,Math.round(Math.random()*100 * 10.0) / 10.0);
            writer.write(t.points[0] + " " + t.points[1] + " " + tree.nearestNeighbor(t).toString()+"\n");
        }
        writer.close()*/
    }
}