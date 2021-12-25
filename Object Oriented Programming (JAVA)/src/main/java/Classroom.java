import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Calendar;
import java.util.ArrayList;
import java.io.*;
import java.text.ParseException;
import java.text.SimpleDateFormat;

public class Classroom {
    private String id;
    public Course course;
    public String room;
    public String term;
    public ArrayList<Student> participants = new ArrayList<Student>();
    Classroom(){

    }
    Classroom(Course cOurse, String Room){
        this.course = cOurse;
        this.room = Room;
        Date date = new Date();
        Calendar calend = Calendar.getInstance();
        calend.setTime(date);
        int month = calend.get(Calendar.MONTH);
        int year = calend.get(Calendar.YEAR);
        if(month>=3 && month<=9){
            this.term = "SS"+year;
        }else{
            this.term = "WS"+year+"/"+((year%100)+1);
        }
        
        this.id = course.getID()+ "-" + this.getTerm();
    }

    Classroom(Course cOurse, String Room, Date Date){
        this.course = cOurse;
        this.room = Room;
        Calendar calend = Calendar.getInstance();
        calend.setTime(Date);
        int month = calend.get(Calendar.MONTH);
        int year = calend.get(Calendar.YEAR);
        if(month>=3 && month<=9){
            this.term = "SS"+year;
        }else{
            this.term = "WS"+year+"/"+((year%100)+1);
        }
        this.id = course.getID()+ "-" + this.getTerm();
    }

    public Course getCourse(){
        return this.course;
    }
    public String getRoom(){
        return this.room;
    }
    public void setRoom(String Room){
        this.room = Room;
    }
    public String getTerm(){
        return this.term;
    }
    public String getID(){
        return this.id;
    }
    public void addStudent(Student sTudent){
        if(!participants.contains(sTudent)){
            participants.add(sTudent);
        }
    }
    public String getParticipantsEmail(){
        String emaill = "";
        for(int i=0; i<participants.size()-1;i++){
            emaill = emaill + participants.get(i).getEmail() + ", ";
        }
        emaill = emaill + participants.get(participants.size()-1).getEmail();
        return emaill;
    }
    public int getTotalParticipants(){
        return participants.size();
    }
    public boolean isParticipating(Student sTudent){
        if(!participants.contains(sTudent)){
            return false;
        }else{
            return true;
        }
    }
    public void removeStudent(Student sTudent){
        participants.remove(sTudent);
    }
    public void removeAllParticipants(){
        participants.removeAll(participants);
    }

    public boolean load(String filename){
        removeAllParticipants();
        BufferedReader f;
        try{
            f = new BufferedReader(new FileReader(filename));
            String line;
            String lines[];
            while ((line = f.readLine()) != null) {
                lines = line.split(",");
                if (lines[3].equals("-")){
                    Student s1 = new Student(lines[0], lines[1], lines[2]);
                    addStudent(s1);
                }else{
                   SimpleDateFormat sdf = new SimpleDateFormat("dd-mm-yyyy"); 
                   Student s1 = new Student(lines[0], lines[1], lines[2], sdf.parse(lines[3]));
                   addStudent(s1);
                }
            }
            f.close();
            return true;
        }catch (IOException | ParseException ex){
            System.out.println("Error loading from" + filename);
            return false;
        }
    }

    public boolean save(String filename){
        FileWriter fw;
        try {
            fw = new FileWriter(filename);
            //write
            for (int i = 0; i < participants.size();i++){
                Student s = participants.get(i);
                String line = s.getID()+","+s.getFirstName()+","+s.getLastName()+",";
                if (s.getBirthDate()==null){
                    line = line + "-";
                }else{
                    SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy"); 
                    line = line + sdf.format(s.getBirthDate());
                }
                fw.write(line);
                fw.write(System.getProperty( "line.separator" ));
            }
            fw.close();
            return true;
        } catch (IOException ex){
            System.out.println("Error saving into" + filename);
            return false;
        }
        
    }
}
