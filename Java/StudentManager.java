package Java;

import java.util.Comparator;
import java.util.Vector;

//实现学生的插入方法
public class StudentManager {
    public static boolean add(Vector<Student> v, Student stu) {
        v.addElement(stu);
        return true;
    }

    // 实现学生的移除方法
    public static Student remove(Vector<Student> v, int i) {
        v.remove(i);
        if (i > v.size()) {
            return null;
        } else
            return v.elementAt(i);
    }

    // 实现学生的举例方法
    public static Student get(Vector<Student> v, int i) {
        if (i > v.size()) {
            return null;
        } else
            return v.elementAt(i);
    }

    // 实现学生的修改方法
    public static void set(Vector<Student> v, int i, Student stu) {
        v.setElementAt(stu, i);
    }

    // 实现学生的浏览方法
    public static void display(Vector<Student> v) {
        for (Student i : v) {
            System.out.println(i.toString());
        }
    }

    // 实现学生的统计人数方法
    public static int size(Vector<Student> v) {
        return (v.size());
    }

    // 实现学生的查找
    public static Student search(Vector<Student> v, String name) {
        int i;
        for (i = 0; i < v.size(); i++) {
            if (v.elementAt(i).name == name)
                break;
            if (i == v.size())
                return null;
        }
        return v.elementAt(i);

    }
}

// 实现学生的排序方法，采用comparator方法
class ComparatorStudent implements Comparator<Student> {

    @Override
    public int compare(Student o1, Student o2) {
        if (o1.score > o2.score)
            return 1;
        else if (o1.score == o2.score)
            return 0;
        else
            return -1;
    }
}
