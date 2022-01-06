package com.dao;

import com.enity.Product;
import com.utils.JDBCUtils;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class ProductDao {
    public static  List<Product> gethot() throws SQLException {
        Connection connection = JDBCUtils.getConnection();
        Statement statement = connection.createStatement();
        String sql="select * from product where is_hot=1";
        ResultSet resultSet = statement.executeQuery(sql);
        List<Product> list=new ArrayList<Product>();
        while(resultSet.next())
        {
            Product product=new Product();
            product.setPid(resultSet.getString("pid"));
            product.setCid(resultSet.getInt("cid"));
            product.setIs_hot(resultSet.getInt("is_hot"));
            product.setMarket_price(resultSet.getDouble("market_price"));
            product.setShop_price(resultSet.getDouble("shop_price"));
            product.setPname(resultSet.getString("pname"));
            product.setPimage(resultSet.getString("pimage"));
            list.add(product);
        }
        return list;
    }

    public static  List<Product> getnew() throws  SQLException
    {
        Connection connection = JDBCUtils.getConnection();
        Statement statement = connection.createStatement();
        String sql="select * from product order by pdate DESC LIMIT 10;";
        ResultSet resultSet = statement.executeQuery(sql);
        List<Product> list=new ArrayList<Product>();
        while(resultSet.next())
        {
            Product product=new Product();
            product.setPid(resultSet.getString("pid"));
            product.setCid(resultSet.getInt("cid"));
            product.setIs_hot(resultSet.getInt("is_hot"));
            product.setMarket_price(resultSet.getDouble("market_price"));
            product.setShop_price(resultSet.getDouble("shop_price"));
            product.setPname(resultSet.getString("pname"));
            product.setPimage(resultSet.getString("pimage"));
            list.add(product);
        }
        return list;
    }
}
