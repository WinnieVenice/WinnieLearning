import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.awt.event.*;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
public class server {
    private static class pair{
               
    }
    private static HashMap<String, String> users = new HashMap<String,String>();
    private static HashMap<String, HashSet<String>> groups = new HashMap<String,HashSet<String>>();
    private static HashMap<String, String> online_users = new HashMap<String, String>();
    private static File userdata = new File(".//userdata.txt");
    private static File groupdata = new File(".//groupdata.txt");
    private static BufferedReader bfr1;
    private static BufferedWriter bfw1;
    private static BufferedReader bfr2;
    private static BufferedWriter bfw2;
    private static JTextArea show;
    volatile static DatagramSocket server;
    
    public final static int MAX_PACKET_SIZE = 65507;
    public final static int PORT = 59001;
    public static void print(String s, InetAddress ip, int port) throws Exception{
        byte[] buff = s.getBytes();
        DatagramPacket cur_packet = new DatagramPacket(buff, buff.length, ip, port);
        server.send(cur_packet);
    }
    public static void print(String s, String cur_people) throws Exception{
        byte[] buff = s.getBytes();
        System.out.println(InetAddress.getByName(cur_people.split("#")[0]));
        DatagramPacket cur_packet = new DatagramPacket(buff, buff.length, InetAddress.getByName(cur_people.split("#")[0]), Integer.parseInt(cur_people.split("#")[1]));
        server.send(cur_packet);
    }
    public static void main(String[] args) throws Exception {
        try {
            if (!userdata.exists()) {
                userdata.createNewFile();
            }
            if (!groupdata.exists()) {
                groupdata.createNewFile();
            }
            bfr1 = new BufferedReader(new InputStreamReader(new FileInputStream(userdata), "utf-8"));  
            bfr2 = new BufferedReader(new InputStreamReader(new FileInputStream(groupdata), "utf-8"));         
            JFrame server_frame = new JFrame("服务端");
            server_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            server_frame.setSize(400, 300);
            server_frame.setResizable(false);
            show = new JTextArea();
            server_frame.add(new JScrollPane(show));
            server_frame.setVisible(true);
            server_frame.addWindowListener(new WindowListener() {
                public void windowDeactivated(WindowEvent e) {}
                public void windowActivated(WindowEvent e) {}
                public void windowDeiconified(WindowEvent e) {}
                public void windowIconified(WindowEvent e) {}
                public void windowClosed(WindowEvent e) {}
                public void windowOpened(WindowEvent e) {}
                public void windowClosing(WindowEvent e) {
                    try {
                        bfr1.close();
                        bfw1 = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(userdata), "utf-8"));
                        for (String x : users.keySet()) {
                            bfw1.write(x + " " + users.get(x)); bfw1.newLine();
                        }
                        bfw1.close();
                        bfr2.close();
                        bfw2 = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(groupdata), "utf-8"));
                        for (String x : groups.keySet()) {
                            bfw2.write(x); bfw2.newLine();
                            String s = "";
                            for (String y : groups.get(x)) {
                                s += y + " ";
                            }
                            bfw2.write(s); bfw2.newLine();
                        }
                        bfw2.close();
                    } catch(Exception ex) {
                        ex.printStackTrace();
                    } 
                }
            });
            //System.out.println("用户数据");
            show.append("用户数据\n");
            for (String rd = bfr1.readLine(); rd != null; rd = bfr1.readLine()) {
                //System.out.println("当前数据信息: " + rd);
                show.append("当前数据信息: " + rd + "\n");
                if (rd.split(" ").length > 1) {
                    users.put(rd.split(" ")[0], rd.split(" ")[1]);
                }
            }
            //System.out.println("读取用户信息成功");
            show.append("读取用户信息成功\n");
            //System.out.println("群组数据");
            show.append("群组数据\n");
            for (String rd = bfr2.readLine(); rd != null; rd = bfr2.readLine()) {
                if (rd == null || rd.equals("")) continue;
                String cur_group = rd;
                //System.out.println("当前群组名称: " + cur_group);
                show.append("当前群组名称: " + cur_group + "\n");
                groups.put(cur_group, new HashSet<String>());
                rd = bfr2.readLine();
                //System.out.println("当前群用户:" + rd);
                show.append("当前群用户:" + rd + "\n");
                String[] cur_users = rd.split(" ");
                for (int i = 0; i < cur_users.length; i++) {
                    if (cur_users[i] == null || cur_users[i].equals("")) continue;
                    groups.get(cur_group).add(cur_users[i]);
                }
            }
            //System.out.println("读取群组信息成功");
            show.append("读取群组信息成功\n");
            //System.out.println("The chat server is running...");
            show.append("聊天服务器正在运行...\n");
            boolean flag = true;
            server = new DatagramSocket(59001);
            byte[] buff = new byte[MAX_PACKET_SIZE];
            DatagramPacket packet = new DatagramPacket(buff, buff.length);
            try {
                while (flag) {
                    server.receive(packet);
                    int cur_port = packet.getPort();
                    InetAddress cur_ip = packet.getAddress();
                    String cur_ip_string = cur_ip.toString();
                    cur_ip_string = cur_ip_string.substring(cur_ip_string.lastIndexOf("/") + 1);
                    String line = new String(packet.getData(), 0, packet.getLength(), "UTF-8");
                    String name = "", pwd = "";
                    if (line.startsWith("CHECKUSER")) {
                        show.append("收到用户登录申请\n");
                        line = line.substring(10);
                        name = line.split(" ")[0];
                        pwd = line.split(" ")[1];
                        show.append("当前用户: " + name + " " + pwd + "\n");
                        boolean sign = true;
                        synchronized (users) {
                            if (line.length() == 0) {
                                print("RETCHECKUSER FALSE", cur_ip, cur_port);
                                //out.println("RETCHECKUSER FALSE");
                                sign = false;
                            } if (online_users.get(name) != null) {
                                show.append("用户: " + name + "已在线\n");
                                print("RETCHECKUSER FALSE", cur_ip, cur_port);
                                //out.println("RETCHECKUSER FALSE");
                                sign = false;
                            } else if (users.get(name) == null) {
                                show.append("创建新用户: " + name + " " + pwd + "\n");
                                users.put(name, pwd);
                                online_users.put(name, cur_ip_string + "#" + Integer.toString(cur_port));
                                print("RETCHECKUSER TRUE", cur_ip, cur_port);
                                //out.println("RETCHECKUSER TRUE");
                            } else if (users.get(name).equals(pwd)) {
                                show.append("用户: " + name + " 密码正确\n");
                                System.out.println(cur_ip.toString());
                                online_users.put(name, cur_ip_string + "#" + Integer.toString(cur_port));
                                print("RETCHECKUSER TRUE", cur_ip, cur_port);
                                //out.println("RETCHECKUSER TRUE");
                            } else {
                                show.append("用户: " + name + "密码错误\n");
                                print("RETCHECKUSER FALSE", cur_ip, cur_port);
                                //out.println("RETCHECKUSER FALSE");
                                sign = false;
                            }
                        }
                        if (sign) {
                            show.append("用户: " + name + ",连接服务器成功\n");
                        } else {
                            show.append("用户: " + name + ",连接服务器失败\n");
                        }
                    } else if (line.startsWith("SENDMSG")) {
                        if (line.substring(8).startsWith("FRIEND")) {
                            String s = line.substring(15);
                            String[] ss = s.split(" ", 3);
                            if (online_users.get(ss[1]) == null) {
                                show.append("用户: " + ss[1] + "不在线\n");
                                print("RETMSG ERROR", cur_ip, cur_port);
                                //out.println("RETMSG ERROR");
                                continue; 
                            }
                            String msg = "RETMSG FRIEND " + ss[0] + " " + ss[2];
                            print(msg, online_users.get(ss[1]));
                            //online_users.get(ss[1]).println(msg);
                        } else {    
                            String s = line.substring(14);
                            String[] ss = s.split(" ", 3);
                            if (groups.get(ss[1]) == null) {
                                show.append("群组: " + ss[1] + "不存在\n");
                                print("RETMSG ERROR", cur_ip, cur_port);
                                //out.println("RETMSG ERROR");
                                continue;
                            }
                            String msg = "RETMSG GROUP " + ss[1] + " " + ss[0] + " " + ss[2];
                            for (String x : groups.get(ss[1])) {
                                if (online_users.get(x) == null || x.equals(ss[0])) continue;
                                show.append("转发群消息给: " + x + ",内容: " + msg + "\n");
                                print(msg, online_users.get(x));
                                //online_users.get(x).println(msg);
                            }
                        }
                    } else if (line.equals("QUIT")) {
                        show.append(name + "下线了\n");
                        if (online_users.get(name) != null && flag) {
                            online_users.remove(name);
                        }
                        for (String x : online_users.keySet()) {
                            //System.out.println("当前在线用户: " + x);
                            show.append("当前剩余在线用户: " + x + "\n");
                        }
                        //return;
                    } else if (line.startsWith("ADDGROUP")) {
                        String s = line.substring(9);
                        String groupname = s.split(" ", 2)[0], username = s.split(" ", 2)[1];
                        if (groups.get(groupname) == null) {
                            groups.put(groupname, new HashSet<String>());
                        }
                        groups.get(groupname).add(username);
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        } catch(Exception e) {
            e.printStackTrace();
        } finally {
            bfr1.close();
            bfw1 = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(userdata), "utf-8"));
            for (String x : users.keySet()) {
                bfw1.write(x + " " + users.get(x));
                bfw1.newLine();
            }
            bfw1.close();
        }
    }
}