import java.awt.Color;

public class FrameLight implements Frame {
    @Override
    public String getText() {
        return "Abstract factory example";
    }

    @Override
    public Color getBackgroundColor() {
        return new Color(228, 228, 228);
    }
}
