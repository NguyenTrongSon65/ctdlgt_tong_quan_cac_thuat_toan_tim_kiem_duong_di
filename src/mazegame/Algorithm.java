package mazegame;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.Stack;


public class Algorithm {
	
	private int searchtime = 100;
	
	public int getSearchTime() {
		return searchtime;
	}
	public void setSearchTime(int searchtime) {
		this.searchtime = searchtime;
	}

	public void dfs(Node start) {
		Stack<Node> nodes = new Stack<>();
		nodes.push(start);

		while (!nodes.empty()) {

			Node curNode = nodes.pop();
			if (!curNode.isEnd()) {

				curNode.setColor(Color.ORANGE);
				try {
					Thread.sleep(searchtime);
				} catch (Exception e) {
					e.printStackTrace();
				}
				curNode.setColor(Color.BLUE);
				for (Node adjacent : curNode.getNeighbours()) {
					nodes.push(adjacent);
				}

			} else {
				curNode.setColor(Color.MAGENTA);
				break;
			}
		}

	}

	public void bfs(Node start, Node end, int graphWidth, int graphHeight) {
		Queue<Node> queue = new LinkedList<>();
		Node[][] prev = new Node[graphWidth][graphHeight];

		queue.add(start);
		while (!queue.isEmpty()) {

			Node curNode = queue.poll();
			if (curNode.isEnd()) {
				curNode.setColor(Color.MAGENTA);
				break;
			}

			if (!curNode.isSearched()) {
				curNode.setColor(Color.ORANGE);
				try {
					Thread.sleep(searchtime);
				} catch (Exception e) {
					e.printStackTrace();
				}
				curNode.setColor(Color.BLUE);
				for (Node adjacent : curNode.getNeighbours()) {
					queue.add(adjacent);
					prev[adjacent.getX()][adjacent.getY()] = curNode;
					

				}
			}
		}

		//shortpath(prev, end);
	}

	private void shortpath(Node[][] prev, Node end) {
		Node pathConstructor = end;
		while(pathConstructor != null) {
			pathConstructor = prev[pathConstructor.getX()][pathConstructor.getY()];

			if(pathConstructor != null) {
			pathConstructor.setColor(Color.ORANGE);
			}
			try {
				Thread.sleep(searchtime);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}
