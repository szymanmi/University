import iterator.Maker;
import strategy.Context;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class App {

	private App() {
		Random rand = new Random();

		int[][] array = new int[10][20];
		List<int[]> list = new ArrayList<>();
		for(int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++)
				array[i][j] = rand.nextInt(50) + 1;
			list.add(array[i]);
		}

		Maker maker = new Maker(list);

		Context context = new Context();
		List<int[]> list2 =	context.getSorted(maker.getIterator());

		for(int i = 0; i < 10; i++) {
			for (int j = 0; j < 20; j++) {
				System.out.print(list2.get(i)[j] + " ");
			}
			System.out.println();
		}
	}

	public static void main(String[] args) {
		App a = new App();
	}
}
