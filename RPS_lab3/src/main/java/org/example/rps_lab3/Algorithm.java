package org.example.rps_lab3;

import com.mysql.cj.conf.ConnectionUrlParser;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.concurrent.TimeUnit;

public class Algorithm {

    public static Map.Entry<List<Integer>, Long> combSort(List<Integer> input) {
        List<Integer> resultList = new ArrayList<>(input);
        int step = resultList.size();
        boolean flag = false;

        long startTime = System.nanoTime();

        while (step > 1 || flag) {
            if (step > 1) {
                step = step * 4 / 5;
            }
            flag = false;
            int i = 0;
            while (i + step < resultList.size()) {
                if (resultList.get(i).compareTo(resultList.get(i + step)) > 0) {
                    flag = true;
                    Collections.swap(resultList, i, i + step);
                }
                i += step;
            }
        }

        long endTime = System.nanoTime();
        long result = (endTime - startTime);

        Map.Entry<List<Integer>,Long> pair = Map.entry(resultList,result);

        return pair;
    }

}
