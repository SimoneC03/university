import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.util.ArrayList;
import java.util.List;

import javax.sound.sampled.Line;

public class Payments {
    private List<Float> amounts = new ArrayList<>();
    private float total = 0, maxValue = 0;

    public float getMaxValue() {
        return maxValue;
    }

    public float getTotal() {
        return total;
    }

    public void insertAmount(float amount) {
        amounts.add(amount);
    } 

    public void calcMaxValue() {
        maxValue = 0;
        for(Float amount : amounts) {
            if(amount > maxValue) maxValue = amount;
        }
    }

    public void calcTotal() {
        total = 0;
        for(Float amount : amounts) {
            total += amount;
        }
    }

    public void drop() {
        amounts = new ArrayList<>();
        total = maxValue = 0;
    }

    public void readAmountsFromFile(String path, String filename) throws IOException {
        LineNumberReader f = new LineNumberReader(new FileReader(new File(path, filename)));
        while(true) {
            String line = f.readLine();
            if(line == null) {
                f.close();
                return;
            }
            insertAmount(Float.parseFloat(line));            
        }
    }

}
