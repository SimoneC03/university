import java.awt.Container;

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
