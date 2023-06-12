package Java;

public class Student {
     int num;
     String name, gender, hobies;
     double score;

     // 构造方法
     public Student(int num, String gender, String name, double score, String hobies) {
          this.gender = gender;
          this.name = name;
          this.score = score;
          this.num = num;
          this.hobies = hobies;
     }

     // set和get方法

     public void setNum(int newNum) {
          num = newNum;
     }

     public void setName(String newName) {
          name = newName;
     }

     public void setGender(String newGender) {
          gender = newGender;
     }

     public void setscore(double newscore) {
          score = newscore;
     }

     public void setHobies(String newhobies) {
          hobies = newhobies;
     }

     public int getNum() {
          return num;
     }

     public String getName() {
          return name;
     }

     public String getGender() {
          return gender;
     }

     public String getHobobies() {
          return hobies;
     }

     public double getScore() {
          return score;
     }

     // toString方法
     public String toString() {
          return "Student{id=" + num + "," + "姓名=" + name + "," + "性别=" + gender + "," + "学分绩=" + score + "," + "爱好="
                    + hobies + "}";
     }

}
