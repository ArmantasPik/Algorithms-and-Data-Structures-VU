package com.company;

import java.util.List;
import java.util.Stack;

public class DepthFirstSearch {

    private Stack<Vertex> stack;

    public DepthFirstSearch() {
        this.stack = new Stack<>();
    }


    /**
     * Depth first search main method
     * @param vertexList The graph in a form of an ArrayList of vertices
     * @param rootVertexValue The sender (Root node)
     * @param resultVertexValue The receiver (Target node)
     * @return True if the target was reached and false if the target was not reached
     */
    public boolean depthFirstSearch(List<Vertex> vertexList, String rootVertexValue, String resultVertexValue) {

        //Check for root node and start with it first
        for(Vertex v : vertexList) {
            if(!v.isVisited() && v.getName().equals(rootVertexValue)) {
                v.setVisited(true);
                return dfsWithStack(v, resultVertexValue);
            }
        }

        return false;
    }


    /**
     * DFS sub method to traverse a graph using a stack
     * @param rootVertex The sender (root node)
     * @param resultVertexValue The receiver (root node)
     * @return True if target found, False if target not found
     */
    private boolean dfsWithStack(Vertex rootVertex, String resultVertexValue) {

        this.stack.add(rootVertex);

        while(!stack.isEmpty()) {
            Vertex actualVertex = this.stack.pop();
            System.out.print("-> " + actualVertex + " ");

            if(actualVertex.getName().equals(resultVertexValue)) {
                return true;
            }

            for(Vertex v : actualVertex.getAdjacentList()) {
                if(!v.isVisited()) {
                    v.setVisited(true);
                    this.stack.push(v);
                }
            }
        }

        return false;
    }
}
