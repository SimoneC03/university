import java.awt.Color;

public class LabelDark implements Label {
    @Override
    public String getText() {
        return "Dark Theme";
    }

    @Override
    public Color getColor() {
        return new Color(226, 226, 226);
    }
}
