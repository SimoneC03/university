/*
 * This class is implemented using the Object pool and the Singleton patterns.
 * The "pool" contains a set of initialized objects kept ready to use and 
 * it cannot be directly instanciated using the "new" operator to ensure it 
 * only have one instance during the execution of the program 
 */


import java.util.List;
import java.util.ArrayList;

public class StudentPool {
    private static StudentPool instance = new StudentPool();
    private List<Student> pool = new ArrayList<>();

    private StudentPool() {}

    public static StudentPool getPool() {
        return instance;
    }
    
    public Student getStudent() throws Exception {
        // If pool has at least one Student, return the first inserted student
        if(pool.size() > 0) return pool.remove(0);
        else throw new Exception("Pool is empty");
    }
    
    public boolean isEmpty() {
        return pool.size() > 0;
    }

    public void release(Student s) {
        pool.add(s);
    }
}
