import java.io.*;

class shiyan7_3_2 {
    public static void main(String[] args) {
        try {
            MatrixEx squareMatrix = new MatrixEx(new File("SquareMatrix.txt"));
            MatrixEx matrix1 = new MatrixEx(new File("Matrix1.txt"));
            double[][] arrayMatrix2 = {
                {2, 4, 6, 6, 2},
                {3, 6, 1, 2, 6},
                {9, 5, 1, 9, 1},
                {2, 5, 2, 9, 7}
            };
            MatrixEx matrix2 = new MatrixEx(arrayMatrix2);
            matrix2.saveMatrix(new File("Matrix2.txt"));
            //输出各矩阵
            System.out.println("Square matrix:");
            System.out.println(squareMatrix.toString());
            System.out.println("Matrix1:");
            System.out.println(matrix1.toString());
            System.out.println("Matrix2:");
            System.out.println(matrix2.toString());
            //计算加减乘除
            System.out.println("matrix1 + matrix2:");
            System.out.println(matrix1.add(matrix2));
            System.out.println("matrix1 - matrix2:");
            System.out.println(matrix1.minus(matrix2));
            System.out.println("squareMatrix · squareMatrix:");
            System.out.println(squareMatrix.multiple(squareMatrix));
            System.out.println("squreMatrix的逆矩阵:");
            System.out.println(squareMatrix.inverse());
            System.out.println("squreMatrix / squareMatrix:");
            System.out.println(squareMatrix.divide(squareMatrix));
        } catch(FileNotFoundException e) {
            System.out.println("File not found!");
        } catch(MatrixEx.MatrixNotMatchOperationRuleException e) {
            e.printErrorMessage();
        }
    }
}

