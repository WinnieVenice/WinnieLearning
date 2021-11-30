import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
public class server {
    private static HashMap<String,String> users = new HashMap<String,String>();
    private static Set<String> online_users = new HashSet<String>();
    private static Set<PrintWriter> writers = new HashSet<>();
    private static File userdata = new File(".//userdata.txt");
    private static FileReader fr;
    private static BufferedReader bfr;
    private static FileWriter fw;
    private static BufferedWriter bfw;
    public static void main(String[] args) throws Exception {
        try {
            fr = new FileReader(userdata);
            bfr = new BufferedReader(fr);
            fw = new FileWriter(userdata, true);
            bfw = new BufferedWriter(fw);
            for (String rd = bfr.readLine(); rd != null; rd = bfr.readLine()) {
                System.out.println("当前数据信息: " + rd);
                if (rd.split(" ").length > 1) {
                    users.put(rd.split(" ")[0], rd.split(" ")[1]);
                }
            }
            for (String x: users.keySet()) {
                System.out.println(x + " " + users.get(x));
            }
            bfw.newLine();
            System.out.println("读取用户信息成功");
            System.out.println("The chat server is running...");
            Scanner cin = new Scanner(System.in);
            ExecutorService pool = Executors.newFixedThreadPool(500);
            try (ServerSocket listener = new ServerSocket(59001)) {
                while (!cin.hasNextLine()) {
                    pool.execute(new Handler(listener.accept()));
                }
            }
        } catch(Exception e) {
            e.printStackTrace();
        } finally {
            bfr.close();
            fr.close();
            bfw.close();
            fw.close();
        }
    }
    private static class Handler implements Runnable {
        private String name;
        private String pwd;
        private Socket socket;
        private Scanner in;
        private PrintWriter out;  
        private File f; 
        private FileReader fr;
        private BufferedReader bfr;
        private FileWriter fw;
        private BufferedWriter bfw;
        public Handler(Socket socket) {
            this.socket = socket;
        }
        public void run() {
            try {
                in = new Scanner(socket.getInputStream());
                out = new PrintWriter(socket.getOutputStream(), true);
                // Keep requesting a name until we get a unique one.
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
                            } if (online_users.contains(name)) {
                                out.println("RETCHECKUSER FALSE");
                                flag = false;
                            } else if (users.get(name) == null) {
                                System.out.println("创建新用户: " + name + " " + pwd);
                                users.put(name, pwd);
                                online_users.add(name);
                                out.println("RETCHECKUSER TRUE");
                                bfw.write(name + " " + pwd);
                                bfw.newLine();
                            } else if (users.get(name).equals(pwd)) {
                                online_users.add(name);
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
                writers.add(out);
                while (true) {
                    String line = in.nextLine();
                    if (line != null) {
                        System.out.println(line);
                        if (line.startsWith("FRIENDLIST")) {
                            String s = "RETFRIENDLIST";
                            
                            out.println(s);
                        } else if (line.startsWith("GROUPLIST")) {

                        } else if (line.startsWith("SENDMSG")) {

                        } else if (line.startsWith("QUIT")) {

                        }
                    }
                }
                /*
                for (PrintWriter writer : writers) {
                    writer.println("MESSAGE " + name + " has joined");
                    System.out.println("MESSAGE " + name + " has joined");
                }
                writers.add(out);
                while (true) {
                    String input = in.nextLine();
                    if (input.toLowerCase().startsWith("/quit")) {
                        return;
                    }
                    for (PrintWriter writer : writers) {
                        writer.println("MESSAGE " + name + ": " + input);
                    }
                }
                */
            } catch (Exception e) {
                System.out.println(e);
            } finally {
                try {
                    bfr.close();
                    fr.close();
                    bfw.close();
                    fw.close();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
                /*
                if (out != null) {
                    writers.remove(out);
                }
                if (name != null) {
                    System.out.println(name + " is leaving");
                    for (PrintWriter writer : writers) {
                        writer.println("MESSAGE " + name + " has left");
                    }
                }   
                try {
                    socket.close();
                } catch (IOException e) {
                }
                */
            }
        }
    }
}