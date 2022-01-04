import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;

public class crawler {
	
	//定义路径
	static String baseurl = "http://www.netbian.com/";
	static String geturl = "http://www.netbian.com/desk/24165.htm";
	static String filepath = "C:\\Users\\WinnieVenice\\Desktop\\test\\";
	public static void main(String[] args) throws IOException{
		System.out.println("初始下载页面："+geturl);
		String html = Jsoup.connect(geturl).execute().body(); 
		List<String> srclists = getHtml(html); 
		getImg(srclists, filepath);
		List<String> list = getNext(html); 
		for (int i = 0; i < list.size(); i++) {
			String url = list.get(i);
			System.out.println("下一个下载页面："+url);
			try {
				html = Jsoup.connect(url).execute().body();
				List<String> srclists2 = getHtml(html); 
				getImg(srclists2, filepath);
			} catch (Exception e) {
				System.out.println("url错误，跳过该url");
			}
		}
		System.out.println("下载完毕");
	}
	public static List<String> getHtml(String html){
		List<String> list = new ArrayList<>();
		Document document = Jsoup.parse(html);
		Elements elements = document.select("div [class=pic]").select("img");
		int len = elements.size();
		for (int i = 0; i < len; i++) {
			list.add(elements.get(i).attr("src"));
		}
		return list;
	}
	public static List<String> getNext(String html){
		List<String> list = new ArrayList<>();
		Document document = Jsoup.parse(html);
		Elements elements = document.select("div [class=list]").select("a");
		for (int i = 0;i<elements.size();i++) {
			String url = baseurl + elements.get(i).attr("href");
			list.add(url);
		}
		return list;
	}
	public static void getImg(List<String> list, String filepath){
		URL newUrl = null;
		HttpURLConnection hconnection = null;
		InputStream inputStream = null;
		FileOutputStream fileOutputStream = null;
		byte[] bs = null;
		try {
			int len = list.size();
			for (int i = 0; i < len; i++) {
				newUrl = new URL(list.get(i));
				hconnection = (HttpURLConnection) newUrl.openConnection(); 
				inputStream = hconnection.getInputStream();  
				bs = null;
				byte[] buff = new byte[1024];
				ByteArrayOutputStream arrayOutputStream = new ByteArrayOutputStream(); //
				for (int j = inputStream.read(buff); j != -1; j = inputStream.read(buff)) {
					arrayOutputStream.write(buff, 0, j);
				}
				bs = arrayOutputStream.toByteArray();
				filepath = filepath + list.get(i).substring(list.get(i).lastIndexOf("/")+1); //获取图片名称
				System.out.println("生成图片路径:"+filepath);
				fileOutputStream = new FileOutputStream(new File(filepath));
				fileOutputStream.write(bs); 
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				inputStream.close();
				fileOutputStream.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
}