class MatrixEx extends Matrix {
    public MatrixEx() {}
    public MatrixEx(int row, int range) { super(row, range); }
    public MatrixEx(double[][] matrix) { super(matrix); }
    public MatrixEx(File matrixFile) throws FileNotFoundException { setMatrix(matrixFile); }
    public void saveMatrix(File matrixFile) throws FileNotFoundException {
        RandomAccessFile rand = new RandomAccessFile(matrixFile, "rw");
        double[][] matrix = getMatrix();
        int row = matrix.length;
        int range = (row > 0) ? matrix[0].length : 0;
        StringBuffer str = new StringBuffer(row + " " + range + '\n');
        for (double[] m: matrix) {
            for (double n: m) {
                str.append(n);
                str.append(' ');
            }
            str.append('\n');
        }
        try {
            rand.seek(0);
            rand.writeChars(str.toString());
        } catch(Exception e) {
            System.out.println("Saving failed!");
        } finally {
            try {
                rand.close();
            } catch(IOException e) {
                System.out.println("IOError!");
            }
        }
    }
    public MatrixEx add(Matrix another) throws MatrixNotMatchOperationRuleException {
        double[][] matrix1 = getMatrix();
        double[][] matrix2 = another.getMatrix();
        if(matrix1.length == 0 || matrix2.length == 0) {
            throw new MatrixNotMatchOperationRuleException("At least one empty matrix was found!");
        } else if(matrix1.length != matrix2.length || matrix1[0].length != matrix2[0].length) {
            throw new MatrixNotMatchOperationRuleException("Two matrices to be added must have the same row and range!");
        }
        int row = matrix1.length;
        int range = matrix1[0].length;
        double[][] result = new double[row][range];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < range; j++) {
                result[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return new MatrixEx(result);
    }
    public MatrixEx minus(Matrix another) throws MatrixNotMatchOperationRuleException {
        double[][] matrix1 = getMatrix();
        double[][] matrix2 = another.getMatrix();
        if(matrix1.length == 0 || matrix2.length == 0) {
            throw new MatrixNotMatchOperationRuleException("At least one empty matrix was found!");
        } else if(matrix1.length != matrix2.length || matrix1[0].length != matrix2[0].length) {
            throw new MatrixNotMatchOperationRuleException("Two matrices to be minused must have the same row and range!");
        }
        int row = matrix1.length;
        int range = matrix1[0].length;
        double[][] result = new double[row][range];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < range; j++) {
                result[i][j] = matrix1[i][j] - matrix2[i][j];
            }
        }
        return new MatrixEx(result);
    }
    //矩阵乘矩阵
    public MatrixEx multiple(Matrix another) throws MatrixNotMatchOperationRuleException {
        double[][] matrix1 = getMatrix();
        double[][] matrix2 = another.getMatrix();
        if(matrix1.length == 0 || matrix2.length == 0) {
            throw new MatrixNotMatchOperationRuleException("At least one empty matrix was found!");
        } else if(matrix1[0].length != matrix2.length) {
            throw new MatrixNotMatchOperationRuleException("The first matrix's range must equals the second matrix's row!");
        }
        int row = matrix1.length;
        int range = matrix2[0].length;
        double[][] result = new double[row][range];
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < range; j++) {
                result[i][j] = 0;
                int n = matrix1[0].length;
                for(int k = 0; k < n; k++) {
                    result[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return new MatrixEx(result);
    }
    //数乘矩阵
    public MatrixEx multiple(double number) {
        int row = getRow();
        int range = getRange();
        double[][] matrix = getMatrix();
        double[][] result = new double[row][range];
        for(int i = 0; i < row; i++)
            for(int j = 0; j < range; j++)
                result[i][j] = matrix[i][j] * number;
        return new MatrixEx(result);
    }
    //矩阵除法
    public MatrixEx divide(MatrixEx another) throws MatrixNotMatchOperationRuleException {
        return multiple(another.inverse());
    }
    //矩阵除以一个数
    public MatrixEx divide(double number) {
        int row = getRow();
        int range = getRange();
        double[][] matrix = getMatrix();
        double[][] result = new double[row][range];
        for(int i = 0; i < row; i++)
            for(int j = 0; j < range; j++)
                result[i][j] = matrix[i][j] / number;
        return new MatrixEx(result);
    }
    public void setMatrix(File matrixFile) throws FileNotFoundException {
        RandomAccessFile rand = new RandomAccessFile(matrixFile, "r");
        try {
            int row, range;
            rand.seek(0);
            row = (int)getNextData(rand);
            range = (int)getNextData(rand);
            double[][] matrix = new double[row][range];
            for(int i = 0; i < row; i++)
                for (int j = 0; j < range; j++) {
                    matrix[i][j] = getNextData(rand);
                }
            setMatrix(matrix);
        } catch(Exception e) {
            System.out.println("Unidentified file!");
        } finally {
            try {
                rand.close();
            } catch(IOException e) {
                System.out.println("IOError!");
            }
        }
    }
    private double getNextData(RandomAccessFile randomAccessFile) throws IOException {
        String str = "";
        int ch;
        do
            ch = randomAccessFile.read();
        while((char)ch == ' ' || (char)ch == '\n');
        while(ch != -1 && (char)ch != ' ' && (char)ch != '\n') {
            str += (char)ch;
            ch = randomAccessFile.read();
        }
        return Double.parseDouble(str);
    }
    /**
     * 求伴随矩阵
     */
    public MatrixEx getCompanionMatrix() throws MatrixNotMatchOperationRuleException {
        if(getRow() != getRange()) throw new MatrixNotMatchOperationRuleException("Only square matrix have companion matrix.");
        int n = getRow();
        double[][] companionMatrix = new double[n][n];
        Detaminate det;
        try {
            det = new Detaminate(this);
        } catch(Detaminate.DetaminateRangeNotMatchRowException e) { return null; }
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                companionMatrix[i][j] = det.getAlgebraicCofactor(j, i);
        return new MatrixEx(companionMatrix);
    }
    /**
     * 求逆矩阵：伴随矩阵除以行列式
     */
    public MatrixEx inverse() throws MatrixNotMatchOperationRuleException {
        try {
            return getCompanionMatrix().divide(new Detaminate(this).toValue());
        } catch(Detaminate.DetaminateRangeNotMatchRowException e) {
            throw new MatrixNotMatchOperationRuleException("This matrix can't be inversed.");
        }
    }
    class MatrixNotMatchOperationRuleException extends Exception {
        String errorMsg = "These two matrices can't perform this operation.";
        MatrixNotMatchOperationRuleException() { 
            super("These two matrices can't perform this operation.");
        }
        MatrixNotMatchOperationRuleException(String msg) { 
            super(msg);
            errorMsg = msg;
        }
        void printErrorMessage() { System.out.println(errorMsg); }
    }
}
/**
 * 行列式类
 */
class Detaminate {
    private int n;      //n阶行列式
    private double[][] detaminate;
    
    public Detaminate() {}
    public Detaminate(int n) {
        this.n = n > 0 ? n : 0;
        detaminate = new double[this.n][this.n];
    }
    public Detaminate(double[][] detaminate) throws DetaminateRangeNotMatchRowException { setDetaminate(detaminate); }
    public Detaminate(Matrix matrix) throws DetaminateRangeNotMatchRowException { 
        setDetaminate(matrix.getMatrix());
    }
    public int getN() { return n; }
    public Double getElem(int i, int j) {
        if (i < n && i >= 0 && j < n && j >= 0) {
            return detaminate[i][j];
        }
        else return null;
    }
    public double[][] getDetaminate() { return detaminate; }
    public void setDetaminate(double[][] detaminate) throws DetaminateRangeNotMatchRowException {
        n = detaminate.length;
        if(n != 0 && n != detaminate[0].length)
            throw new DetaminateRangeNotMatchRowException();
        this.detaminate = detaminate;
    }
    public void setElem(int i, int j, double v) {
        if (i < n && i >= 0 && j < n && j >= 0) {
            detaminate[i][j] = v;
        }
    }
    public boolean equals(Detaminate a) {
        if (a.getN() != n) {
            return false;
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (detaminate[i][j] != a.getElem(i, j))
                        return false;
                }
            }
            return true;
        }
    }
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (int i = 0; i < n; i++) {
            str.append("┃\t");
            for (int j = 0; j < n; j++)
                str.append((double)Math.round(detaminate[i][j] * 1e4) / 1e4 + "\t");
            str.append("┃\n");
        }
        return str.toString();
    }

    class DetaminateRangeNotMatchRowException extends Exception {
        String errorMsg = "Detaminate must has the same row and range.";
        DetaminateRangeNotMatchRowException() { 
            super("Detaminate must has the same row and range.");
        }
        DetaminateRangeNotMatchRowException(String msg) { 
            super(msg);
            errorMsg = msg;
        }
        void printErrorMessage() { System.out.println(errorMsg); }
    }
    /**
     * 求余子式
     * @return 失败返回null
     */
    public Detaminate getCofactor(int i, int j) {
        if(i < n && j < n) {
            double[][] cofactor = new double[n - 1][n - 1];
            for(int p = 0; p < n; p++) {
                int row;
                if(p < i) row = p;
                else if(p == i) continue;
                else row = p - 1;

                for(int q = 0; q < n; q++) {
                    int range;
                    if(q < j) range = q;
                    else if(q == j) continue;
                    else range = q - 1;

                    cofactor[row][range] = detaminate[p][q];
                }
            }
            try {
                return new Detaminate(cofactor);
            } catch(DetaminateRangeNotMatchRowException e) {}
        }
        return null;
    }
    /**
     * 求代数余子式
     * @return 失败返回null
     */
    public Double getAlgebraicCofactor(int i, int j) {
        Detaminate cofactor = getCofactor(i, j);
        if(cofactor == null) return null;
        if((i + j) % 2 == 0) return cofactor.toValue();
        else return -cofactor.toValue(); 
    }
    /**
     * 求行列式的值
     */
    public double toValue() {
        if(n == 1) return detaminate[0][0];
        double D = 0;
        for(int i = 0; i < n; i++)
            D += getElem(0, i) * getAlgebraicCofactor(0, i);
        return D;
    }
}
/**
 * 矩阵类
 */
