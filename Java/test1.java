package Java;

import java.util.Vector;
import java.util.Collections;

public class test1 {
    public static void main(String[] args) {
        Vector<Student> stus = new Vector<Student>();
        // 为向量添加对象
        Student stu1 = new Student(20020824, "男", "马鲁斯", 79.3, "耍剑");
        Student stu2 = new Student(20020716, "男", "伊克特", 88.2, "学习黑科技");
        Student stu3 = new Student(19920707, "女", "赫利本", 75.2, "化妆");
        Student stu4 = new Student(20021008, "女", "赛大宝", 78.2, "玩splatoon3");
        Student stu5 = new Student(20020502, "男", "猪一卓", 66.2, "睡觉、吃饭");
        // 使用addAll方法一次性添加完元素
        Collections.addAll(stus, stu1, stu2, stu3, stu4, stu5);
        // 下面打印初始数据
        System.out.println("这是原始数据：");
        for (Student i : stus) {
            System.out.println(i.toString());
        }
        System.out.println();
        // 添加适当例子以修改、删除等
        Student stu6 = new Student(20070819, "女", "小茶酱", 82.1, "追剧");
        Student stu7 = new Student(20073812, "男", "李太牛", 79.1, "打羽毛球");
        // 下面测试添加方法、浏览方法
        StudentManager.add(stus, stu6);
        System.out.println("这是采用添加方法之后的数据：");
        StudentManager.display(stus);
        System.out.println();
        // 下面测试移除方法
        StudentManager.remove(stus, 2);
        System.out.println("这是采用移除方法之后的数据：");
        StudentManager.display(stus);
        System.out.println();
        // 下面测试修改方法
        System.out.println("这是修改stu1之后的数据：");
        StudentManager.set(stus, 0, stu7);
        StudentManager.display(stus);
        System.out.println();
        // 下面测试排序方法
        System.out.println("这是按照成绩升序排序的数据：");
        ComparatorStudent Comparator = new ComparatorStudent();
        Collections.sort(stus, Comparator);
        StudentManager.display(stus);
        System.out.println();
        // 下面测试统计人数方法
        System.out.println("总人数为：" + StudentManager.size(stus));
        System.out.println();
        // 下面实现查找方法
        System.out.println("·······························进行查找中··························");
        System.out.println("查找成功！你要找的人信息如下：\n" + StudentManager.search(stus, "赛大宝"));

    }
}
