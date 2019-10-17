import java.applet.*;
import java.awt.*;

public class CosTable extends Applet {
    public void paint(Graphics g) {
        for(int i = 30; i <= 60; i++) {
            g.drawString("cos(" + i + "°)=" + Math.cos((i * Math.PI) / 180), 20, 20 * (i - 29));
        }
    }
}
