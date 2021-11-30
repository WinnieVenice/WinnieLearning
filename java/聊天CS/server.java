import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
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
public class server {
    private static HashMap<String,String> users = new HashMap<String,String>();
    private static HashMap<String, PrintWriter> online_users = new HashMap<String, PrintWriter>();
    private static File userdata = new File(".//userdata.txt");
    private static BufferedReader bfr;
    private static BufferedWriter bfw;
    public static void main(String[] args) throws Exception {
        try {
            bfr = new BufferedReader(new InputStreamReader(new FileInputStream(userdata), "utf-8"));           
            JFrame server_frame = new JFrame("服务端");
            server_frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            server_frame.setSize(400, 300);
            server_frame.setResizable(false);
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
                        bfr.close();
                        bfw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(userdata), "utf-8"));
                        for (String x : users.keySet()) {
                            bfw.write(x + " " + users.get(x));
                            bfw.newLine();
                        }
                        bfw.close();
                    } catch(Exception ex) {
                        ex.printStackTrace();
                    } 
                }
            });
            for (String rd = bfr.readLine(); rd != null; rd = bfr.readLine()) {
                System.out.println("当前数据信息: " + rd);
                if (rd.split(" ").length > 1) {
                    users.put(rd.split(" ")[0], rd.split(" ")[1]);
                }
            }
            for (String x: users.keySet()) {
                System.out.println(x + " " + users.get(x));
            }
            System.out.println("读取用户信息成功");
            System.out.println("The chat server is running...");
            boolean flag = true;
            ExecutorService pool = Executors.newFixedThreadPool(500);
            try (ServerSocket listener = new ServerSocket(59001)) {
                while (flag) {
                    pool.execute(new Handler(listener.accept()));
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        } finally {
            bfr.close();
            bfw = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(userdata), "utf-8"));
            for (String x : users.keySet()) {
                bfw.write(x + " " + users.get(x));
                bfw.newLine();
            }
            bfw.close();
        }
    }
    private static class Handler implements Runnable {
        private String name;
        private String pwd;
        private Socket socket;
        private Scanner in;
        private PrintWriter out;
        public Handler(Socket socket) {
            System.out.println("线程建立成功");
            this.socket = socket;
        }
        public void run() {
            try {
                in = new Scanner(socket.getInputStream());
                out = new PrintWriter(socket.getOutputStream(), true);
                System.out.println("有新的用户进入");
                boolean flag = true;
                while (true) {
                    String line = in.nextLine();
                    System.out.println("当前消息: " + line);
                    if (line.startsWith("CHECKUSER")) {
                        System.out.println("收到用户登录申请");
                        line = line.substring(10);
                        name = line.split(" ")[0];
                        pwd = line.split(" ")[1];
                        System.out.println("当前用户: " + name + " " + pwd);
                        synchronized (users) {
                            if (line.length() == 0) {
                                out.println("RETCHECKUSER FALSE");
                                flag = false;
                            } if (online_users.get(name) == null) {
                                out.println("RETCHECKUSER FALSE");
                                flag = false;
                            } else if (users.get(name) == null) {
                                System.out.println("创建新用户: " + name + " " + pwd);
                                users.put(name, pwd);
                                online_users.put(name, out);
                                out.println("RETCHECKUSER TRUE");
                            } else if (users.get(name).equals(pwd)) {
                                online_users.put(name, out);
                                out.println("RETCHECKUSER TRUE");
                            } else {
                                out.println("RETCHECKUSER FALSE");
                                flag = false;
                            }
                            break;
                        }
                    }
                }
                if (flag) System.out.println("用户: " + name + ",连接服务器成功");
                else {
                    System.out.println("用户: " + name + ",连接服务器失败");
                    return;
                }
                while (true) {
                    if (!in.hasNext()) continue;
                    String line = in.nextLine();
                    if (line != null) {
                        System.out.println(line);
                        if (line.startsWith("SENDMSG")) {
                            String s = line.substring(8);
                            String[] ss = s.split(" ");
                            if (online_users.get(ss[1]) == null) {
                                System.out.println("用户: " + ss[1] + "不在线");
                                out.println("RETSENDMSG ERROR");
                                continue;
                            }
                            
                        }
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
            } finally {
                try {
                    socket.close();
                }catch(Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }
}