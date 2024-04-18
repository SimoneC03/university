import java.awt.Color;

public class LabelLight implements Label {
    @Override
    public String getText() {
        return "Light Theme";
    }

    @Override
    public Color getColor() {
        return new Color(42, 42, 42);
    }
}
