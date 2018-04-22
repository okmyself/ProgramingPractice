import java.awt.*;
import java.applet.*;
public class cosTable extends Applet {
	
	public void paint(Graphics g) {
		for(int i = 30; i <= 60; i++) {
			double r = i * Math.PI / 180;
			g.drawString(Math.cos(r) + "", 20, 20 * (i - 29));
		}
	}
}