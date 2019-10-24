package 第一次作业_2;

import java.text.ParseException;
import java.text.SimpleDateFormat;

public class General {
    /* 检查日期是否存在，不存在返回null，否则返回特定日期格式yyyy-MM-dd */
    public static String checkDate(int year, int month, int day) { return checkDate(year + "-" + month + "-" + day); }
    public static String checkDate(String date) {
            SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd");
            try {
                dateFormat.setLenient(false);   /* 严格验证日期是否有效 */
                dateFormat.parse(date);
            } catch (ParseException e) {
                return null;
            }
            return date;
        }
//    private static String checkDate(int year, int month, int day) {
//        if (year < 1800 || year > 2018) return null;
//        if (month < 1 || month > 12) return null;
//        if (day < 1) return null;
//        int daymax;
//        switch (month) {
//            case 1:
//            case 3:
//            case 5:
//            case 7:
//            case 8:
//            case 10:
//            case 12:
//                daymax = 31;
//                break;
//            case 2:             /* 判断是否闰年 */
//                if (year % 400 == 0)
//                    daymax = 29;
//                else if (year % 4 == 0 && year % 100 != 0)
//                    daymax = 29;
//                else
//                    daymax = 28;
//                break;
//            default:
//                daymax = 30;
//                break;
//        }
//        if (day > daymax) return null;
//        return year + "-" + ((month < 10) ? "0" : "") + month + ((day < 10) ? "0" : "") + day;
//    }
}
