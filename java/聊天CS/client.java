import java.awt.Container;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Queue;
import java.util.Scanner;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;


public class client {
    static String ip;
    static int port;
    static JFrame user_frame;
    static JFrame login_frame;
    static String name;
    static String pwd;
    static client _client;
    static Scanner in;
    static PrintWriter out;
    static Queue<String> msg_queue;
    public static void main(String[] args) throws Exception {
        login_dialog();
    }
    private static void login_dialog() throws Exception{
        login_frame = new JFrame("user login");
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
                pwd = user_pwd.getText();
                ip = server_ip.getText();
                port = Integer.parseInt(server_port.getText());
                try {
                    if (link_server() == true) {
                        user_dialog();
                        login_frame.setVisible(false);
                    } else {
                        JOptionPane.showMessageDialog(login_frame, "连接服务器失败", "error", JOptionPane.ERROR_MESSAGE);
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });
        con.add(login_button);
        login_frame.setVisible(true);
    }
    private static boolean link_server() throws IOException {
        try {
            Socket soc = new Socket(ip, port);
            in = new Scanner(soc.getInputStream());
            out = new PrintWriter(soc.getOutputStream());
            if (check_user() == false) {
                JOptionPane.showMessageDialog(user_frame, "密码错误", "error", JOptionPane.ERROR_MESSAGE);
                return false;
            }
            return true;
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;   
        }
    }
    private static boolean check_user() throws IOException {
        try {
            out.println("CHECKUSER " + name + " " + pwd);
            while (in.hasNextLine()) {
                String line = in.nextLine();
                if (line.startsWith("RETCHECKUSER")) {
                    if (line.substring(13) == "TRUE") {
                        return true;
                    } else {
                        return false;
                    }
                }
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;
        }
    }
    private static void user_dialog() {
        user_frame = new JFrame("用户: " + name);
        user_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        user_frame.setSize(300, 600);
        int user_frame_w = user_frame.getWidth() / 6, user_frame_h = user_frame.getHeight() / 6;
        user_frame.setResizable(false);
        user_frame.setLocationRelativeTo(null);
        user_frame.setLayout(null);
        Container con = user_frame.getContentPane();
        JButton chat_list = new JButton("聊天");
        chat_list.setBounds(0, 0, user_frame_w * 2, user_frame_h);
        con.add(chat_list);
        JButton friend_list = new JButton("好友");
        friend_list.setBounds(user_frame_w * 2, 0, user_frame_w * 2, user_frame_h);
        con.add(friend_list);
        JButton group_list = new JButton("群");
        group_list.setBounds(user_frame_w * 4, 0, user_frame_w * 2, user_frame_h);
        con.add(group_list);
        JList list = new JList<String>();
        //list.setBounds(0, user_frame_h, user_frame_w * 5, user_frame_h * 5);
        //list.setListData(new String[]{"xxc1(ai)", "雪梨", "苹果", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨"});
        JScrollPane scroll = new JScrollPane(list);
        scroll.setBounds(0, user_frame_h, user_frame_w * 6 - 15, user_frame_h * 5);
        con.add(scroll);
        user_frame.setVisible(true);
    }
    private static void deal_msg() {
        
    }
}