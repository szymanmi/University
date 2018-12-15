package iterator;

import java.util.List;


public class Maker implements IteratorMaker {
	private List<int[]> list;

	public Maker(List<int[]> list){
		this.list = list;
	}

	@Override
	public Iterator getIterator() {
		return new IntIterator();
	}

	private class IntIterator implements Iterator {

		int index;

		@Override
		public boolean hasNext() {

			return index < list.size();
		}

		@Override
		public Object next() {

			if(this.hasNext()){
				return list.get(index++);
			}
			return null;
		}
	}

}