package Java;

import java.util.Enumeration;
import java.util.Vector;

public class Book {
    private String name;
    private int price;
    public Book(String name,int price){
        this.name = name;
        this.price = price;
    }
    public void setname(String newname){
        name = newname;
    }
    public void setprice(int newprice){
        price = newprice;
    }
    public String getName(){return name;}
    public int getPrice(){return price;}
    public String toString(){
        return "书名《"+name+"》"+","+"价格为"+price+"元";
    }
public static void main(String[] args){
    Book a = new Book("《基督山伯爵》",68);
    Book b = new Book("《俗世奇人》",23);
    Book c = new Book("《围城》",32);
    Vector<Book> v = new Vector<Book>(3,1);//向量的创建
    v.addElement(b);
    v.addElement(a);
    v.addElement(c);
    System.out.println(v.elementAt(0));
    System.out.println(v.elementAt(1));
    System.out.println(v.elementAt(2));
    
}
}
