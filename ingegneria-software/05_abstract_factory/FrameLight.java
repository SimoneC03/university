import java.awt.Color;

/*
 * This class represents a Product which implements the Frame AbstractProduct interface
 * and can be created by a ConcreteFactory.
 * 
 * This implementation exposes a light version of the Frame
 */

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
