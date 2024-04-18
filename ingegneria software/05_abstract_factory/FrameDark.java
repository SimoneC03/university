import java.awt.Color;

public class FrameDark implements Frame {
    @Override
    public String getText() {
        return "Abstract factory example";
    }

    @Override
    public Color getBackgroundColor() {
        return new Color(42, 42, 42);
    }
}
