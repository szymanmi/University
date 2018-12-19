package strategy;

import iterator.Iterator;

import java.util.ArrayList;
import java.util.List;

public class Context {
	private Sort currentSort;


	public Context() {
		currentSort = new QuickSort();
	}


	public List<int[]> getSorted(Iterator iterator) {
		List<int[]> sortedList = new ArrayList<>();

		while (iterator.hasNext()) {
			sortedList.add((int[]) currentSort.sort(iterator.next()));
		}

		return sortedList;
	}
}
