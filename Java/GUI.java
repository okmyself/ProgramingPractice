import java.awt.*;

class GUI {
    public static void main(String[] agrs) {
        Frame myapp = new Frame("Demo");
        myapp.setLayout(new BorderLayout());
        Label label = new Label();
        Panel panel = new Panel();
        panel.setLayout(new GridLayout(4, 4));
        String[] names = {"7", "8", "9", "+", "4", "5", "6", "-", "1", "2", "3", "*", "0", ".", "=", "/"};
        Button[] buttons = new Button[16];
        myapp.add(label, BorderLayout.NORTH);
        myapp.add(panel, BorderLayout.CENTER);
        int index = 0;
        for(Button i: buttons) {
            i = new Button(names[index++]);
            panel.add(i);
        }
        myapp.pack();
        myapp.setVisible(true);
    }
}