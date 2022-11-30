#include <iostream>
#include <cstddef>


using namespace std;

struct node
{
  
  int valor;
  node* left;
  node* right;
  int bf;
};

struct insert_return
{
  node* root_return;
  int hc_return;
};


class AVL
{
  private:
  node* root;

  public:
    
  AVL(){ //construtor
    root = NULL;    
  }

  node* get_root(){
    cout << root -> valor << endl;
    return root;
  }

  insert_return insert_main(int val, node* root_ptr){
    int hc;
    insert_return retorno;


    if(root_ptr == NULL){
      node* R = new node;
      R->valor = val;
      R->bf = 0;
      R->left = NULL;
      R->right = NULL;

      retorno.root_return = R;
      retorno.hc_return = 1;

      return retorno;
    }
    else if(val == root_ptr->valor){
      retorno.root_return = root_ptr;
      retorno.hc_return = 0;
      
      
      return retorno;
    }
    else if(val < root_ptr->valor){
      retorno = insert_main(val, root_ptr -> left); 
      
      root_ptr -> left = retorno.root_return;
      hc = retorno.hc_return;

  
      root_ptr -> bf = (root_ptr -> bf) - hc;
      
    }
    else{
      retorno = insert_main(val, root_ptr -> right); 
      root_ptr -> right = retorno.root_return;
      hc = retorno.hc_return;

      root_ptr -> bf = (root_ptr -> bf) + hc;
    }
    
    if(hc == 0){
      retorno.root_return = root_ptr;
      retorno.hc_return = 0;
      return retorno;
    }
    else  if(root_ptr -> bf == 0){
      retorno.root_return = root_ptr;
      retorno.hc_return = 0;
      return retorno;
    }
    else if(root_ptr -> bf == 1 || root_ptr -> bf == -1 ){
      retorno.root_return = root_ptr;
      retorno.hc_return = 1;
      return retorno;
    }
    else if(root_ptr -> bf == 2){
      if(root_ptr -> right -> bf == -1){
        root_ptr -> right = rotate_right(root_ptr -> right); 
      }

      retorno.root_return = rotate_left(root_ptr);
      retorno.hc_return = 0;
      return retorno;
      
    }
    else{
      if(root_ptr -> left -> bf == 1){
        root_ptr -> left = rotate_left(root_ptr -> left);
      }
      retorno.root_return = rotate_right(root_ptr);
      retorno.hc_return = 0;
      return retorno;
    }
    
  }

  void insert(int val){
    root = insert_main(val, root).root_return;
  }



  node* search_main(int val, node* root_ptr){
    if(root_ptr == NULL){
      return NULL;
    }

    if(val == root_ptr -> valor){
      return root_ptr;
    }
    else if(val < root_ptr -> valor){
      return search_main(val, root_ptr -> left);
    }
    else{
      return search_main(val, root_ptr -> right);
    }
  }

  void search(int val){
    node* busca = search_main(val, root);

    if(busca == NULL){
      cout << "valor nao encontrado" << endl;
    }else{
      cout << busca->valor << ". valor encontrado" <<endl;
    }
  }


  node* rotate_left(node* root_ptr){
    node* R  = root_ptr -> right;
    node* RL = R -> left;
    R -> left = root_ptr;
    root_ptr -> right = RL;

    if (R-> bf <= 0){
      root_ptr -> bf = root_ptr -> bf - 1;
    }else{
      root_ptr -> bf = root_ptr -> bf - 1 - R -> bf;
    }

    if(root_ptr-> bf >= 0){
      R -> bf = R -> bf - 1;
    }else{
      R -> bf = R -> bf - 1 + root_ptr -> bf;
    } 
  
    return R;
  }

  node* rotate_right(node* root_ptr){
    node* R  = root_ptr -> left;
    node* RR = R -> right;
    R -> right = root_ptr;
    root_ptr -> left = RR;

    if (R-> bf >= 0){
      root_ptr -> bf = root_ptr -> bf + 1;
    }else{
      root_ptr -> bf = root_ptr -> bf + 1 - R -> bf;
    }

    if(root_ptr-> bf <= 0){
      R -> bf = R -> bf + 1;
    }else{
      R -> bf = R -> bf + 1 + root_ptr -> bf;
    } 
    return R;
  }
 
 
  /********************************/
  //PERCURSOS NA ARVORE:

  void preorder(node* root_ptr){

      if(root_ptr == NULL){
          return;
      }
      cout << root_ptr->valor << " ";
      cout << "(" << root_ptr->bf << ") ";
      preorder(root_ptr->left);
      preorder(root_ptr->right);
    }
  
  void postorder(node* root_ptr){

      if(root_ptr == NULL){
          return;
      }
      postorder(root_ptr->left);     
      postorder(root_ptr->right);
      cout << root_ptr->valor << " ";
      cout << "(" << root_ptr->bf << ") ";
  }
    
  void inorder(node* root_ptr){

      if(root_ptr == NULL){
          return;
      }
      inorder(root_ptr->left);
      cout << root_ptr->valor << " ";
      cout << "(" << root_ptr->bf << ") ";
      inorder(root_ptr->right);
    }
  /********************************/

};

int main() {

  
  AVL arvorezinha;
  string comando;
  int val;
  
  do
  {
    cin >> comando;

    if (comando == "ADD") {
      cin>>val;
      arvorezinha.insert(val);
    }
    else if (comando == "BUS") {
      cin>>val;
      arvorezinha.search(val);   
    }
    else if (comando == "PRE") {
      arvorezinha.preorder(arvorezinha.get_root());
      cout << "\n";
    }
    else if (comando == "POS") {
      arvorezinha.postorder(arvorezinha.get_root());
      cout << "\n";
    }
    else if (comando == "INO") {
      arvorezinha.inorder(arvorezinha.get_root());
      cout << "\n";
    }

  } while (comando != "END");


  return 0;
}