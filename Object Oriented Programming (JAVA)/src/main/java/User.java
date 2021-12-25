import java.util.Date;

public class User {
    public String id; 
    public String lastname; 
    public String firstname; 
    public Date birthdate; 
    public Domain domain;

    User(){

    }
    User(String ID, Domain dOmain, String firstName, String lastName){
        this.id = ID;
        this.domain = dOmain;
        this.firstname = firstName;
        this.lastname = lastName;
    }
    User(String ID, Domain dOmain, String firstName, String lastName, Date Birthdate){
        this.id = ID;
        this.domain = dOmain;
        this.firstname = firstName;
        this.lastname = lastName;
        this.birthdate = Birthdate;
    }
    String getFirstName(){
        return this.firstname;
    }
    String getLastName(){
        return this.lastname;
    }
    void setFirstName(String firstName){
        this.firstname = firstName;
    }
    void setLastName(String lastName){
        this.lastname = lastName;
    }
    String getID(){
        return this.id;
    }
    Date getBirthDate(){
        return this.birthdate;
    }
    void setBirthDate(Date birthDate){
        this.birthdate = birthDate;
    }
    public Domain getDomain(){
        return domain;
    }
    String getFQUN(){
        String hellooo1;
        if(this.domain == Domain.STUDENT){
            hellooo1 = "@student.hsrw";
        }else{
            hellooo1 = "@staff.hsrw";
        }
        String concat = id+hellooo1;
        return concat;
    }
    String getEmail(){
        String hellooo;
        if(this.domain == Domain.STUDENT){
            hellooo = "hsrw.org";
        }else{
            hellooo = "hochschule-rhein-waal.de";
        }
        String concat2 = firstname+"."+lastname+"@"+hellooo;
        return concat2;
    }
    

}
