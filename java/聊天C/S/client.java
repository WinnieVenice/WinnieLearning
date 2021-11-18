import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextArea;
import javax.swing.JTextField;

public class client {
    static String ip;
    static String port;
    static JFrame user_frame;
    static String name;
    public static void main(String[] args) throws Exception {
        login_dialog();
    }
    private static void login_dialog() {
        JFrame login_frame = new JFrame("user login");
        login_frame.setSize(400, 300);
        int login_frame_w = login_frame.getWidth() / 5, login_frame_h = login_frame.getHeight() / 11;
        login_frame.setLocationRelativeTo(null);
        login_frame.setResizable(false);
        login_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        login_frame.setLayout(null);
        Container con = login_frame.getContentPane();
        JLabel user_name_tag = new JLabel("用户名: ");
        user_name_tag.setBounds(login_frame_w, login_frame_h, login_frame_w, login_frame_h);
        con.add(user_name_tag);
        JTextField user_name = new JTextField();
        user_name.setBounds(login_frame_w * 2, login_frame_h, login_frame_w * 2, login_frame_h);
        con.add(user_name);
        JLabel user_pwd_tag = new JLabel("密码: ");
        user_pwd_tag.setBounds(login_frame_w, login_frame_h * 3, login_frame_w, login_frame_h);
        con.add(user_pwd_tag);
        JTextField user_pwd = new JTextField();
        user_pwd.setBounds(login_frame_w * 2, login_frame_h * 3, login_frame_w * 2, login_frame_h);
        con.add(user_pwd);
        JLabel server_ip_tag = new JLabel("服务器ip");
        server_ip_tag.setBounds(login_frame_w, login_frame_h * 5, login_frame_w, login_frame_h);
        con.add(server_ip_tag);
        JTextField server_ip = new JTextField("127.0.0.1");
        server_ip.setBounds(login_frame_w, login_frame_h * 6, login_frame_w, login_frame_h);
        con.add(server_ip);
        JLabel server_port_tag = new JLabel("端口");
        server_port_tag.setBounds(login_frame_w * 3, login_frame_h * 5, login_frame_w, login_frame_h);
        con.add(server_port_tag);
        JTextField server_port = new JTextField("59001");
        server_port.setBounds(login_frame_w * 3, login_frame_h * 6, login_frame_w, login_frame_h);
        con.add(server_port);
        JButton login_button = new JButton("注册/登录");
        login_button.setBounds(login_frame_w, login_frame_h * 8, login_frame_w * 3, login_frame_h);
        login_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                name = user_name.getText();
                ip = server_ip.getText();
                port = server_port.getText();
                
                login_frame.setVisible(false);
            }
        });
        con.add(login_button);
        login_frame.setVisible(true);
    }
}
