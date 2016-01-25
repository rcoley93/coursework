//Ryan Coley
//11/21/14
//rjcoley
//1332490
//asg3
//tree.java
//makes a bst using queue and nodes

import static java.lang.System.*;

class Tree {

    private class Node {
        String key;
        Queue value = new Queue();
        Node left;
        Node right;
    }
    private Node root = null;

    private void debugHelper(Node tree,int d) {
     if(tree == null){
          return;
     }
     debugHelper(tree.left,d+1);
     for(int i=0;i<d;i++){
          System.out.print("  ");
     }
     System.out.println(d + ": " + tree.key);
     debugHelper(tree.right,d+1);
    }

    private void outputHelper(Node tree) {
          if(tree != null){
               outputHelper(tree.left);
               System.out.print(tree.key +": ");
               tree.value.printQueue();
               System.out.println();
               outputHelper(tree.right);
          }
    }

    public void insert(String key, int linenum) {
        Node n = new Node();
        n.key = key;
        n.value.insert(linenum);
        n.left = null;
        n.right = null;
        if(root == null){root = n;}
        else{
          Node temp = root;
          while(true){
               if(n.key.compareTo(temp.key) < 0){
                    if(temp.left == null){
                         temp.left = n;
                         break;
                    }else temp = temp.left;
               }else if(n.key.compareTo(temp.key) > 0){
                    if(temp.right == null){
                         temp.right = n;
                         break;
                    }else temp = temp.right;
               }else if(n.key.compareTo(temp.key) == 0){
                    temp.value.insert(linenum);
                    break;
               }
          }
        }
    }

    public void debug() {
        // Show debug output of tree
        debugHelper(root,0);
    }

    public void output() {
        // Show sorted words with lines where each word appears
        outputHelper(root);
    }
}
