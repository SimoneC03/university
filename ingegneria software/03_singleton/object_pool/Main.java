public class Main {
    public static void main(String args[]) {
        StudentPool studentPool = StudentPool.getPool();
        Student bob = new Student("Bob");
        studentPool.release(bob);

        // try to read from pool
        try {
            Student s = studentPool.getStudent();
            System.out.println("Student fetched from pool: ");
            System.out.println("Name: " + s.name());
        } catch(Exception e) {
            System.out.println("The Student pool is empty");
        }

        // try yo read from pool without releasing the fetched Student
        try {
            Student s = studentPool.getStudent();
            System.out.println("Student fetched from pool: ");
            System.out.println("Name: " + s.name());
        } catch(Exception e) {
            System.out.println("The Student pool is empty");
        }
    }
}
