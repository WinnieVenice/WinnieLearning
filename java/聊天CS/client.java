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
import java.util.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.MouseInputAdapter;
import javax.swing.event.MouseInputListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

public class client {
    
    static String ip;
    static int port;
    static JFrame user_frame;
    static JFrame login_frame;
    static String name;
    static String pwd;
    static Scanner in;
    static PrintWriter out;
    static String[] friend_list;
    static String[] group_list;
    static String[] chat_list;
    static ArrayList<JFrame> chat_frame; 
    static volatile Deque<String> send_msg_queue = new LinkedList<String>();
    String chat_name;
    public static void main(String[] args) throws Exception {
        new client().login_dialog();
    }
    public client() {}
    public client(String chat_name) {
        
        this.chat_name = chat_name;
    }
    private void login_dialog() throws Exception{
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
        new Thread(new send_msg(ip, port)).start();
        login_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                name = user_name.getText();
                pwd = user_pwd.getText();
                ip = server_ip.getText();
                port = Integer.parseInt(server_port.getText());
                try {
                    if (link_server() == true) {
                        chat_frame = new ArrayList<JFrame>();
                        //new Thread(new client()).start();
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
            System.out.println("ip: " + ip + ", port: " + port);
            
            /*
            Socket soc = new Socket(ip, port);
            in = new Scanner(soc.getInputStream());
            out = new PrintWriter(soc.getOutputStream());
            if (REQUEST_check_user() == false) {
                JOptionPane.showMessageDialog(user_frame, "密码错误", "error", JOptionPane.ERROR_MESSAGE);
                return false;
            }
            */
            return true;
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;   
        }
        //return true;
    }
    private static JFrame create_new_chat_frame(String frame_name) {
        JFrame cur_frame = new JFrame(frame_name);
        cur_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        cur_frame.setSize(400, 300);
        cur_frame.setResizable(false);
        cur_frame.setLocationRelativeTo(null);
        cur_frame.setLayout(null);
        int w = cur_frame.getWidth() / 7, h = cur_frame.getHeight() / 11;
        Container con = cur_frame.getContentPane();
        JTextArea chating = new JTextArea();
        chating.setBounds(w, h, w * 5 , h * 4);
        con.add(chating);
        JTextArea sendmsg = new JTextArea();
        sendmsg.setBounds(w, h * 6, w * 5, h * 2);
        con.add(sendmsg);
        JButton send_button = new JButton("发送信息");
        send_button.setBounds(w * 4, h * 8, w * 2, h);
        send_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String line = "SENDMSG " + name + " " + cur_frame.getTitle() + " " + sendmsg.getText();
                //send_msg_queue.add(line);
                //send_msg_queue.offer(line);
                //System.out.println("q:" + send_msg_queue.peek());
                //new client().run();
                send_msg_queue.offer(line);
                System.out.println("q:" + send_msg_queue.peek());
            }
        });
        con.add(send_button);
        cur_frame.setVisible(true);
        return cur_frame;
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
        JList<String> list = new JList<String>();
        list.setListData(new String[]{"wwj", "xxc", "hzb", "zrf"});
        MouseListener mouselistener = new MouseInputAdapter() {
            public void mouseClicked(MouseEvent e) {
                String frame_name = list.getSelectedValue();
                boolean flag = false;
                for (int i = 0; i < chat_frame.size(); i++) {
                    if (frame_name == chat_frame.get(i).getTitle()) {
                        flag = true;
                        chat_frame.get(i).setVisible(true);
                        break;
                    }
                }
                if (flag == false) {
                    chat_frame.add(create_new_chat_frame(frame_name));
                }
            }   
        };
        list.addMouseListener(mouselistener);
        JButton chat_button = new JButton("聊天");
        chat_button.setBounds(0, 0, user_frame_w * 2, user_frame_h);
        chat_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                list.setListData(chat_list);
            }
        });
        con.add(chat_button);
        JButton friend_button = new JButton("好友");
        friend_button.setBounds(user_frame_w * 2, 0, user_frame_w * 2, user_frame_h);
        friend_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    if (REQUEST_friend_list() == true) {
                        list.setListData(friend_list);
                    } else {
                        JOptionPane.showMessageDialog(user_frame, "获取好友列表失败", "error", JOptionPane.ERROR_MESSAGE);
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog(user_frame, "获取好友列表失败", "error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        con.add(friend_button);
        JButton group_button = new JButton("群");
        group_button.setBounds(user_frame_w * 4, 0, user_frame_w * 2, user_frame_h);
        group_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                try {
                    if (REQUEST_group_list() == true) {
                        list.setListData(group_list);
                    } else {
                        JOptionPane.showMessageDialog(user_frame, "获取群列表失败", "error", JOptionPane.ERROR_MESSAGE);
                    }
                } catch (Exception ex) {
                    ex.printStackTrace();
                    JOptionPane.showMessageDialog(user_frame, "获取群列表失败", "error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        con.add(group_button);
        //list.setBounds(0, user_frame_h, user_frame_w * 5, user_frame_h * 5);
        //list.setListData(new String[]{"xxc1(ai)", "雪梨", "苹果", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "荔枝", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨", "雪梨"});
        JScrollPane scroll = new JScrollPane(list);
        scroll.setBounds(0, user_frame_h, user_frame_w * 6 - 15, user_frame_h * 5);
        con.add(scroll);
        user_frame.setVisible(true);
    }
    private static boolean REQUEST_check_user() throws IOException {
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

        return true;
    }
    private static boolean REQUEST_friend_list() throws IOException{
        try {
            out.println("FRIENDLIST " + name);
            while (in.hasNextLine()) {
                String line = in.nextLine();
                if (line.startsWith("RETFRIENDLIST")) {
                    friend_list = line.substring(14).split(" ");
                    return true;
                } else return false;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;
        }
        return false;
    }
    private static boolean REQUEST_group_list() throws IOException{
        try {
            out.println("GROUPLIST " + name);
            while (in.hasNextLine()) {
                String line = in.nextLine();
                if (line.startsWith("RETGROUPLIST")) {
                    group_list = line.substring(13).split(" ");
                    return true;
                } else return false;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;
        }
        return false;
    }
    private class send_msg implements Runnable{
        String ip;
        int port;
        public send_msg(String ip, int port) {
            this.ip = ip; this.port = port;
        }
        public void run() {
            while (true) {
                //System.out.println(send_msg_queue.size());
                while (send_msg_queue.isEmpty() == false) {
                    System.out.println("this");
                    String line = send_msg_queue.peek(); send_msg_queue.poll();
                    System.out.println(line);
                    //out.println(line);
                }
            }
        }
    }

}