class Matrix {
    private int row, range;
    private double[][] matrix;
    
    public Matrix() {}
    public Matrix(int row, int range) {
        this.row = row > 0 ? row : 0;
        this.range = range > 0 ? range : 0;
        matrix = new double[this.row][this.range];
    }
    public Matrix(double[][] matrix) { setMatrix(matrix); }
    public int getRow() { return row; }
    public int getRange() { return range; }
    public Double getElem(int i, int j) {
        if (i < row && i >= 0 && j < range && j >= 0) {
            return matrix[i][j];
        }
        else return null;
    }
    public double[][] getMatrix() { return matrix; }
    public void setMatrix(double[][] matrix) {
        row = matrix.length;
        if(row != 0) range = matrix[0].length;
        else range = 0;
        this.matrix = matrix;
    }
    public void setElem(int i, int j, double v) {
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
            //左括号
            if(i == 0)
                str.append("┏\t");
            else if(i == row - 1)
                str.append("┗\t");
            else str.append("┃\t");
            //矩阵内容，保留4位小数
            for (int j = 0; j < range; j++)
                str.append((double)Math.round(matrix[i][j] * 1e4) / 1e4 + "\t");
            //右括号
            if(i == 0)
                str.append("┓");
            else if(i == row - 1)
                str.append("┛");
            else str.append("┃");
            str.append("\n");
        }
        return str.toString();
    }
}