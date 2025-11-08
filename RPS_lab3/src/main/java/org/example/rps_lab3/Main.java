package org.example.rps_lab3;


import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Random;

public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        List<Integer> list = new ArrayList<Integer>();
        Random rand = new Random();
        for (int i = 0; i < 100; i++) {
            list.add(rand.nextInt(1000));
        }

        List<Integer> sorted_list = new ArrayList<Integer>();
        Map.Entry<List<Integer>, Long> pair = Algorithm.combSort(list);

        System.out.println(list);
        System.out.println("t: " + pair.getValue() + " l: " + pair.getKey());
    }
}
