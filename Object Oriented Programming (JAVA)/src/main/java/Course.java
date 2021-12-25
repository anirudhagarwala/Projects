public class Course {
    private String id;
    public int credit;
    public String name;
    public Professor lecturer;

    Course(){

    }
    Course(String ID, String Name, Professor Lecturer, int Credit){
        this.id = ID;
        this.name = Name;
        this.lecturer = Lecturer;
        this.credit = Credit;
    }
    public String getID(){
        return this.id;
    }
    public String getName(){
        return this.name;
    }

    public void setName(String Name){
        this.name = Name;
    }
    public void setLecturer(Professor Lecturer){
        this.lecturer = Lecturer;
    }
    public Professor getLecturer(){
        return this.lecturer;
    }
    public int getCredit(){
        return this.credit;
    }
    public void setCredit(int Credit){
        this.credit = Credit;
    }
}