package com.company;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/* Task:
 * Duota informacija, kokios žmonių poros yra pažįstamos. Patikrinti, ar, pavyzdžiui,
 * Jonas gali perduoti Marytei laiškelį per pažįstamus. (grafo realizacija paremta kaimynystės sąrašais; naudoti paieškos į gylį metodą)
*/

public class GraphMain {

    // Driver Code
    public static void main(String args[]) {

        List<Vertex> list = null;
        String rootVertexName = "";
        String resultVertexName = "";

        //Firstly, initialize the graph
        while (list == null) {
            list = initializeData();
        }

        //Validate name of the sender
        while (rootVertexName.isEmpty()) {
            System.out.print("Enter who is sending letter: ");
            rootVertexName = validateString(list);
        }

        //Validate name of the receiver
        while (resultVertexName.isEmpty()) {
            System.out.print("Enter who is receiving letter: ");
            resultVertexName = validateString(list);
        }

        DepthFirstSearch dfs = new DepthFirstSearch();

        //Execute depth first search
        if (dfs.depthFirstSearch(list, rootVertexName, resultVertexName)) {
            System.out.println("\nIt is possible");
        } else {
            System.out.println("\nIt is not possible");
        }
    }


    /**
     * Method to initialize graph data from a file
     * @return Returns list if the file is valid and data can be initialized, otherwise return null
     */
    public static List<Vertex> initializeData() {
        List<Vertex> list = new ArrayList<>();
        Scanner scanner = new Scanner(System.in);
        String fileName;
        File dataFile;

        //Read data file name from console
        System.out.print("Enter data file name: ");
        fileName = scanner.nextLine();
        dataFile = new File("C:\\Users\\arman\\Desktop\\vu\\ADS\\graph\\project\\data\\" + fileName);

        //If data file exist then execute initialization
        if (dataFile.exists() && !dataFile.isDirectory()) {
            String line = "";
            String splitBy = ",";

            //Reading data from file
            try {
                BufferedReader br = new BufferedReader(new FileReader(dataFile.getAbsolutePath()));

                //If there is data in the file read it
                if ((line = br.readLine()) != null) {
                    String[] readVertices = line.split(splitBy);

                    //Initialize Vertices (First line of initial values)
                    for (int i = 0; i < readVertices.length; i++) {
                        Vertex initialVertex = new Vertex(readVertices[i]);
                        list.add(initialVertex);

                        System.out.print(readVertices[i] + " ");
                    }
                    System.out.println();

                    //Add adjacent vertices from data file
                    while ((line = br.readLine()) != null) {
                        String[] readAdjacent = line.split(splitBy);

                        for (Vertex rootVertex : list) {

                            if (rootVertex.getName().equals(readAdjacent[0])) {

                                for (int i = 1; i < readAdjacent.length; i++) {

                                    for (Vertex adjacentVertex : list) {

                                        if (readAdjacent[i].equals(adjacentVertex.getName())) {
                                            rootVertex.addNeighbour(adjacentVertex);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    br.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        } else {
            System.out.println("File is not valid. Try again.");
            return null;
        }

        return list;
    }


    /**
     * Validate whether a string value is inside a given graph
     * @param list list of vertices
     * @return vertexName if it is valid, if it is not valid then return empty string
     */
    public static String validateString(List<Vertex> list) {
        Scanner scanner = new Scanner(System.in);
        boolean flag = false;

        String vertexName = scanner.nextLine();

        for (Vertex checkVertex : list) {
            if (vertexName.equals(checkVertex.getName())) {
                flag = true;
                break;
            }
        }

        if (!flag) {
            System.out.println("The name you entered did match anyone in the list");
            vertexName = "";
        }

        return vertexName;
    }

}