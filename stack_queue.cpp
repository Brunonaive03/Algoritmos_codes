#include <iostream>
#include <string>
#include <cstddef> // p/ NULL

using namespace std;

struct node
{
    string data;
    node* next;
};

class stack
{
    private:
    node* node_topo;
    int num_pags;
    public:

    stack()
    {
        node_topo = NULL; 
        num_pags = 0; 
    }

    bool empty_stack()
    {
        return (node_topo == NULL);
    }


    int OPEN(string new_data)
    {
        node* novo_node = new node;
        

        novo_node -> next = node_topo;
        novo_node -> data = new_data;
        node_topo = novo_node;

        
        
        num_pags += 1;

        return num_pags;
    }

    string BACK() 
    {
        if(!empty_stack()){
            node* node_temp = node_topo;

            node_topo = node_topo->next;
            delete node_temp;

            num_pags -= 1;

            if(node_topo != NULL){
                return node_topo -> data;
            }else{
                return "NULL";
            }
            
        }else{
            return "NULL";
        }
    }

    string CURSOR()
    {
        if(node_topo != NULL){
            return node_topo -> data;
        
        }else{
            return "NULL";
        }
    }
    
    

    int PANIC() // apagar td
    {
        
        int pgs_apagadas = num_pags;
        while(node_topo != NULL){
            node* node_temp = node_topo;
            node_topo = node_topo->next;
            delete node_temp;
            
        }
        num_pags = 0;
        return pgs_apagadas;
    }

};

class queue
{
    private:
    node* node_inicio;
    node* node_final;
    int pags_salvas;

    public:

    queue()
    {
        node_inicio = NULL;
        pags_salvas = 0;  
    }

    bool empty_queue()
    {
        return (node_inicio == NULL);
    }


    int SAVE(string new_data)
    {
        node* novo_node = new node;
        pags_salvas += 1;

        novo_node -> next = NULL;
        novo_node -> data = new_data;
        
        if(node_inicio == NULL){
            node_inicio = novo_node;
        }else{
            node_final->next = novo_node;
        }  
        node_final = novo_node;

        
        
        
        return pags_salvas;

    }

    string READ()
    {
        if(!empty_queue()){
            pags_salvas -= 1;

            node* node_temp = node_inicio;
            string item_deletado = node_inicio->data;
            node_inicio = node_inicio->next;
            delete node_temp;

            return item_deletado;
        }else{
            return "NULL";
        }
    }


};


int main(){

    stack historico;
    queue salvos;

    string comando, pagina, pagina_printada;
    int index;

    do {

        cin >> comando;

        if(comando == "OPN"){
            cin >> pagina;
            index = historico.OPEN(pagina);
            cout << index << "\n";

        }else if(comando == "BCK"){
            pagina_printada = historico.BACK();
            cout << pagina_printada << "\n";
        
        }else if(comando == "CUR"){
            pagina_printada = historico.CURSOR();
            cout << pagina_printada << "\n";
        
        }else if(comando == "PAN"){
            index = historico.PANIC();
            cout << index << "\n";
        
        }else if(comando == "SAV"){
            pagina = historico.CURSOR();
            if(pagina != "NULL"){
                index = salvos.SAVE(pagina);
                cout << index << "\n";
            }
            
        }else if(comando == "REA"){
            pagina_printada = salvos.READ();
            cout << pagina_printada << "\n";
        
        }
        
    } while(comando != "END");

    return 0;

}
