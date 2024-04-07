import java.io.File;
import java.io.LineNumberReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class CalcAmounts {
    private final List<String> amounts = new ArrayList<>();

    public int calcTotal(String path, String name) throws IOException {
        FileReader reader = new FileReader(new File(path, name));
        LineNumberReader l = new LineNumberReader(reader);
        String line = l.readLine();
        int total = 0;
        while (true) {
            total += Float.parseFloat(line);
            line = l.readLine();
            if(line == null) break;
        }
        reader.close();
        return total;
    }

    public static void main(String args[]) {
        System.err.println("Calculating total...");
        CalcAmounts c = new CalcAmounts();
        try {
            System.err.println("Total of amounts is: " + c.calcTotal("./", "amounts.txt"));
        } catch (Exception e) {
            System.err.println("An error has occurred while calculating amounts");
        }
    }
}