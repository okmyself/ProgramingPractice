package 第二次作业;

import java.awt.*;
import java.io.*;

//工具类
class Util {
    //指定文字的中心位置，输出文字
    public static void drawString(String s, Graphics2D g, Font f, int center_x, int center_y) {
        if (s == null) return;
        g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,
                (RenderingHints.VALUE_TEXT_ANTIALIAS_LCD_HRGB));    //抗锯齿
        g.setFont(f);
        FontMetrics fm = g.getFontMetrics(f);
        int textWidth = fm.stringWidth(s);
        int ascent = fm.getAscent();    //基线上面的高度
        int descent = fm.getDescent();  //基线下面的高度
        int x = center_x - textWidth / 2;
        int y = center_y + (ascent - descent) / 2;
        g.drawString(s, x, y);
    }
    //通过文件加载字体，找不到或无法载入将返回null
    public static Font loadFont(Object obj, String fontFilePath, int style, int size) {
        InputStream is = obj.getClass().getResourceAsStream(fontFilePath);
        Font f;
        try {
            f = Font.createFont(Font.TRUETYPE_FONT, is);
        } catch (FontFormatException | IOException e) {
            return null;
        }
        return f.deriveFont(style, size);       //通过复制此Font对象并应用新样式和大小，创建一个新Font对象。
    }
    //通过路径载入一个图片，返回Image对象
    public static Image loadImage(String picturePath) {
        Toolkit imgTool = Toolkit.getDefaultToolkit();
        return imgTool.getImage(picturePath);
    }
}
//二元组
//class Pair<A, B> {
//    public final A first;
//    public final B second;
//    public Pair(A a, B b){
//        first = a;
//        second = b;
//    }
//
//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        Pair<?, ?> pair = (Pair<?, ?>) o;
//        return Objects.equals(first, pair.first) &&
//                Objects.equals(second, pair.second);
//    }
//
//    @Override
//    public int hashCode() {
//
//        return Objects.hash(first, second);
//    }
//
//    @Override
//    public String toString() {
//        return "(" + first + ", " + second + ")";
//    }
//}