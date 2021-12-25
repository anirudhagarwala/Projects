import java.util.Date;
public class Professor 
            extends User{
    Faculty faculty = Faculty.valueOf("TUB");
    Campus campus = Campus.valueOf("KLE");
    int phone = 0;
    String facultyS;
    Professor(){

    }
    Professor(String ID, String firstName, String lastName){
        super.id = ID;
        super.firstname = firstName;
        super.lastname = lastName;
        super.domain = Domain.STAFF;
    }
    Professor(String ID, String firstName, String lastName, Date birthDate){
        super.id = ID;
        super.firstname = firstName;
        super.lastname = lastName;
        super.birthdate = birthDate;
        super.domain = Domain.STAFF;
    }
    void setFaculty(Faculty fAculty){
        this.faculty = fAculty;
        if(this.faculty == Faculty.KU){
            this.campus = Campus.KL;
        
        }else{
            this.campus = Campus.KLE;
        }
    }
    Faculty getFaculty(){
        return faculty;
    }
    String getFacultyString(){
        switch (this.faculty){
            case TUB:
                facultyS = "Technology and Bionics";
                break;
            case LS:
                facultyS = "Life Sciences";
                break;
            case GO:
                facultyS = "Society and Economics";
                break;
            case KU:
                facultyS = "Communication and Environment";
                break;
            default:
                break;
        }
        return facultyS;
    }
    void setPhone(int Phone){
        this.phone = Phone;
    }
    String getPhone(){
        String ph;
        if(this.campus == Campus.KLE){
            ph = "+49 2821 806 73 "+ String.valueOf(this.phone);
        }else {
            ph = "+49 2842 908 "+ String.valueOf(this.phone);
        }
        return ph;
    }
}
