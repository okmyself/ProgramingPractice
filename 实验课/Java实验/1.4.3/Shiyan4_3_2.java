class Matrix {
    private int row, range;
    private int[][] matrix;
    public Matrix(int row, int range) {
        this.row = row > 0 ? row : 0;
        this.range = range > 0 ? range : 0;
        matrix = new int[this.row][this.range];
    }
    public int getRow() { return row; }
    public int getRange() { return range; }
    public Integer getElem(int i, int j) {
        if (i < row && i >= 0 && j < range && j >= 0) {
            return matrix[i][j];
        }
        else return null;
    }
    public int[][] getMatrix() { return matrix; }
    public void setMatrix(int[][] matrix) {
        if(matrix.length != row)
            return;
        if(matrix[0].length != range)
            return;
        this.matrix = matrix;
    }
    public void setElem(int i, int j, int v) {
        if (i < row && i >= 0 && j < range && j >= 0) {
            matrix[i][j] = v;
        }
    }
    public boolean equals(Matrix a) {
        if (a.getRow() != row) {
            return false;
        } else if (a.getRange() != range) {
            return false;
        } else {
            for (int i = 0; i < row; i++) {
                for (int j = 0; j < range; j++) {
                    if (matrix[i][j] != a.getElem(i, j))
                        return false;
                }
            }
            return true;
        }
    }
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < range; j++)
                str.append(matrix[i][j] + "\t");
            str.append("\n");
        }
        return str.toString();
    }
}

class Shiyan4_3_2 {
    public static void main(String[] args) {
        Matrix m = new Matrix(3, 4);
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 4; j++)
                m.setElem(i, j, (int)(Math.random() * 100));
        System.out.println(m.toString());
    }
}
