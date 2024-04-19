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

    public static void main(String[] args) throws SQLException
    {
        Connection con = createConnectionByDriverManager("TEST", "test");
        PreparedStatement pstmt = con.prepareStatement("SELECT 'PING' FROM DUAL");
        long startTime = 0;
        long endTime = 0;
        long timeElapsed = 0;
        ResultSet rs = null;
        int i = 0;

        while(true){
            startTime = System.nanoTime();
            rs = pstmt.executeQuery();
            //while (rs.next())
            //{
            //    System.out.println("ID = : " + rs.getString(1));
            //}
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
