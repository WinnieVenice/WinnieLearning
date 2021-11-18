
import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import java.io.OutputStream;
import java.util.zip.ZipEntry;

import java.util.zip.ZipOutputStream;
public class 加密压缩文件{
    public static void main (String[] args) throws Exception{
        show_dialog();
    }
    private static JFileChooser fc = null;
    private static File f = null;
    private static void show_dialog() throws Exception{
        JFrame _main = new JFrame("加密文件");
        _main.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        _main.setSize(1200, 600);
        int w = _main.getWidth() / 7, h = _main.getHeight() / 8;
        Container con = _main.getContentPane();
        con.setLayout(null);
        JLabel jl1 = new JLabel("加密算法:");
        jl1.setBounds(w, 3 * h, w, h);
        con.add(jl1);
        JComboBox<String> jcb = new JComboBox<String>();
        jcb.setBounds(2 * w, 3 * h, w, h);
        con.add(jcb);
        jcb.addItem("算法1");
        JLabel jl2 = new JLabel("密钥:");
        jl2.setBounds(4 * w, 3 * h, w, h);
        con.add(jl2);
        JTextField jtf = new JTextField();
        jtf.setBounds(5 * w, 3 * h, w, h);
        con.add(jtf);
        JButton jb0 = new JButton("选择文件或文件夹");
        jb0.setBounds(w, h, 5 * w, h);
        con.add(jb0);
        JButton jb1 = new JButton("线程和线程池加密");
        jb1.setBounds(w, 5 * h,  w, h);
        con.add(jb1);
        JButton jb2 = new JButton("线程和线程池解密");
        jb2.setBounds(3 * w, 5 * h, w, h);
        con.add(jb2);
        JButton jb3 = new JButton("压缩");
        jb3.setBounds(5 * w, 5 * h, w, h);
        con.add(jb3);
        key = 0;
        jb0.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                fc = new JFileChooser();
                fc.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
                fc.showOpenDialog(null);
                f = fc.getSelectedFile();
            }
        });
        jb1.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                key = Integer.parseInt(jtf.getText());
                if (f != null || key == 0) {
                    _init();
                    long st1 = 0, ed1 = 0, st2 = 0, ed2 = 0;
                    try {
                        st1 = System.currentTimeMillis();
                        dfs(f, true);
                        ed1 = System.currentTimeMillis();
                        st2 = System.currentTimeMillis();
                        thread_pool(true);
                        ed2 = System.currentTimeMillis();
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                    JOptionPane.showMessageDialog(null, "加密成功。线程加密耗时：" + String.valueOf(ed1 - st1) + "; 线程池加密耗时：" + String.valueOf(ed2 - st2));
                } else {
                    JOptionPane.showMessageDialog(null, "文件为空或密钥为0", null, JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        jb2.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                key = Integer.parseInt(jtf.getText());
                if (f != null || key == 0) {
                    _init();
                    long st1 = 0, ed1 = 0, st2 = 0, ed2 = 0;
                    try {
                        st1 = System.currentTimeMillis();
                        dfs(f, false);
                        ed1 = System.currentTimeMillis();
                        st2 = System.currentTimeMillis();
                        thread_pool(false);
                        ed2 = System.currentTimeMillis();
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                    JOptionPane.showMessageDialog(null, "解密成功。线程加密耗时：" + String.valueOf(ed1 - st1) + "; 线程池加密耗时：" + String.valueOf(ed2 - st2));
                } else {
                    JOptionPane.showMessageDialog(null, "文件为空或密钥为0", null, JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        jb3.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e) {
                if (f != null) {
                    try {
                        System.out.println(f.getParentFile().getAbsolutePath().toString());
                        toZip(f.getAbsolutePath(), new FileOutputStream(new File(f.getParentFile().getAbsolutePath() + "\\" + f.getName().split("\\.")[0] + ".zip")));
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                    JOptionPane.showMessageDialog(null, "压缩成功");
                } else {
                    JOptionPane.showMessageDialog(null, "文件为空", null, JOptionPane.ERROR_MESSAGE);
                }
            }
        });
        _main.setResizable(false);
        _main.setVisible(true);
    }
    private static int key;
    private static Map<Character,Character> hsh;
    private static void _init() {
        hsh = new HashMap<Character, Character> ();
        for (int i = 0; i < 128; i++) {
            hsh.put((char)i, (char)(i + key));
        }
    }
    private static void thread_pool(boolean T) throws Exception{
        ExecutorService es = Executors.newFixedThreadPool(2);
        if (T == true) {
            dfs(f, true);
        } else {
            dfs(f, false);
        }
        es.shutdown();
    }
    private static void enc(File f) throws Exception{
        try {
            enc_thread t = new enc_thread(f, hsh);
            Thread T = new Thread(t);
            T.start();
        }catch (Exception ex) {
            ex.printStackTrace();
        }
    }
    private static void inv_enc(File f) throws Exception {
        
        try {
            inv_enc_thread t = new inv_enc_thread(f, hsh, key);
            Thread T = new Thread(t);
            T.start();
        }catch(Exception ex) {
            ex.printStackTrace();
        }
    }
    private static void dfs(File f, boolean T) throws Exception {
        if (f == null) return;
        if (f.isFile()){
            if (T) {
                enc(f);
            } else {
                inv_enc(f);
            }
        } else if (f.isDirectory()) {
            File[] _list = f.listFiles();
            for (File _f : _list) {
                dfs(_f, T);
            }
        }
    }
    private static final int BUFFER_SIZE = 2048;
    public static void toZip(String path_f, OutputStream out) throws Exception{
            System.out.println(path_f);
            ZipOutputStream zos = null ;
            try {
                zos = new ZipOutputStream(out);
                File sourceFile = new File(path_f);
                compress(sourceFile,zos,sourceFile.getName());
            } catch (Exception ex) {
                ex.printStackTrace();
            }finally{
                if(zos != null){
                    try {
                        zos.close();
                    } catch (Exception ex) {
                        ex.printStackTrace();
                    }
                }
        }
    }
    private static void compress(File sourceFile, ZipOutputStream zos, String name) throws Exception{
        byte[] buf = new byte[BUFFER_SIZE];
        if(sourceFile.isFile()){
            zos.putNextEntry(new ZipEntry(name));
            int len;
            FileInputStream in = new FileInputStream(sourceFile);
            while ((len = in.read(buf)) != -1){
                zos.write(buf, 0, len);
            }
            zos.closeEntry();
            in.close();
        } else {
            File[] listFiles = sourceFile.listFiles();
            if(listFiles == null || listFiles.length == 0){
                zos.putNextEntry(new ZipEntry(name + "/"));
                zos.closeEntry();
            }else {
                for (File file : listFiles) {
                    compress(file, zos, name + "/" + file.getName());
                }
            }
        }
    }
}
class enc_thread implements Runnable{
    File f;
    FileReader fr = null;
    BufferedReader bfr = null;
    FileWriter fw = null;
    BufferedWriter bfw = null;
    Map<Character,Character> hsh;
    public enc_thread(File f, Map<Character, Character> hsh){
        this.f = f;
        this.hsh = hsh;
    }
    public void run(){
        try {
            fr = new FileReader(f);
            bfr = new BufferedReader(fr);
            String[] name = f.getName().split("\\.");
            if (name[0].endsWith("_enc") == true) return;
            fw = new FileWriter(f.getParentFile().getAbsolutePath() + "/" + name[0] + "_enc." + name[1]);
            bfw = new BufferedWriter(fw);
            for (String rd = bfr.readLine(); rd != null; rd = bfr.readLine()) {
                for (int i = 0; i < rd.length(); i++) {
                    if (hsh.getOrDefault(rd.charAt(i), null) == null) continue;
                    bfw.write(hsh.get(rd.charAt(i)));
                }
                bfw.newLine();
            }
            bfr.close();
            bfw.close();
            fr.close();
            fw.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}
class inv_enc_thread implements Runnable{
    File f;
    FileReader fr = null;
    BufferedReader bfr = null;
    FileWriter fw = null;
    BufferedWriter bfw = null;
    Map<Character, Character> hsh;
    int key;
    public inv_enc_thread(File f, Map<Character, Character> hsh, int key) {
        this.f = f;
        this.hsh = hsh;
        this.key = key;
    }
    public void run() {
        try {
            fr = new FileReader(f);
            bfr = new BufferedReader(fr);
            String[] name = f.getName().split("\\.");
            if (name[0].endsWith("_enc") == false) return;
            name[0] = name[0].split("_enc")[0];
            fw = new FileWriter(f.getParentFile().getAbsolutePath() + "/" + name[0] + "." + name[1]);
            bfw = new BufferedWriter(fw);
            for (String rd = bfr.readLine(); rd != null; rd = bfr.readLine()) {
                for (int i = 0; i < rd.length(); i++) {
                    if (hsh.getOrDefault(rd.charAt(i), null) == null) continue;
                    bfw.write((char)(rd.charAt(i) - key));
                }
                bfw.newLine();
            }
            bfr.close();
            bfw.close();
            fr.close();
            fw.close();
        } catch (Exception ex) {
            ex.printStackTrace();
        }
    }
}