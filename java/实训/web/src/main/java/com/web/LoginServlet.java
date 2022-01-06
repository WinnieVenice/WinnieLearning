package com.web;

import com.dao.UserDao;
import com.enity.User;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.sql.SQLException;

@WebServlet (name ="login",urlPatterns ={"/login","/logout"})
public class LoginServlet extends HttpServlet {
    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        String randomCode = (String) session.getAttribute("randomCode"); //随机生成的验证码
        String yzmCode = req.getParameter("yzmCode");
        String username = req.getParameter("username");
        String password = req.getParameter("password");
        if(!randomCode.equalsIgnoreCase(yzmCode))
        {
            req.setAttribute("errorMsg","验证码错误");
            req.getRequestDispatcher("/login.jsp").forward(req,resp);
        }
        try {
            User user = UserDao.loginUser(username, password);
            if(user.getUsername()!=null&&user.getPassword()!=null)
            {
                session.setAttribute("user",user);
                //req.setAttribute("user",user);
                resp.sendRedirect(getServletContext().getContextPath()+"/index");
                //req.getRequestDispatcher("/index").forward(req,resp);

            }
            else
            {
                req.setAttribute("errorMsg","账号或密码错误");
                req.getRequestDispatcher("/login.jsp").forward(req,resp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        HttpSession session = req.getSession();
        session.invalidate();
        resp.sendRedirect(req.getContextPath()+"/login.jsp");
    }
}
