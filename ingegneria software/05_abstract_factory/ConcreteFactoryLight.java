import java.awt.Container;

/*
 * This class represents a ConcreteFactory and implements the operations to create
 * all the families of objects for a light theme.
 */

public class ConcreteFactoryLight implements AbstractFactory {

    @Override
    public Label getLabel() {
        return new LabelLight();
    }

    @Override
    public Frame getFrame() {
        return new FrameLight();
    }
}
