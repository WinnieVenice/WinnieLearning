package com.web;

import com.dao.ProductDao;
import com.enity.Product;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.SQLException;
import java.util.List;

@WebServlet(name = "IndexServlet",urlPatterns = {"/index"})
public class IndexServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {


    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

        try {
            List<Product> gethot = ProductDao.gethot();
            List<Product> getnew = ProductDao.getnew();
            request.setAttribute("hotProductList",gethot);
            request.setAttribute("newProductList",getnew);
            request.getRequestDispatcher("/index.jsp").forward(request,response);


        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
