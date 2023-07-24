import java.io.*;
import java.math.*;
import java.util.*;

public class Main {
	InputReader in;
	PrintWriter out;

	public void solve() throws IOException {
		// Code here...
	}

	public void run() {
		try {
			in = new InputReader(System.in);
			out = new PrintWriter(System.out);
			solve();
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	class InputReader {
		BufferedReader br;
		StringTokenizer st;

		InputReader(File f) {
			try {
				br = new BufferedReader(new FileReader(f));
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			}
		}

		public InputReader(InputStream f) {
			br = new BufferedReader(new InputStreamReader(f));
		}

		String next() {
			while (st == null || !st.hasMoreTokens()) {
				try {
					st = new StringTokenizer(br.readLine());
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
			return st.nextToken();
		}

		int nextInt() {
			return Integer.parseInt(next());
		}
	}

	public static void main(String[] arg) {
		new Main().run();
	}
}
