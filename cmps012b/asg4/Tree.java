//Ryan Coley
//12/8/14
//rjcoley
//1332490
//asg4
//tree.java
//makes a bst using queue and nodes

import static java.lang.System.*;

class Tree {

    private class Node {
        String key;
        Node left;
        Node right;
    }
    private Node root = null;

    private void outputHelper(Node tree) {
          if(tree != null){
               outputHelper(tree.left);
               System.out.print(tree.key+" ");
               outputHelper(tree.right);
          }
    }

    public void insert(String key) {
        Node n = new Node();
        n.key = key;
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
               }
          }
        }
    }

    public void output() {
        // Show sorted words with lines where each word appears
        outputHelper(root);
    }
}
