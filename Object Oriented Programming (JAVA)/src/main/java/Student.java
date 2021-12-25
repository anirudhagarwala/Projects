import java.util.Date;
public class Student extends User {
    static int idSeed = 10000;
    public StudyCourse studycourse;
    public String studycoursedesc;

    Student(){
        idSeed++;
    }
    Student(String firstName, String lastName){
        super.firstname = firstName;
        super.lastname = lastName;
        super.id = String.valueOf(idSeed);
        super.domain = Domain.STUDENT;
        idSeed++;
    }
    Student(String firstName, String lastName, Date birthDate){
        super.firstname = firstName;
        super.lastname = lastName;
        super.birthdate = birthDate;
        super.id = String.valueOf(idSeed);
        super.domain = Domain.STUDENT;
        idSeed++;
    }
    public Student(String id, String firstName, String lastName){
        super.firstname = firstName;
        super.lastname = lastName;
        super.id = String.valueOf(id);
        super.domain = Domain.STUDENT;
        idSeed++;
    }
    public Student(String id, String firstName, String lastName, Date birthDate){
        super.firstname = firstName;
        super.lastname = lastName;
        super.birthdate = birthDate;
        super.id = String.valueOf(id);
        super.domain = Domain.STUDENT;
        idSeed++;
    }
    public StudyCourse getStudyCourse() {
        return this.studycourse;
    }
    String getStudyCourseDescription(){
        
        switch (this.studycourse){
            case ME:
                studycoursedesc = "Mechanical Engineering, B.Sc.";
                break;
            case BMS:
                studycoursedesc = "Biomaterials Science, B.Sc.";
                break;
            case EL:
                studycoursedesc = "Electrical and Electronics Engineering, B.Sc.";
                break;
            case IE:
                studycoursedesc = "Industrial Engineering, B.Sc.";
                break;
            case MBB:
                studycoursedesc = "Bionics, M.Sc.";
                break;
            case MME:
                studycoursedesc = "Mechanical Engineering, M.Sc.";
                break;
            case MSE:
                studycoursedesc = "Mechatronic Systems Engineering, B.Sc.";
                break;
            case SCB:
                studycoursedesc = "Science Communication & Bionics, B.Sc.";
                break;
            default:
                break;
        }
        return studycoursedesc;
    }
    void setStudyCourse(StudyCourse newStudyCourse){
        studycourse = newStudyCourse;
    }
    void setStudyCourse(String newStudyCourse1){
        studycourse = StudyCourse.valueOf(newStudyCourse1);
    } 
}
