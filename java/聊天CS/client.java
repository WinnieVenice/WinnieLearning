import java.awt.Container;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Queue;
import java.util.*;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.event.MouseInputAdapter;


import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class client {
    static Socket soc;
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
    static volatile Deque<String> get_msg_queue = new LinkedList<String>();
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
        login_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                name = user_name.getText();
                if (name == null || name.equals("")) {
                    JOptionPane.showMessageDialog(login_frame, "用户名为空", "error", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                pwd = user_pwd.getText();
                if (pwd == null || pwd.equals("")) {
                    JOptionPane.showMessageDialog(login_frame, "用户名为空", "error", JOptionPane.ERROR_MESSAGE);
                    return;
                }
                ip = server_ip.getText();
                port = Integer.parseInt(server_port.getText());
                try {
                    if (link_server() == true) {
                        chat_frame = new ArrayList<JFrame>();
                        new Thread(new send_msg()).start();
                        new Thread(new get_msg()).start();
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
            soc = new Socket(ip, port);
            System.out.println(soc.getClass());
            in = new Scanner(soc.getInputStream());
            out = new PrintWriter(soc.getOutputStream(), true);
            if (REQUEST_check_user() == false) {
                JOptionPane.showMessageDialog(user_frame, "登陆失败", "error", JOptionPane.ERROR_MESSAGE);
                return false;
            }
            
            return true;
        } catch (Exception ex) {
            ex.printStackTrace();
            return false;   
        }
        //return true;
    }
    private static JFrame create_new_chat_frame(String frame_name) {
        JFrame cur_frame = new JFrame(frame_name);
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
                send_msg_queue.offer(line);
                System.out.println("q:" + send_msg_queue.peek());
            }
        });
        con.add(send_button);
        cur_frame.setVisible(true);
        return cur_frame;
    }
    private static boolean find(Vector<String> s, String v) {
        for (int i = 0; i < s.size(); i++) {
            if (s.get(i).equals(v)) return true;
        }
        return false;
    }
    private static void user_dialog() throws Exception {
        File f_friend = new File(".//" + name + "_friend.txt");
        BufferedReader bfr1 = new BufferedReader(new InputStreamReader(new FileInputStream(f_friend), "utf-8"));
        File f_group = new File(".//" + name + "_group.txt");
        BufferedReader bfr2 = new BufferedReader(new InputStreamReader(new FileInputStream(f_group), "utf-8"));
        Vector<String> friendlist = new Vector<String>();
        Vector<String> grouplist = new Vector<String>();
        if (!f_friend.exists()) {
            f_friend.createNewFile();
        }
        for (String rd = bfr1.readLine(); rd != null; rd = bfr1.readLine()) {
            System.out.println("当前好友: " + rd);
            friendlist.add(rd);
        }
        if (!f_group.exists()) { 
            f_group.createNewFile();
        }
        for (String rd = bfr2.readLine(); rd != null; rd = bfr2.readLine()) {
            System.out.println("当前群: " + rd);
            grouplist.add(rd);
        }
        user_frame = new JFrame("用户: " + name);
        user_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        user_frame.addWindowListener(new WindowListener() {
            public void windowDeactivated(WindowEvent e) {}
            public void windowActivated(WindowEvent e) {}
            public void windowDeiconified(WindowEvent e) {}
            public void windowIconified(WindowEvent e) {}
            public void windowClosed(WindowEvent e) {}
            public void windowOpened(WindowEvent e) {}
            public void windowClosing(WindowEvent e) {
                try {
                    bfr1.close();
                    bfr2.close();
                    BufferedWriter bfw1 = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(f_friend), "utf-8"));
                    BufferedWriter bfw2 = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(f_group), "utf-8"));
                    for (int i = 0; i < friendlist.size(); i++) {
                        bfw1.write(friendlist.get(i));
                        bfw1.newLine();
                    }
                    bfw1.close();
                    for (int i = 0; i < grouplist.size(); i++) {
                        bfw2.write(grouplist.get(i));
                        bfw2.newLine();
                    }
                    bfw2.close();
                } catch(Exception ex) {
                    ex.printStackTrace();
                } 
            }
        });
        user_frame.setSize(300, 600);
        int user_frame_w = user_frame.getWidth() / 8, user_frame_h = user_frame.getHeight() / 6;
        user_frame.setResizable(false);
        user_frame.setLocationRelativeTo(null);
        user_frame.setLayout(null);
        Container con = user_frame.getContentPane();
        JList<String> list = new JList<String>();
        MouseListener mouselistener = new MouseInputAdapter() {
            public void mouseClicked(MouseEvent e) {
                String frame_name = list.getSelectedValue();
                if (frame_name == null || frame_name.equals("")) return;
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
        JLabel add_name_text = new JLabel("所添加好友/群名:");
        add_name_text.setBounds(0, 0, user_frame_w * 3, user_frame_h);
        con.add(add_name_text);
        JTextArea add_name = new JTextArea();
        add_name.setBounds(user_frame_w * 3, 0, user_frame_w * 5, user_frame_h);
        con.add(add_name);
        JButton add_friend = new JButton("加好友");
        add_friend.setBounds(0, user_frame_h, user_frame_w * 2, user_frame_h);
        add_friend.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String s = add_name.getText();
                if (s == null || s.equals("")) {
                    JOptionPane.showMessageDialog(user_frame, "输入为空", "error", JOptionPane.ERROR_MESSAGE);
                } else if (find(friendlist, s)) {
                    JOptionPane.showMessageDialog(user_frame, "已添加过该好友", "提示", JOptionPane.ERROR_MESSAGE);    
                } else {
                    friendlist.add(s);
                    list.setListData(friendlist);
                }
            }
        });
        con.add(add_friend);
        JButton add_group = new JButton("加群");
        add_group.setBounds(user_frame_w * 2, user_frame_h, user_frame_w * 2, user_frame_h);
        add_group.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String s = add_name.getText();
                if (s == null || s.equals("")) {
                    JOptionPane.showMessageDialog(user_frame, "输入为空", "error", JOptionPane.ERROR_MESSAGE);
                } else if (find(grouplist, s)) {
                    JOptionPane.showMessageDialog(user_frame, "已添加过该群", "提示", JOptionPane.ERROR_MESSAGE);    
                } else {
                    grouplist.add(s);
                    list.setListData(grouplist);
                }
            }
        });
        con.add(add_group);
        JButton friend_button = new JButton("好友");
        friend_button.setBounds(user_frame_w * 4, user_frame_h, user_frame_w * 2, user_frame_h);
        friend_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                list.setListData(friendlist);
            }
        });
        con.add(friend_button);
        JButton group_button = new JButton("群");
        group_button.setBounds(user_frame_w * 6, user_frame_h, user_frame_w * 2, user_frame_h);
        group_button.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                list.setListData(grouplist);
            }
        });
        con.add(group_button);
        JScrollPane scroll = new JScrollPane(list);
        scroll.setBounds(0, user_frame_h * 2, user_frame_w * 8 - 15, user_frame_h * 5);
        con.add(scroll);
        user_frame.setVisible(true);
    }
    private static boolean REQUEST_check_user() throws IOException {
        try {
            out.println("CHECKUSER " + name + " " + pwd);
            System.out.println("发送登录请求");
            while (true) {
                String line = in.nextLine();
                if (line.startsWith("RETCHECKUSER")) {
                    System.out.println(line);
                    if (line.substring(13).equals("TRUE")) {
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
        //return true;
    }
    private class send_msg implements Runnable {
        public send_msg() {}
        public void run() {
            while (true) {
                while (send_msg_queue.isEmpty() == false) {
                    String line = send_msg_queue.peek(); send_msg_queue.poll();
                    System.out.println("有新的信息发送: " + line);
                    out.println(line);
                }
            }
        }
    }
    private class get_msg implements Runnable {
        public get_msg() {}
        public void run() {
            while (true) {
                if (!in.hasNext()) continue;
                String line = in.nextLine();
                if (line != null) {
                    System.out.println("有新的信息收到: " + line);
                    get_msg_queue.offer(line);
                }
            }
        }
    }
}