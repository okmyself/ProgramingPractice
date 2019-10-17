import java.text.DateFormatSymbols;
import java.util.*;

public class MonthTest {
    public static void main(String[] args) {
        Scanner keyin = new Scanner(System.in);
        System.out.print("请输入要显示万年历的年份：");
        int year = keyin.nextInt();
        System.out.print("请输入每行打印月份的数量：");
        int range = keyin.nextInt();
        keyin.close();
        if(range <= 0) {
            System.out.println("每行打印月份的数量必须大于0");
            return;
        }
        // System.out.println("\t\t\t" + month + "月\t\t\t");
        int n = 54;     //设定输出54个等号和星号
        // for(int i = 0; i < n; i++) System.out.print('=');
        // System.out.println(new Month(year, month));
        // for(int i = 0; i < n; i++) System.out.print('*');
        // System.out.println();
        int row = (12 - 1) / range + 1;
        for(int y = 1; y <= row; y++) {
            String[] months = new String[range];
            /* 一行中的日历保存在months数组中 */
            for(int x = 1; x <= range; x++) {
                int month = (y - 1) * range + x;
                if(month > 12) break;
                months[x - 1] = new Month(year, month).toString();
            }

            int line = months[0].split("\n").length;    /* 取出每个月占的行数 */
            /* 打印月份和=号 */
            for(int month = (y - 1) * range + 1; month <= y * range; month++) {
                if(month > 12) break;
                System.out.print("\t\t\t" + month + "月\t\t\t\t");
            }
            System.out.println();
            for(int month = (y - 1) * range + 1; month <= y * range; month++) {
                if(month > 12) break;
                for(int i = 0; i < n; i++) System.out.print('=');
                System.out.print("\t");
            }
            System.out.println();
            /* 打印处于某一行的几个月 */
            for(int i = 0; i < line; i++) {
                String str = "";
                for(int j = 0; j < range; j++) {
                    int month = (y - 1) * range + j + 1;
                    if(month > 12) break;
                    str += months[j].split("\n")[i];
                }
                System.out.println(str);
            }
            /* 打印*号 */
            for(int month = (y - 1) * range + 1; month <= y * range; month++) {
                if(month > 12) break;
                for(int i = 0; i < n; i++) System.out.print('*');
                System.out.print("\t");
            }
            System.out.println();
        }
    }
}

class Month {
    int days;
    String[][] m = new String[7][7];
    /**
     * year为当前年份，month从1开始
     */
    Month(int year, int month) {
        // m[0][0] = "星期日"; 
        // m[0][1] = "星期一";   
        // m[0][2] = "星期二";
        // m[0][3] = "星期三";
        // m[0][4] = "星期四";
        // m[0][5] = "星期五";
        // m[0][6] = "星期六";
        String[] shortWeekDays = new DateFormatSymbols().getShortWeekdays();
        for(int i = 1; i < shortWeekDays.length; i++)
            m[0][i - 1] = shortWeekDays[i];

        int dayOfWeek;
        Calendar cal = Calendar.getInstance();
        cal.set(year, month - 1, 1);                            //第二个参数从0开始
        dayOfWeek = cal.get(Calendar.DAY_OF_WEEK) - 1;          //dayOfWeek星期日是0，星期一是1……
        int day = dayOfWeek;                                    //当前月的第一天是星期几
        // cal.roll(Calendar.MONTH, 1);                         //往后一个月
        // cal.roll(Calendar.DATE, -1);                         //得到当前月的最后一天
        int maxDate = cal.getActualMaximum(Calendar.DATE);      //得到当前月的最大天数
        for (int i = 1; i <= maxDate; i++) {
            int row = (i + day - 1) / 7 + 1;
            int range = dayOfWeek;
            m[row][range] = "" + i;
            dayOfWeek++;
            if(dayOfWeek > 6) dayOfWeek = 0;
        }
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder("");
        for(String i[]: m) {
            str.append("\n");
            for(String j: i) {
                if(j != null) 
                    str.append(j);
                str.append("\t");
            }
        }
        // while(str.toString().endsWith("\t") || str.toString().endsWith("\n"))
        //     str.deleteCharAt(str.length() - 1);
        return str.toString();
    }
}