package com.web;

import com.dao.UserDao;
import com.enity.User;
import org.apache.commons.beanutils.BeanUtils;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.sql.SQLException;
import java.util.Map;
import java.util.UUID;

@WebServlet(name = "RegisterServlet",urlPatterns = {"/register"})
public class RegisterServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.setCharacterEncoding("utf-8");
        HttpSession session = request.getSession();
        String randomCode = (String) session.getAttribute("randomCode"); //随机生成的验证码
        String yzmCode = request.getParameter("yzmCode");
        if(!randomCode.equalsIgnoreCase(yzmCode)){
            request.setAttribute("errorMsg","验证码错误");
            request.getRequestDispatcher("/register.jsp").forward(request,response);
            return;
        }
        Map<String, String[]> parameterMap = request.getParameterMap();
        User user=new User();
        try {
            BeanUtils.populate(user,parameterMap);
            String s = UUID.randomUUID().toString().substring(0,32);
            user.setUid(s);
            if(UserDao.checkUsername(user.getUsername())==1)
            {
                request.setAttribute("errorMsg","用户名重复");
                request.getRequestDispatcher("/register.jsp").forward(request,response);
                System.out.println("用户名重复");
                return;
            }
            int i = UserDao.addUser(user);
            if(i==1){
                response.sendRedirect(getServletContext().getContextPath()+"/login.jsp");
            }
            else{
                request.getRequestDispatcher("/register.jsp").forward(request,response);
            }
        } catch (IllegalAccessException e) {
            e.printStackTrace();
        } catch (InvocationTargetException e) {
            e.printStackTrace();
        } catch (SQLException e) {
            e.printStackTrace();
        }


    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {

    }
}
