import java.util.*;

// Thanks @tirthraj07 - I am now convinced to give up on STL :)

class Node implements Comparable<Node>{
    // A Node will have x and y coordinates, values of g, h and f, and the parent Node

    public int x, y;
    public double g, h, f;
    public Node parent;

    // let's define the constructor

    public Node(int x, int y){
        this.x = x;
        this.y = y;
        this.g = Double.MAX_VALUE;
        this.h = Double.MAX_VALUE;
        this.f = Double.MAX_VALUE;
        this.parent = null;

        // now, we need to override the methods that are defined in the interface of Comapable<Node>  
    }

    // check of the x and y of this Node and the other node are equal. Before that, we firstly check if the passed Object is an instace of class Node


    @Override
    public boolean equals(Object obj){
        if(obj instanceof Node other){
            return this.x == other.x && this.y == other.y;
        }
        return false;
    }

    // in compareTo, we check compare the f values of the current and other Node

    @Override
    public int compareTo(Node other){
        return Double.compare(this.f, other.f);
    }

    // the default hashCode method will generate unique hashcodes for each Object. But here, we need to override it to generate same hashcodes for Nodes with same x and y

    @Override
    public int hashCode(){
        return Objects.hash(this.x, this.y);
    }

    // we also override the toString method to print the object of Node

    @Override
    public String toString(){
        return "(" + this.x + ", " + this.y + ")";
    }
}

class AStar{

    // in this class, we need to set all the variables and data structures required for the A* algorithm

    private int NUM_ROW, NUM_COL;
    private int[] dx = {0, 0, 1, -1};
    private int[] dy = {1, -1, 0, 0};
    private int[][] grid;
    private PriorityQueue<Node> openList;
    private HashSet<Node> closedList;

    // we can also store the goalNode as a data member of AStar, as it wont change. We don't need to pass the goalNode all the time explicitly.

    private Node goal;

    // lets begin the actual implementation

    //we need to keep 3 methods at handy: heuristic function, path printing logic, validity if coordinates

    private int heuristic(Node other){
        return Math.abs(goal.x - other.x) + Math.abs(goal.y - other.y);
    }

    private boolean isValid(int x, int y){
        return x>=0 && y>=0 && x<NUM_ROW && y<NUM_COL && grid[x][y]!=1;
    }

    private void printPath(){
        List<Node> path = new ArrayList<>();
        Node curr = this.goal;
        while(curr != null){
            path.add(curr);
            curr = curr.parent;
        }
        Collections.reverse(path);
        for(Node item : path){
            System.out.print(item.toString() + " ");
        }
    }

    // we wil implement the logic in the constructor itself

    public AStar(int [][] grid, Node start, Node goal){

        

        this.grid = grid;
        this.NUM_ROW = grid.length;
        this.NUM_COL = grid[0].length;

        // added edge cases

        if(!isValid(start.x, start.y)){
            System.out.println("Invalid start coordinate!");
            return;
        }

        if(!isValid(goal.x, goal.y)){
            System.out.println("Invalid goal coordinate!");
            return;
        }
        
        this.goal = goal;
        this.openList = new PriorityQueue<>();
        this.closedList = new HashSet<>();



        start.g = 0;    // we start here, so actual distance from previous node is 0, as there is no previous node
        start.h = heuristic(start);     // calculate estimated cost from start to goal (remember, goal is implicit here)
        
        start.f = start.h + start.g;    // set the total cost (h + g)

        openList.offer(start); 


        while(!openList.isEmpty()){

            Node current = openList.poll();
            closedList.add(current);

            // firstly, lets check if the goal is reached

            if(current.equals(goal)){
                goal.parent = current.parent;
                printPath();
                return;
            }

            // now we can explore the neighbors of current node, by moving is all the 4 directions

            for(int i=0; i<4; i++){
                int newx = current.x + dx[i];
                int newy = current.y + dy[i];

                //if newx, newy are out of bound or is a obstacle, skip it

                if(!isValid(newx, newy)) continue;

                Node nbr = new Node(newx, newy);
                nbr.g = current.g + 1;  //g will be 1 more than the current node, as we move in unit distance
                nbr.h = heuristic(nbr);
                nbr.f = nbr.g + nbr.h;
                nbr.parent = current;   //nbr is a child of current, so we set parent of nbr as current
                
                // now let's first check if it is the closedlist, if yes no need to revisit it

                if(closedList.contains(nbr)) continue;

                // now we also need to check that for same x, y do we have a Node in the openList already
                // if we have one, and it has less g value that nbr, we remove it from the openList (THIS IS THE EXACT REASON TO NOT USE priority_queue in C++, as we cannot pop arbitrary item from it :/ )

                Node nodeAlreadyInOpenList = openList.stream().filter(n -> n.equals(nbr)).findFirst().orElse(null);

                if(nodeAlreadyInOpenList!=null && nodeAlreadyInOpenList.g > nbr.g){
                    openList.remove(nodeAlreadyInOpenList);
                }
                openList.offer(nbr);
            }
        }

        System.out.println("Goal is unreachable!");
    }

    public static void main(String[] args){
        int[][] grid = {
            {0, 0, 1, 1, 0},
            {1, 0, 0, 1, 1},
            {0, 1, 0, 0, 0},
            {1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0}
        };

        Node startNode = new Node(0, 0);
        Node goalNode = new Node(4, 4);

        AStar aStar = new AStar(grid, startNode, goalNode);
    } 
}

