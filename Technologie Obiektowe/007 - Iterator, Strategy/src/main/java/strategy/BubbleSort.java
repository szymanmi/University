package strategy;

public class BubbleSort implements Sort {
	@Override
	public Object sort(Object arr) {

		int arrr[] = (int[])arr;
		int n = arrr.length;
		for (int i = 0; i < n-1; i++)
			for (int j = 0; j < n-i-1; j++)
				if (arrr[j] > arrr[j+1])
				{
					// swap arr[j+1] and arr[i]
					int temp = arrr[j];
					arrr[j] = arrr[j+1];
					arrr[j+1] = temp;
				}
		return arrr;
	}

}
