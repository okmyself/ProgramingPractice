package 第二次作业;

import java.util.EventObject;

//事件类型
enum EVENT_TYPE {
    MOUSE_EXITED, MOUSE_MOVED, MOUSE_DRAGGED, MOUSE_ENTERED, MOUSE_PRESSED, MOUSE_RELEASED, ACTION_PERFORMED
}

//监听者接口
interface ChessPainterListener {
    public void mouseMoved(ChessPainterEvent e);
    public void mouseExited(ChessPainterEvent e);
    public void mousePressed(ChessPainterEvent e);
    public void mouseReleased(ChessPainterEvent e);
    public void mouseEntered(ChessPainterEvent e);
    public void mouseDragged(ChessPainterEvent e);
    public void actionPerformed(ChessPainterEvent e);
}

//适配器类
class ChessPainterAdapter implements ChessPainterListener {
    @Override
    public void mouseMoved(ChessPainterEvent e) { }
    @Override
    public void mouseExited(ChessPainterEvent e) { }
    @Override
    public void mousePressed(ChessPainterEvent e) { }
    @Override
    public void mouseReleased(ChessPainterEvent e) { }
    @Override
    public void mouseEntered(ChessPainterEvent e) { }
    @Override
    public void mouseDragged(ChessPainterEvent e) { }
    @Override
    public void actionPerformed(ChessPainterEvent e) { }
}

//事件类
class ChessPainterEvent extends EventObject {
    private int x;
    private int y;
    private EVENT_TYPE eventType;

    /**
     * Constructs a prototypical Event.
     *
     * @param source The object on which the Event initially occurred.
     * @throws IllegalArgumentException if source is null.
     */
    public ChessPainterEvent(Object source, EVENT_TYPE eventType) {
        super(source);
        this.x = -1;
        this.y = -1;
        this.eventType = eventType;
    }

    public ChessPainterEvent(Object source, int x, int y, EVENT_TYPE eventType) {
        super(source);
        this.x = x;
        this.y = y;
        this.eventType = eventType;
    }

    public int getX() { return x; }
    public int getY() { return y; }
    public EVENT_TYPE getEventType() { return eventType; }
}