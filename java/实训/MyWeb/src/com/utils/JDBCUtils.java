package com.utils;
//import com.mysql.jdbc.Driver;
import com.mysql.cj.jdbc.Driver;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

/**
 * @Auther czw
 **/
public class JDBCUtils {
    public static  Connection getConnection() throws SQLException {
        DriverManager.registerDriver(new Driver());
        String url = "jdbc:mysql://localhost:3306/shop";
        String user = "root";
        String pwd = "root";
        Connection connection = DriverManager.getConnection(url, user, pwd);
        return connection;
    }

    public static void main(String[] args) throws SQLException {
        Connection connection = JDBCUtils.getConnection();
        System.out.println(connection);
    }
}
