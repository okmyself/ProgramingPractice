package 第一次作业_2;

import 第一次作业_1.REvent;

import java.util.Date;

/**
 * 结点类，以链表形式存储，请注意：如果需要两条相交路径（通过同一结点），请不要共用同一Node对象！
 */
class Node {
    private Node previous;
    private REvent node;
    //    private REvent end;
    private Node next;
    private Double distance;    //包装类可以赋值为null

    public Node(REvent node) {
        this(node, null);
    }

    public Node(REvent node, Node next) {
        this.node = node;
        this.next = next;
    }

    public Node(double x, double y) { this(new REvent(x, y)); }

    public REvent getNode() {
        return node;
    }

    /**
     * @param node node不能为null
     */
    public void setNode(REvent node) {
        if (node == null) return;
        this.node = node;
    }

    public Node getNext() {
        return next;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    /**
     * 设置当前运动到的位置距离node的距离，会将前后全部路径的distance置为空指针
     * @param distance 距离node点的位置，可正可负，若超过路径长度，可能被设置到下一段路径，超过后面所有路径长度之和，则设置失败
     * @return 返回是否设置成功
     */
    public boolean setDistance(double distance) {
//        if(distance < 0 || next == null) return false;
//        double length = distance;
//        Path previous, current = this;
//        length -= current.start.distance(current.end);
//        while(length > 0) {
//            previous = current;
//            current = current.next;
//            if(current == null) return false;
//            distance = length;
//            length -= current.start.distance(current.end);
//        }
//        previous.setDistance();

        if (distance > 0 && next == null) return false;         /* 当前结点为最后一个结点 */
        if (distance < 0 && previous == null ) return false;    /* 当前结点为第一个结点 */
        if (distance >= 0) {
            double length = node.distance(next.node);
            if (length < distance) {
                return next.setDistance(distance - length);
            } else {
                this.distance = distance;
                /* 设置后继结点的distance为null */
                Node current = this.next;
                while (current != null) {
                    current.distance = null;
                    current = current.next;
                }
                /* 设置前驱结点的distance为null */
                current = this.previous;
                while (current != null) {
                    current.distance = null;
                    current = current.previous;
                }
            }
        } else {
            double length = node.distance(previous.node);
            return previous.setDistance(length + distance);
        }
        return true;
}

    /**
     * 取得当前结点与next结点构成的路径上的点距当前结点的距离
     * @return 若点不在上述路径上则返回null
     */
    public Double getDistance() { return distance; }

    /**
     * 设置结点与previous结点连接，修改前一结点previous对象的next属性
     * @param previous 前一结点对象，可以为空指针
     * @return 返回previous结点
     */
    public Node addPrevious(Node previous) {
//        if (previous == null) throw new NullPointerException();
        if (previous != null) previous.next = this;
        this.previous = previous;
        return previous;
    }

    public Node addPrevious(double x, double y) { return addPrevious(new Node(x, y)); }

    /**
     * 设置结点与next结点连接，修改后一结点next对象的previous属性
     * @param next 下一结点对象，可以为空指针
     * @return 返回next结点
     */
    public Node addNext(Node next) {
        if (next != null) next.previous = this;
        this.next = next;
        return next;
    }

    public Node addNext(double x, double y) { return addNext(new Node(x, y)); }

    /**
     * 由于设置start属性可能导致路径连通失效，本方法检查从当前结点开始遍历所有的可访问的next和previous结点，验证是否符合前一结点的next == 后一结点previous
     * @return 返回路径是否连通
     */
    public boolean checkAccessable() {
        Node previous, current = this, next;
        while (current != null) {
            next = current.next;
            if (next != null && next.previous != current) return false;
            current = next;
        }
        current = this;
        while (current != null) {
            previous = current.previous;
            if (previous != null && previous.next != current) return false;
            current = previous;
        }
        return true;
    }

    /**
     * 删除当前整条路径上的指定结点，并重新连接previous和next结点
     * @param node 欲删除的结点
     * @return 返回是否删除成功，成功的前提是该点存在并且该点处连通
     */
    public boolean deleteNode(Node node) {
        Node current = this;
        while (current != null) {
            if(current == node) {
                if(current.previous != null)
                    current.previous.next = current.next;
                if (current.next != null)
                    current.next.previous = current.previous;
            }
            current = current.next;
        }
        current = this;
        while (current != null) {
            if(current == node) {
                if(current.previous != null)
                    current.previous.next = current.next;
                if (current.next != null)
                    current.next.previous = current.previous;
            }
            current = current.previous;
        }
        return true;
    }

    /**
     * 找到第一个distance参数不为空的结点，默认先向后找再向前找，保证所找到的结点next参数不为空
     * @return 成功返回distance所处的REvent坐标，其中时间设为new Date(0)，失败返回null
     */
    public REvent getPoint() {
        Node current = getNodeBeforePoint();
        /* 判断是否找到 */
        if (current == null)
            return null;
        else {
            if(current.next == null) return null;
            double x1 = current.node.getX();
            double y1 = current.node.getY();
            double x2 = current.next.node.getX();
            double y2 = current.next.node.getY();
            double l = current.node.distance(current.next.node);
            double x = (x2 - x1) * current.distance / l + x1;
            double y = (y2 - y1) * current.distance / l + y1;
            return new REvent(x, y, new Date(0));
        }

    }

    /**
     * 找到第一个distance参数不为空的结点，默认先向后找再向前找
     * @return 成功返回结点，失败返回null
     */
    public Node getNodeBeforePoint() {
        Node current = this;
        /* 向后寻找 */
        while (current != null && current.distance == null)
            current = current.next;
        /* 如果向后没找到，则向前寻找 */
        if (current == null) {
            current = this;
            while (current != null && current.distance == null)
                current = current.previous;
        }
        return current;
    }

    /**
     * 从路径中删除当前结点
     */
    public void deleteNode() {
        if (this.previous != null)
            this.previous.next = this.next;
        if (this.next != null)
            this.next.previous = this.previous;
    }

//    /**
//     * 置空与当前结点连接的整条路径上的所有结点的distance参数
//     */
//    public void clearPoint() {
//        Node current = this;
//        while(current != null) {
//            current.distance = null;
//            current = current.next;
//        }
//        current = this;
//        while(current != null) {
//            current.distance = null;
//            current = current.previous;
//        }
//    }
}

//class PathCannotAccessException extends Exception {
//    PathCannotAccessException() { this("路径不能连通：请保证当前路径的末尾与下一路径的开头相同！"); }
//    PathCannotAccessException(String msg) { super(msg); }
//}