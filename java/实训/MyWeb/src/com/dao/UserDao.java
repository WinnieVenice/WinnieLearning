package com.dao;



import com.enity.User;
import com.utils.JDBCUtils;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/**
 * @Auther czw
 **/
public class UserDao {
    public static  int addUser(User user) throws SQLException {
        Connection connection = JDBCUtils.getConnection();
        String sql="Insert into user(uid,username,password,name,email,birthday,sex) " +
                "values('"+user.getUid()+"','"+user.getUsername()+"','"+user.getPassword()+"','"+user.getName()+"','"+user.getEmail()+"'," +
                "'"+user.getBirthday()+"','"+user.getSex()+"')";
        Statement statement = connection.createStatement();
        int i = statement.executeUpdate(sql);
        return i>0?1:-1;
    }
    public static User loginUser(String name,String pwd) throws SQLException {
        Connection connection = JDBCUtils.getConnection();
        String sql="select * from user where username='"+name+"'and password='"+pwd+"'";
        Statement statement = connection.createStatement();
        User user=new User();
        ResultSet resultSet = statement.executeQuery(sql);
        while(resultSet.next())
        {

            user.setUsername(resultSet.getString("username"));
            user.setPassword(resultSet.getString("password"));
        }
        return user;
    }
    public static List<User> getall() throws SQLException {
        List<User> users=new ArrayList<User>();
        Connection connection = JDBCUtils.getConnection();
        String sql="select * from tb_user ";
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(sql);
        while(resultSet.next())
        {
            User user=new User();

            user.setName(resultSet.getString("username"));
            user.setPassword(resultSet.getString("password"));
            users.add(user);
        }
        return  users;
    }
    public static  int checkUsername(String username) throws SQLException {
        Connection connection = JDBCUtils.getConnection();
        String sql="select * from user where username='"+username+"'";
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(sql);
        if(resultSet.next())return 1;
        else return -1;
    }

    public static void main(String[] args) throws SQLException {
        System.out.println(UserDao.checkUsername("zzz"));
    }

}
