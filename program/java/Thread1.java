
public class Thread1 {
 public static void main(String[] args) {
  // TODO Auto-generated method stub
  GuruThread3 threadguru1 = new GuruThread3("guru1");
  threadguru1.start();
  GuruThread3 threadguru2 = new GuruThread3("guru2");
  threadguru2.start();
  GuruThread3 threadguru3 = new GuruThread3();
  GuruThread3 threadguru4 = new GuruThread3();
  threadguru3.start();
  threadguru4.start();
 }
}

class GuruThread3 implements Runnable {
 Thread guruthread;
 private String guruname;
 GuruThread3() {
  guruname = Thread.currentThread().getName();
 }

GuruThread3(String name) {
  guruname = name;
 }

 @Override
 public void run() {
  System.out.println("Thread running" + guruname);
  for (int i = 0; i < 1000; i++) {
//   System.out.println(guruname);
   System.out.println("xx"+Thread.currentThread().getName());
   try {
    Thread.sleep(1000);
   } catch (InterruptedException e) {
    System.out.println("Thread has been interrupted");
   }
  }
 }

 public void start() {
  System.out.println("Thread started");
  if (guruthread == null) {
   guruthread = new Thread(this, guruname);
   guruthread.start();
  }
 }
}

