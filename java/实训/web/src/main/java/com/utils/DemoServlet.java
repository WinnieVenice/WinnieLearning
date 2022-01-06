package com.utils;
import cn.hutool.captcha.CaptchaUtil;
import cn.hutool.captcha.CircleCaptcha;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;
@WebServlet(name = "/demo",urlPatterns ="/demo")
public class DemoServlet  extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        CircleCaptcha circleCaptcha = CaptchaUtil.createCircleCaptcha(80, 50);
        HttpSession session = req.getSession();
        session.setAttribute("randomCode",circleCaptcha.getCode());
        circleCaptcha.write(resp.getOutputStream());

    }
}
