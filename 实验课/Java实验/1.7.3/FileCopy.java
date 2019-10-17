import java.io.*;
class FileCopy {
    public static void main(String[] args) {
        if(args.length != 2) {
            System.out.println("Usage: java FileCopy srcFile destFile");
            return;
        }
        try {
            FileReader in = new FileReader(new File(args[0]));
            BufferedReader bin = new BufferedReader(in);
            FileWriter out = new FileWriter(new File(args[1]));
            BufferedWriter bout = new BufferedWriter(out);
            int i = 1;
            String str;
            while((str = bin.readLine()) !=  null) {
                bout.write(i + ": " + str);
                bout.newLine();
                i++;
            }
            bout.close();
            out.close();
            bin.close();
            in.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
}