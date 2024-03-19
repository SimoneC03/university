import java.io.File;
import java.io.LineNumberReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class Payments {
    private List<String> amounts = new ArrayList<>();
    private float total, maxValue;

    public void readFile(String path, String name) throws IOException {
        LineNumberReader f = new LineNumberReader(new FileReader(new File(path, name)));
        while (true) {
            String line = f.readLine();
            if (line == null)
                break;
            insertAmount(line);
        }
        f.close();
    }

    public void insertAmount(String line) {
        amounts.add(line);
    }

    public void calcMax() {
        maxValue = 0;
        for (String el : amounts) {
            if (maxValue < Float.parseFloat(el))
                maxValue = Float.parseFloat(el);
        }
    }

    public void calcTotal() {
        total = 0;
        for (String el : amounts) {
            total += Float.parseFloat(el);
        }
    }

    public void drop() {
        amounts = new ArrayList<>();
        total = maxValue = 0;
    }

    public float getMax() {
        return maxValue;
    }

    public float getTotal() {
        return total;
    }

    public static void main(String args[]) {
        System.err.println("Calculating total of amounts...");
        try {
            Payments p = new Payments();
            p.readFile("./", "amounts.txt");
            p.calcTotal();
            System.err.println("Total of amounts is: " + p.getTotal());
        } catch (Exception e) {
            System.err.println("An error has occurred while calculating total amounts");
        }
    }
}