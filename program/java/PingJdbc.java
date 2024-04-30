import java.sql.*;
import javax.sql.*;

public class PingJdbc
{
    protected static final String GOLDILOCKS_DRIVER_CLASS = "sunje.goldilocks.jdbc.GoldilocksDriver";
    protected static final String URL_NAMED = "jdbc:goldilocks://192.168.0.120:30009/test?program=MySample";
    protected static final String URL_FOR_DEBUGGING = URL_NAMED + "?global_logger=console&trace_log=on&query_log=on&protocol_log=on";

    public static Connection createConnectionByDriverManager(String id, String password) throws SQLException
    {
        try
        {
            Class.forName(GOLDILOCKS_DRIVER_CLASS);
        }
        catch (ClassNotFoundException sException)
        {
            System.out.println("xx driver");
        }

        return DriverManager.getConnection(URL_NAMED, "TEST", "test");
    }

    public static void main(String[] args) throws SQLException,InterruptedException
    {
        Connection con = createConnectionByDriverManager("TEST", "test");
<<<<<<< HEAD
        PreparedStatement pstmt1 = con.prepareStatement("alter session set trace_long_run_timer = 1");
        pstmt1.execute();
        pstmt1.close();
        PreparedStatement pstmt2 = con.prepareStatement("alter session set trace_long_run_cursor = 10");
        pstmt2.execute();
        pstmt2.close();
        PreparedStatement pstmt3 = con.prepareStatement("alter session set trace_long_run_sql = 10");
        pstmt3.execute();
        pstmt3.close();
        PreparedStatement pstmt = con.prepareStatement("SELECT 'PING' FROM DUAL");
=======
        Statement stmt = con.createStatement();
        stmt.execute("alter session set trace_long_run_timer = 1");
        stmt.execute("alter session set trace_long_run_cursor = 10");
        stmt.execute("alter session set trace_long_run_sql = 10");
       //PreparedStatement pstmt = con.prepareStatement("SELECT 'PING' FROM DUAL");
        PreparedStatement pstmt = con.prepareStatement("SELECT * FROM t1");
>>>>>>> b4a4432ce125652bbd78707082294912666bbc1a
        long startTime = 0;
        long endTime = 0;
        long timeElapsed = 0;
        ResultSet rs = null;
        int i = 0;

        while(true){
            startTime = System.nanoTime();
            rs = pstmt.executeQuery();
            while (rs.next())
            {
<<<<<<< HEAD
                Thread.sleep(1000);
=======
			//    Thread.sleep(500); //1초 대기
>>>>>>> b4a4432ce125652bbd78707082294912666bbc1a
                System.out.println("ID = : " + rs.getString(1));
            }
            endTime = System.nanoTime();
            timeElapsed = endTime - startTime;
            System.out.println("nano seconds : " +  timeElapsed + "  Time : " + new Timestamp(System.currentTimeMillis()));        
            //System.out.println("milli seconds : " +  timeElapsed/1000000);        
            //System.out.println("seconds : " + (double)timeElapsed / 1000);

            rs.close();
            try {
			    Thread.sleep(500); //1초 대기
		    } catch (InterruptedException e) {
			    e.printStackTrace();
		    }
            if(i==1){
                break;
            }
        }
        pstmt.close();
        con.close();
    }
}
