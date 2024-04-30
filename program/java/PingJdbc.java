import java.sql.*;
import javax.sql.*;

public class PingJdbc
{
    protected static final String GOLDILOCKS_DRIVER_CLASS = "sunje.goldilocks.jdbc.GoldilocksDriver";
    protected static final String URL_NAMED = "jdbc:goldilocks://127.0.0.1:30009/test?program=MySample";
    protected static final String URL_FOR_DEBUGGING = URL_NAMED + "?global_logger=console&trace_log=on&query_log=on&protocol_log=on";

    public static Connection createConnectionByDriverManager(String id, String password) throws SQLException
    {
        try
        {
            Class.forName(GOLDILOCKS_DRIVER_CLASS);
        }
        catch (ClassNotFoundException sException)
        {
        }

        return DriverManager.getConnection(URL_NAMED, "TEST", "test");
    }

    public static void main(String[] args) throws SQLException
    {
        Connection con = createConnectionByDriverManager("TEST", "test");
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
        long startTime = 0;
        long endTime = 0;
        long timeElapsed = 0;
        ResultSet rs = null;
        int i = 0;
        while(true){
            startTime = System.currentTimeMillis();
            rs = pstmt.executeQuery();
            while (rs.next())
            {
                Thread.sleep(1000);
                System.out.println("ID = : " + rs.getString(1));
            }
            endTime = System.currentTimeMillis();
            timeElapsed = endTime - startTime;
            System.out.println("milli seconds : " +  timeElapsed);        
            //System.out.println("seconds : " + (double)timeElapsed / 1000);
            rs.close();
            if(i==1){
                break;
            }
        }

        pstmt.close();
        con.close();
    }
}
